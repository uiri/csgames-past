/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetworkController.cpp
** Implementation of the NetworkController
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "NetworkController.h"

NetworkController::NetworkController() : resolver(io_service), query("127.0.0.1", "1337"), socket(io_service), eventFactory()
{
	endpoint_iterator = resolver.resolve(query);
	readerThread = NULL;
	writerThread = NULL;
	status = ControllerStatus::TryToConnect;
	exitSocket = false;
}

NetworkController::~NetworkController()
{
	if(readerThread)
	{
		delete readerThread;
	}

	if(writerThread)
	{
		delete writerThread;
	}
}

void NetworkController::writeFunc()
{
	bool exit = false;
	try
	{
		std::string message = "";

		while(!exit)
		{
			if(!QueueController::getInstance().isMessageQueueEmpty())
			{
				message = QueueController::getInstance().getMessage();

				if(message == "Exit")
				{
					exit = true;
				}

				// To be sure that message don't overlap
				message += '\n';

				boost::system::error_code ignored_error;
				boost::asio::write(socket, boost::asio::buffer(message),
							   boost::asio::transfer_all(), ignored_error);
			}
			boost::this_thread::sleep(boost::posix_time::milliseconds(30));
		}
		readerThread->join();
		socket.close();
	}
	catch (std::exception& e)
	{
		printf("Exception in writter : %s\n", e.what());
	}
}

void NetworkController::init()
{
	while(status == ControllerStatus::TryToConnect)
	{
		if(!tryToConnect())
		{
			printf("Can't reach server... Will try again in 2s\n");
			boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
		}
		else
		{
			status = ControllerStatus::TryJoinGame;
		}
	}

	try
	{
		if(readerThread == NULL)
		{
			readerThread = new boost::thread( boost::bind (&NetworkController::readerFunc, this));
		}

		if(writerThread == NULL)
		{
			writerThread = new boost::thread( boost::bind (&NetworkController::writeFunc, this));
		}
	}
	catch (std::exception& e)
	{
		printf("Exception in init : %s\n", e.what());
	}

	tryJoinGame();
}

bool NetworkController::tryToConnect()
{
	try
	{
		boost::asio::connect(socket, endpoint_iterator);
	}
	catch (std::exception& e)
	{
		printf("Exception in init : %s\n", e.what());
		return false;
	}
	return true;
}

void NetworkController::tryJoinGame()
{
	QueueController::getInstance().addMessage("GameClientReady");
	status = ControllerStatus::WaitingYouAreTheGameClient;
}

void NetworkController::readerFunc()
{
	try
	{
		while(!exitSocket)
		{
			//we read the buffer to put the message in the buffer
			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				throw boost::system::system_error(error); // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			buf.data()[len] = '\0';
			std::string messagePack = buf.data();

			std::string message = NetUtility::getNextToken(messagePack, "\n");
			while (!message.empty())
			{
				parseMessage(message);
				message = NetUtility::getNextToken(messagePack, "\n");
			}
		}
	}
	catch (std::exception& e)
	{
		printf("Exception in reader : %s\n", e.what());
	}
}

void NetworkController::parseMessage(std::string message)
{
	std::string header = NetUtility::getNextToken(message, ":");
	if(header == "Net")
	{
		parseMessageBody(message);
	}
	else if(header == "Game")
	{
		eventFactory.generate(message);
	}
}

void NetworkController::close()
{
	QueueController::getInstance().addMessage("Exit");

	if(readerThread)
		readerThread->join();

	if(writerThread)
		writerThread->join();
}

void NetworkController::parseMessageBody(std::string body)
{
	if(body == "OkForExit")
	{
		exitSocket = true;
	}
	else if(body == "YourAreTheGameClient")
	{
		status = ControllerStatus::Connected;
	}
	else if(body == "ErrorClientAlreadyConnected")
	{
		close();
	}
}
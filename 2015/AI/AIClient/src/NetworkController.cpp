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

#include "NetworkController.h"

NetworkController::NetworkController(GameMap* gameMap) : resolver(io_service), query("127.0.0.1", "1337"), socket(io_service), netCommandController(gameMap)
	{
		this->gameMap = gameMap;

		endpoint_iterator = resolver.resolve(query);
		readerThread = NULL;
		writerThread = NULL;
		status = ControllerStatus::TryToConnect;
		gameStarted = false;
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
			if(!messageQueue.empty())
			{
				message = messageQueue.back();
				messageQueue.pop();

				if(message == "Exit")
				{
					exit = true;
				}
				else if(message == "AIClientReady")
				{
					boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
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
	messageQueue.push("AIClientReady");
	status = ControllerStatus::WaitingYouAreTheGameClient;
}

void  NetworkController::addMessageToQueue(std::string message)
{
	messageQueue.push(message);
}

void NetworkController::readerFunc()
{
	bool exit = false;
	try
	{
		while(!exit)
		{
			//we read the buffer to put the message in the buffer
			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof)
				throw boost::system::system_error(error); // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			buf.data()[len] = '\0';

			if(!std::strcmp(buf.data(), "OkForExit"))
			{
				exit = true;
				break;
			}

			char* seps = ":";
			char* message = buf.data();
			char* token = NULL;
			char* next_token = NULL;

			token = strtok(message, seps);

			while(token != NULL)
			{
				if(status == ControllerStatus::Connected)
				{
					if(!strcmp(token, "GameStart"))
					{
						gameStarted = true;
					}
					netCommandController.UpdateStateMachine(token);
				}
				else
				{
					parseMessage(token);
				}
				token = strtok(NULL, seps);
			}
		}
	}
	catch (std::exception& e)
	{
		printf("Exception in reader : %s\n", e.what());
	}
}

void NetworkController::close()
{
	std::string message = "Exit";
	addMessageToQueue(message);

	if(readerThread)
		readerThread->join();

	if(writerThread)
		writerThread->join();
}

void NetworkController::parseMessage(char* token)
{
	if(!strcmp(token, "YourId"))
	{
		netCommandController.UpdateStateMachine(token);
		status = ControllerStatus::Connected;
	}
	else if(!strcmp(token, "ErrorGameClientNotConnected"))
	{
		printf("The game client is not connected... Will try again in 2s\n");
		tryJoinGame();
	}
}

bool NetworkController::isConnected()
{
	return (status == ControllerStatus::Connected)?true:false;
}

bool NetworkController::isGameStarted()
{
	return gameStarted;
}

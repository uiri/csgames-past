/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Main.cpp
** The main function to test the ai client
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include <iostream>

#include "NetworkController.h"
#include "GameMap.h"

namespace
{
	enum AiStatus {AddPlayer, WaitGameStart, MoveToCorner, WaitReachCorner};
};

int main(int argc, char* argv[])
{
	try
	{
		std::string playerName = "Rudolf";
		std::string characterName1 = "dodo";
		std::string characterName2 = "potato";
		std::string characterNames[2] = {characterName1, characterName2};

		GameMap gameMap(playerName, characterNames);
		AiStatus myStatus = AiStatus::AddPlayer;
		NetworkController netController(&gameMap);

		netController.init();

		bool exit = false;

		std::string message = "";

		while(!exit)
		{
			if(netController.isConnected())
			{
				if(myStatus == AiStatus::AddPlayer)
				{
					boost::this_thread::sleep(boost::posix_time::milliseconds(2000));
					char numstr[21]; // enough to hold all numbers up to 64-bits
					sprintf_s(numstr, "%d", gameMap.yourId);
					characterNames[0] += numstr;
					characterNames[1] += numstr;
					playerName += numstr;

					std::string message = NetUtility::generateAddPlayerMessage(playerName, characterNames);
					netController.addMessageToQueue(message);
					myStatus = AiStatus::WaitGameStart;
				}
				else if(myStatus == AiStatus::WaitGameStart && netController.isGameStarted())
				{
					myStatus = AiStatus::MoveToCorner;
				}
				else if(myStatus == AiStatus::MoveToCorner)
				{
					std::string message = NetUtility::generateMoveCharacterMessage(1,50,50);
					netController.addMessageToQueue(message);

					message = NetUtility::generateMoveCharacterMessage(0,-50,-50);
					netController.addMessageToQueue(message);

					myStatus = AiStatus::WaitReachCorner;
				}
				else if(myStatus == AiStatus::WaitReachCorner)
				{
					if(gameMap.players[gameMap.yourId]->characters[1]->x > 45)
					{
						printf("Yep its over!!\n");
					}
				}
			}
			boost::this_thread::sleep(boost::posix_time::milliseconds(30));
		}

		netController.close();
	}
	catch (std::exception& e)
	{
		printf("Exception in main : %s\n", e.what());
	}
}
/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetPlayerController.cpp
** Implementation of the NetPlayerController
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "NetPlayerController.h"

NetPlayerController::NetPlayerController(std::queue<std::string>* messageQueue)
{
	this->messageQueue = messageQueue;
}

NetPlayerController::~NetPlayerController()
{

}

void NetPlayerController::addPlayer(int id, char* playerName, char* characterNames[maxCharacter])
{
	netPlayers[id] = new NetPlayer(messageQueue, playerName, id, characterNames);

	if(netPlayers.size() == MAX_PLAYER)
	{
		typedef std::map<int, NetPlayer*>::iterator it_type;
		for(it_type iterator = netPlayers.begin(); iterator != netPlayers.end(); ++iterator)
		{
			messageQueue->push(NetUtility::updatePlayer(iterator->first));

			for( int j=0; j<maxCharacter; ++j)
			{
				// TODO: use the map to check the starting position
				iterator->second->moveCharacter(j, iterator->first*10, j*10);
			}
		}
	}
}

void NetPlayerController::quitPlayer(int id)
{
	std::map<int, NetPlayer*>::iterator it = netPlayers.find(id);
	NetPlayer* disconnectedPlayer = it->second;
	netPlayers.erase(it);
	delete disconnectedPlayer;
}

void NetPlayerController::moveCharacter(int playerId, int characterId, double x, double y)
{
	NetPlayer* targetPlayer = netPlayers.find(playerId)->second;
	if(targetPlayer)
	{
		targetPlayer->moveCharacter(characterId, x, y);
	}
}
/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** GameMap.cpp
** Implementation of the GameMap
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "GameMap.h"

GameMap::GameMap(std::string playerName, std::string characterNames[maxCharacter])
{
	this->playerName = playerName;
	for( int i=0; i<maxCharacter; ++i)
	{
		this->characterNames[i] = characterNames[i];
	}
}

GameMap::~GameMap()
{
	if(players[yourId])
		delete players[yourId];

	if(players[opponentId])
		delete players[opponentId];
}

void GameMap::printSelf()
{
	if(players[yourId])
		players[yourId]->printSelf();

	if(players[opponentId])
		players[opponentId]->printSelf();
}

void GameMap::addPlayer(int id)
{
	if(id == yourId)
	{
		players[id] = new Player(playerName, characterNames);
	}
	else
	{
		opponentId = id;
		players[id] = new Player();
	}
}

void GameMap::quitPlayer(int id)
{
	std::map<int, Player*>::iterator it = players.find(id);
	Player* disconnectedPlayer = it->second;
	players.erase(it);
	delete disconnectedPlayer;
}

void GameMap::moveCharacter(int playerId, int characterId, double x, double y)
{
	Player* targetPlayer = players.find(playerId)->second;
	if(targetPlayer)
	{
		targetPlayer->moveCharacter(characterId, x, y);
	}
}

void GameMap::setYourID(int id)
{
	this->yourId = id;
}
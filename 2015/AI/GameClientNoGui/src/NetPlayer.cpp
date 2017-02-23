/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetPlayer.cpp
** Implementation of the NetPlayer
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "NetPlayer.h"

NetPlayer::NetPlayer(std::queue<std::string>* messageQueue, int playerId)
{
	this->tagName = "NoName";
	this->messageQueue = messageQueue;
	this->playerId = playerId;

	for(int i = 0; i < maxCharacter; ++i)
	{
		netCharacters[i] = new NetCharacter(messageQueue, "NoName", 0, 0, playerId, i);
	}
}

NetPlayer::NetPlayer(std::queue<std::string>* messageQueue, char* tagName, int playerId, char* characterNames[maxCharacter])
{
	this->tagName = "NoName";
	this->messageQueue = messageQueue;
	this->playerId = playerId;

	for(int i = 0; i < maxCharacter; ++i)
	{
		netCharacters[i] = new NetCharacter(messageQueue, characterNames[i], 0, 0, playerId, i);
	}
}

NetPlayer::~NetPlayer()
{
	for(int i = 0; i < maxCharacter; ++i)
	{
		if(netCharacters[i])
		{
			delete netCharacters[i];
		}
	}
}

void NetPlayer::moveCharacter(int id, double x, double y)
{
	netCharacters[id]->moveCharacter(x, y);
}

/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetCharacter.cpp
** Implementation of the NetCharacter
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "NetCharacter.h"

NetCharacter::NetCharacter(std::queue<std::string>* messageQueue)
{
	this->messageQueue = messageQueue;
}

NetCharacter::NetCharacter(std::queue<std::string>* messageQueue, std::string tagName, double x, double z, int playerId, int characterId)
{
	this->messageQueue = messageQueue;
	this->tagName = tagName;
	this->x = x;
	this->z = z;
	this->playerId = playerId;
	this->characterId = characterId;
}

NetCharacter::~NetCharacter()
{

}

void NetCharacter::moveCharacter(double x, double z)
{
	this->x = x;
	this->z = z;

	messageQueue->push(NetUtility::generateMoveCharacterPacket(playerId, characterId, x, z));
}

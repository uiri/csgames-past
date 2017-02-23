/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetCharacter.h
** The Character that is controlled by the AI
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __NetCharacter_h_
#define __NetCharacter_h_

#include <iostream>
#include <queue>

#include "NetUtility.h"

class NetCharacter
{
private:
	std::queue<std::string>* messageQueue;
	std::string tagName;
	int playerId;
	int characterId;
	double x;
	double z;

public:
	NetCharacter(std::queue<std::string>* messageQueue);
	NetCharacter(std::queue<std::string>* messageQueue, std::string tagName, double x, double z, int playerId, int characterId);
	~NetCharacter();
	void moveCharacter(double x, double y);
};

#endif // #ifndef __NetCharacter_h_
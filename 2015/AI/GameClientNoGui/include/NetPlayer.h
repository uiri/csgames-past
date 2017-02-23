/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetPlayer.h
** The player that controle a character team
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __NetPlayer_h_
#define __NetPlayer_h_

#include <iostream>
#include <map>

#include "NetCharacter.h"

#define maxCharacter 2

class NetPlayer
{
private:
	std::queue<std::string>* messageQueue;
	char* tagName;
	std::map<int, NetCharacter*> netCharacters;
	int playerId;

public:
	NetPlayer(std::queue<std::string>* messageQueue, int playerId);
	NetPlayer(std::queue<std::string>* messageQueue, char* tagName, int playerId, char* characterNames[maxCharacter]);
	~NetPlayer();
	void moveCharacter(int id, double x, double y);
};

#endif // #ifndef __NetCharacter_h_
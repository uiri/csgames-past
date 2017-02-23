/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetCommandController.h
** The controler for all the command receive over the network
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __NetCommandController__
#define __NetCommandController__

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "GameMap.h"

namespace Command
{
	enum State { Init, WaitingDescription, WaitingPlayerId, WaitingPosX, WaitingPosZ, 
				 WaitingCharacterId, WaitingGameClientId };
	enum CommandType { None, Error, YourId, UpdatePlayer, UpdateCharacter };
};

class NetCommandController
{
private:
	GameMap* gameMap;
	Command::State mState;
	Command::CommandType mType;
	double x;
	double z;
	int playerId;
	int characterId;
	char* description;

public:
	NetCommandController(GameMap* gameMap);
	void UpdateStateMachine(char* token);
	
	void Error();
	void YourId();
	void UpdatePlayer();
	void UpdateCharacter();
	void OkForExit();
};

#endif

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
#include "NetPlayerController.h"

namespace Command
{
	enum State { Init, WaitingDescription, WaitingPlayerId, WaitingPlayerName, WaitingCharacterName,
				 WaitingPosX, WaitingPosZ, WaitingCharacterId };
	enum CommandType { None, Error, Disconnect, AddPlayer, Move };
};

class NetCommandController
{
private:
	NetPlayerController* netPlayerController;
	Command::State mState;
	Command::CommandType mType;
	double x;
	double z;
	int playerId;
	int characterId;
	char* description;
	char* playerName;

	int characterCount;
	char* characterNames[maxCharacter];

public:
	NetCommandController(NetPlayerController* netPlayerController);
	void UpdateStateMachine(char* token);
	
	void Error();
	void Disconnect();
	void AddPlayer();
	void MoveCharacter();
	void OkForExit();
};

#endif

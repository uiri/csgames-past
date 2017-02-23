/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetCommandController.cpp
** Implementation of the NetCommandController
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "NetCommandController.h"

NetCommandController::NetCommandController(GameMap* gameMap)
{
	this->gameMap = gameMap;
	mState = Command::Init;
	mType = Command::None;
	x = 0;
	z = 0;
	playerId = 0;
	characterId = 0;
	description = "";
}

void NetCommandController::UpdateStateMachine(char* token)
{
	bool bIsDigit = true;

	switch(mState)
	{
	case Command::Init:
		if(!strcmp(token, "Error"))
		{
			mType = Command::Error;
			mState = Command::WaitingDescription;
		}
		else if(!strcmp(token, "YourId"))
		{
			mType = Command::YourId;
			mState = Command::WaitingPlayerId;
		}
		else if(!strcmp(token, "UpdatePlayer"))
		{
			mType = Command::UpdatePlayer;
			mState = Command::WaitingPlayerId;
		}
		else if(!strcmp(token, "UpdateCharacter"))
		{
			mType = Command::UpdateCharacter;
			mState = Command::WaitingPlayerId;
		}
		break;

	case Command::WaitingDescription:
		description = token;

		if(mType == Command::Error)
		{
			Error();
		}
		mState = Command::Init;
		mType = Command::None;
		break;

	case Command::WaitingPosX:
		for (int i = (int) strlen(token)-1; i > 0; i--)
			if (!isdigit(token[i]))
			{
				bIsDigit = false;
				break;
			}

		if(bIsDigit)
		{
			x = atoi(token);
			mState = Command::WaitingPosZ;
		}
		else
		{
			mState = Command::Init;
		}
		break;

	case Command::WaitingPosZ:
		for (int i = (int) strlen(token)-1; i > 0; i--)
			if (!isdigit(token[i]))
			{
				bIsDigit = false;
				break;
			}

		if(bIsDigit)
		{
			z = atoi(token);
			mState = Command::WaitingGameClientId;
		}
		else
		{
			mState = Command::Init;
		}
		break;

	case Command::WaitingCharacterId:
		for (int i = (int) strlen(token)-1; i > 0; i--)
			if (!isdigit(token[i]))
			{
				bIsDigit = false;
				break;
			}

		if(bIsDigit)
		{
			characterId = atoi(token);
			mState = Command::WaitingPosX;
		}
		else
		{
			mState = Command::Init;
			mType = Command::None;
		}
		break;

	case Command::WaitingPlayerId:
		for (int i = (int) strlen(token)-1; i > 0; i--)
			if (!isdigit(token[i]))
			{
				bIsDigit = false;
				break;
			}

		if(bIsDigit)
		{
			playerId = atoi(token);
			if(mType == Command::YourId)
				YourId();
			else if (mType == Command::UpdatePlayer)
				UpdatePlayer();
		}

		if (mType == Command::UpdateCharacter)
		{
			mState = Command::WaitingCharacterId;
		}
		else
		{
			mState = Command::Init;
			mType = Command::None;
		}
		break;

	case Command::WaitingGameClientId:
		if(mType = Command::UpdateCharacter)
		{
			UpdateCharacter();
		}
		mState = Command::Init;
		mType = Command::None;
		break;
	}
}

void NetCommandController::Error()
{
	std::cout << "Error :" << description << std::endl;
}

void NetCommandController::YourId()
{
	std::cout << "You receive the id:  " << playerId << std::endl;
	gameMap->setYourID(playerId);
}

void NetCommandController::UpdatePlayer()
{
	std::cout << "New player with id:  " << playerId << std::endl;
	gameMap->addPlayer(playerId);
}


void NetCommandController::UpdateCharacter()
{
	std::cout << "Player " << playerId << " move character " << characterId << 
				 " to (" << x << "," << z << ")" << std::endl;

	gameMap->moveCharacter(playerId, characterId, x, z);
}

void NetCommandController::OkForExit()
{
	std::cout << "You are ok to disconnect!" << std::endl;

	// TODO: check what to do here
}

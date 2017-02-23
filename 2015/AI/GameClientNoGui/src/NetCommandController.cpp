/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetCommandController.cpp
** Implementation of NetCommandController
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "NetCommandController.h"

NetCommandController::NetCommandController(NetPlayerController* netPlayerController)
{
	this->netPlayerController = netPlayerController;
	mState = Command::Init;
	mType = Command::None;
	x = 0;
	z = 0;
	playerId = 0;
	characterId = 0;
	description = "";
	playerName = "";
	characterCount = 0;
	
	for( int i=0; i<maxCharacter; ++i)
	{
		characterNames[i] = "";
	}
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
		else if(!strcmp(token, "Disconnect"))
		{
			mType = Command::Disconnect;
			mState = Command::WaitingPlayerId;
		}
		else if(!strcmp(token, "AddPlayer"))
		{
			mType = Command::AddPlayer;
			mState = Command::WaitingPlayerName;
		}
		else if(!strcmp(token, "Move"))
		{
			mType = Command::Move;
			mState = Command::WaitingPosX;
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
			mState = Command::WaitingCharacterId;
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
			mState = Command::WaitingPlayerId;
		}
		else
		{
			mState = Command::Init;
			mType = Command::None;
		}
		break;

	case Command::WaitingPlayerName:
		playerName = token;
		mState = Command::WaitingCharacterName;
		characterCount = 0;
		break;

	case Command::WaitingCharacterName:
		characterNames[characterCount++] = token;

		if(characterCount > maxCharacter-1)
		{
			mState = Command::WaitingPlayerId;
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
			if(mType == Command::AddPlayer)
				AddPlayer();
			else if (mType == Command::Move)
				MoveCharacter();
			else if (mType == Command::Disconnect)
				Disconnect();
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

void NetCommandController::Disconnect()
{
	std::cout << "Player " << playerId << " disconnected from the game" << std::endl;

	netPlayerController->quitPlayer(playerId);
}

void NetCommandController::AddPlayer()
{
	std::cout << "Player " << playerId << " join with name " << playerName << std::endl;
	for( int i=0; i<maxCharacter; ++i)
	{
		std::cout << "    * Character " << characterNames[i] << " enter the battlefield" << std::endl;
	}
	
	netPlayerController->addPlayer(playerId, playerName, characterNames);
}

void NetCommandController::MoveCharacter()
{
	std::cout << "Player " << playerId << " move character " << characterId << 
				 " to (" << x << "," << z << ")" << std::endl;

	netPlayerController->moveCharacter(playerId, characterId, x, z);
}

void NetCommandController::OkForExit()
{
	std::cout << "You are ok to disconnect!" << std::endl;

	// TODO: check what to do here
}
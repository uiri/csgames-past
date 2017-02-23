/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**         \/        \/             \/         \/         \/        \/        \/ 
**
** EventFactory.h
** The factory to create all the GameEvent that come from the net
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "EventFactory.h"

EventFactory::EventFactory()
{
}

EventFactory::~EventFactory()
{
}

void EventFactory::generate(std::string message)
{
	std::string type = NetUtility::getNextToken(message, ":");

	GameEvent* currentEvent = createEvent(type);
	if(currentEvent)
	{
		if(currentEvent->fill(message))
		{
			QueueController::getInstance().addEvent(currentEvent);
		}

	}
}

GameEvent* EventFactory::createEvent(std::string type)
{
	if(type == "Error")
	{
		return new ErrorEvent();
	}
	else if(type == "Disconnect")
	{
		return new DisconnectEvent();
	}
	else if(type == "AddPlayer")
	{
		return new AddTeamEvent();
	}
	else if(type == "Move")
	{
		return new MoveCharacterEvent();
	}
	else if(type == "DropMine")
	{
		return new DropMineEvent();
	}
	else if(type == "ThrowMissile")
	{
		return new ThrowMissileEvent();
	}
	return NULL;
}

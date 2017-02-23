/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**         \/        \/             \/         \/         \/        \/        \/ 
**
** QueueController.h
** Implementation of the QueueController
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "QueueController.h"

QueueController::QueueController()
{
}

void QueueController::addEvent(GameEvent* gameEvent)
{
	//TODO: try to reproduce the crash here
	if(!gameEvent)
		gameEvent->getType();
	gameEventQueue.push(gameEvent);
}

GameEvent* QueueController::getEvent()
{
	GameEvent* event = gameEventQueue.front();
	gameEventQueue.pop();
	return event;
}

bool QueueController::isGameEventQueueEmpty()
{
	return gameEventQueue.empty();
}

void QueueController::addMessage(std::string message)
{
	messageQueue.push(message);
}

std::string QueueController::getMessage()
{
	std::string message = messageQueue.front();
	messageQueue.pop();
	return message;
}

bool QueueController::isMessageQueueEmpty()
{
	return messageQueue.empty();
}

/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**         \/        \/             \/         \/         \/        \/        \/ 
**
** EventController.h
** Controller that manage all the event
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __EventController_h_
#define __EventController_h_

#include "GameEvent.h"
#include "QueueController.h"
#include "World.h"

class EventController
{
private:

public:
    EventController();
    virtual ~EventController();

	void executeAllGameEvent();
	void dispatchEvent(GameEvent* gameEvent);
	void error(GameEvent* gameEvent);
	void disconnect(GameEvent* gameEvent);
	void addTeam(GameEvent* gameEvent);
	void moveCharacter(GameEvent* gameEvent);
	void dropMine(GameEvent* gameEvent);
	void mineHit(GameEvent* gameEvent);
	void throwMissile(GameEvent* gameEvent);
	void missileHit(GameEvent* gameEvent);
};

#endif // #ifndef __EventController_h_
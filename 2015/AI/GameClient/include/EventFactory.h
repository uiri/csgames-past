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

#ifndef __EventFactory__
#define __EventFactory__

#include "GameEvent.h"
#include "NetUtility.h"
#include "QueueController.h"

class EventFactory
{
private:
	GameEvent* createEvent(std::string type);

public:
	EventFactory();
    virtual ~EventFactory();

	void generate(std::string message);
};

#endif // #ifndef __EventFactory__

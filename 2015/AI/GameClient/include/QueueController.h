/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** QueueController.h
** Manager that contains all the queue
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __QueueController_h_
#define __QueueController_h_

#include "GameEvent.h"

class QueueController
{
private:
	std::queue<std::string> messageQueue;
	std::queue<GameEvent*> gameEventQueue;

	// Don't implement for singleton
	QueueController(QueueController const&);
    void operator=(QueueController const&);

public:
	QueueController();
    static QueueController& getInstance()
    {
        static QueueController instance;
        return instance;
    }

	void addMessage(std::string message);
	std::string getMessage();
	bool isMessageQueueEmpty();

	void addEvent(GameEvent*);
	GameEvent* getEvent();
	bool isGameEventQueueEmpty();
};

#endif // #ifndef __Map_h_

/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetPlayerController.h
** Controller that manage all the network player information
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __NetPlayerController_h_
#define __NetPlayerController_h_

#include "NetPlayer.h"

#define MAX_PLAYER 2

class NetPlayerController
{
private:
	std::queue<std::string>* messageQueue;
	std::map<int, NetPlayer*> netPlayers;

public:
	NetPlayerController(std::queue<std::string>* messageQueue);
	~NetPlayerController();

	void addPlayer(int id, char* playerName, char* characterNames[maxCharacter]);
	void quitPlayer(int id);
	void moveCharacter(int playerId, int characterId, double x, double y);
};

#endif // #ifndef __NetPlayerController_h_
/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** GameMap.h
** Map that contain all the objet
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __GameMap_h_
#define __GameMap_h_

#include <iostream>
#include <map>

#include "Player.h"

class GameMap
{
public:
	std::map<int, Player*> players;
	int yourId;
	int opponentId;
	std::string playerName;
	std::string characterNames[maxCharacter];

	GameMap(std::string playerName, std::string characterNames[maxCharacter]);
	~GameMap();
	void printSelf();
	void addPlayer(int id);
	void quitPlayer(int id);
	void moveCharacter(int playerId, int characterId, double x, double y);

	// Getter & Setters
	void setYourID(int id);
};

#endif // #ifndef __GameMap_h_
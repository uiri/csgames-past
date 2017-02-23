/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Player.h
** The player that controle a character team
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __Player_h_
#define __Player_h_

#include <iostream>
#include <map>

#include "Character.h"

#define maxCharacter 2

class Player
{
private:
	std::string tagName;

public:
	std::map<int, Character*> characters;
	Player();
	Player(std::string tagName, std::string characterNames[maxCharacter]);
	~Player();
	void printSelf();
	void moveCharacter(int id, double x, double z);
};

#endif // #ifndef __Player_h_
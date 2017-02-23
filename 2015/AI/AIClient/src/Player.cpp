/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Player.cpp
** Implementation of the Player
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "Player.h"

Player::Player()
{
	this->tagName = "NoName";

	for(int i = 0; i < maxCharacter; ++i)
	{
		characters[i] = new Character("NoName", 0, 0);
	}
}

Player::Player(std::string tagName, std::string characterNames[maxCharacter])
{
	this->tagName = "NoName";

	for(int i = 0; i < maxCharacter; ++i)
	{
		characters[i] = new Character(characterNames[i], 0, 0);
	}
}

Player::~Player()
{
	for(int i = 0; i < maxCharacter; ++i)
	{
		if(characters[i])
		{
			delete characters[i];
		}
	}
}

void Player::moveCharacter(int id, double x, double y)
{
	characters[id]->moveCharacter(x, y);
}

void Player::printSelf()
{
	std::cout << "Player: " << tagName.c_str() << std::endl;

	for( int i=0; i<maxCharacter; ++i)
	{
		characters[i]->printSelf();
	}
}
/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Team.h
** Team that control some characters
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __Team_h_
#define __Team_h_

#include "Character.h"

class Team
{
private:
	int id;
	std::string name;

	int characterCount;
	Character* characters[MAX_CHARACTER_PER_TEAM];

public:
	Team(std::string name, int id);
	virtual ~Team();

	// Getters
	Character* getCharacter(int characterId);
	int getId();
	std::string getName();
	bool isAlive();

	// Action
	void characterHit(int characterId);
	void addCharacter(Character* character);
	void addTime(Ogre::Real deltaTime, Ogre::Camera* camera);
	void deactivate();
};

#endif
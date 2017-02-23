/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Team.cpp
** Implementation of the NetTeam
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "Team.h"

Team::Team(std::string name, int teamId)
{
	this->name = name;
	this->id = teamId;
	characterCount = 0;

	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		characters[i] = NULL;
	}
}

Team::~Team()
{
	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		if(characters[i])
		{
			delete characters[i];
		}
	}
}

void Team::addCharacter(Character* character)
{
	characters[characterCount++] = character;
}

Character* Team::getCharacter(int characterId)
{
	if(characterId < MAX_CHARACTER_PER_TEAM)
		return characters[characterId];
	else
		return NULL;
}

void Team::addTime(Ogre::Real deltaTime, Ogre::Camera* camera)
{
	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		if(characters[i])
		{
			characters[i]->addTime(deltaTime, camera);
		}
	}
}

int Team::getId()
{
	return id;
}

std::string Team::getName()
{
	return name;
}

bool Team::isAlive()
{
	return characterCount > 0;
}

void Team::characterHit(int characterId)
{
	Character* hitCharacter = getCharacter(characterId);
	if(hitCharacter && hitCharacter->isAlive())
	{
		hitCharacter->hit();
		if(!hitCharacter->isAlive())
		{
			--characterCount;
		}
	}
}

void Team::deactivate()
{
	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		if(characters[i])
		{
			characters[i]->deactivate();
		}
	}
}

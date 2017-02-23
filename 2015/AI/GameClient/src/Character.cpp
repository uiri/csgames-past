/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Character.cpp
** Implementation of the Character
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "Character.h"

Character::Character(Ogre::SceneNode* bodyNode, Mine* mine, Missile* missile, TextOverlay* nameOverlay, TextOverlay* lifeOverlay, std::string name, int teamId, int characterId)
{
	// Network
	this->teamId = teamId;
	this->characterId = characterId;

	// 3d Infos
	TANK_MESH_HEIGHT = 2.5;
	this->bodyNode = bodyNode;
	this->position = Map::getInstance().getStartingPosition(teamId, characterId);
	this->lastPosition = this->position;
	Map::getInstance().setTile(this->position, MapEntity::CHARACTER, this->teamId, this->characterId);

	this->targetPosition = this->position;
	Ogre::Vector3 startingVector = this->position.toOgreVector3(TANK_MESH_HEIGHT);
	this->bodyNode->setPosition(startingVector);
	this->subStepPosition = startingVector;

	// Character Infos
	this->name = name;
	this->mine = mine;
	this->missile = missile;
	this->nameOverlay = nameOverlay;
	this->lifeOverlay = lifeOverlay;

	this->askForMine = false;
	this->askForMissile = false;
	this->timeToWait = 0.0;
	this->life = 3;
	this->disable = false;

	char numstr[21];
	sprintf(numstr, "%d", this->life);
	std::string text = "Life: ";
	text += numstr;

	this->lifeOverlay->setText(text);

	//Debug
	toggleDebugFlag = false;
}

Character::~Character()
{
	if(mine)
		delete mine;

	if(missile)
		delete missile;

	if(nameOverlay)
		delete nameOverlay;

	if(lifeOverlay)
		delete lifeOverlay;
}

void Character::addTime(Ogre::Real deltaTime, Ogre::Camera* camera)
{
	if(!disable)
	{
		missile->addTime(deltaTime);
	}

	if(isAlive())
	{
		updateBody(deltaTime);
		nameOverlay->update(camera);
		lifeOverlay->update(camera);
	}
}

void Character::setTargetPosition(int x, int z)
{
	Vector2 newTarget(x, z);

	if(Map::getInstance().isPositionValid(newTarget) && !(newTarget == targetPosition))
	{
		this->targetPosition.x = x;
		this->targetPosition.y = z;
		lastPosition = position;
	}
}

void Character::updateBody(Ogre::Real deltaTime)
{
	if(bodyNode != NULL && !disable)
	{
		Ogre::Vector3 currentPosition = bodyNode->getPosition();
		Ogre::Vector3 goalDirection = subStepPosition - currentPosition;
		
		if(goalDirection.length() < Ogre::Real(1.0))
		{
			if(timeToWait > 0)
			{
				timeToWait -= deltaTime;
				goalDirection = Ogre::Vector3::ZERO;
			}
			else
			{
				if(askForMine)
				{
					dropMine();
					goalDirection = Ogre::Vector3::ZERO;
				}
				else if(askForMissile)
				{
					throwMissile();
					goalDirection = Ogre::Vector3::ZERO;
				}
				else if(position == targetPosition)
				{
					goalDirection = Ogre::Vector3::ZERO;
				}
				else
				{
					Vector2 newPosition = Map::getInstance().calculateNextStep(position, targetPosition, lastPosition);

					if(newPosition == position)
					{
						goalDirection = Ogre::Vector3::ZERO;
					}
					else
					{
						this->lastPosition = this->position;
						Map::getInstance().moveCharacterTile(position, newPosition);
						position = newPosition;
						sendPosition();

						subStepPosition = position.toOgreVector3(TANK_MESH_HEIGHT);
						goalDirection = subStepPosition - currentPosition;
					}
				}
			}
		}

		if(goalDirection != Ogre::Vector3::ZERO)
		{
			// Calculate direction
			goalDirection.normalise();
			Ogre::Quaternion currentDirection = bodyNode->getOrientation().zAxis().getRotationTo(goalDirection);

			// Find the rotation in yaw
			Ogre::Real yawToGoal = currentDirection.getYaw().valueDegrees();

			bodyNode->yaw(Ogre::Degree(yawToGoal));

			bodyNode->translate(0, 0, deltaTime * CHARACTER_WALK_SPEED, Ogre::Node::TS_LOCAL);

			if(toggleDebugFlag)
			{
				std::cout << "yawToGoal:" << Ogre::Degree(yawToGoal) << std::endl;
				std::cout << "goalDirection:" << goalDirection << std::endl;
			}
		}
	}
}

int Character::getId()
{
	return characterId;
}

std::string Character::getName()
{
	return name;
}

void Character::sendPosition()
{
	std::string message = NetUtility::generateMoveCharacterMessage(teamId, characterId, position.x, position.y);
	QueueController::getInstance().addMessage(message);
}

bool Character::isMineReady()
{
	return !mine->isVisible();
}

void Character::askMine()
{
	askForMine = true;
}

void Character::dropMine()
{
	askForMine = false;
	if(mine && isMineReady())
	{
		Map::getInstance().setTile(position, MapEntity::CHARACTER_MINE, teamId, characterId);
		mine->setPosition(position);
		mine->setVisible(true);
	}
}

void Character::throwMissile()
{
	askForMissile = false;
	if(missile && isMissileReady() && timeToWait <= 0)
	{
		timeToWait = 1.0;
		missile->launch();

		Ogre::Vector3 goalDirection = MapDirection::DirectionToVector(missile->getDirection());
		Ogre::Quaternion currentDirection = bodyNode->getOrientation().zAxis().getRotationTo(goalDirection);

		// Find the rotation in yaw
		Ogre::Real yawToGoal = currentDirection.getYaw().valueDegrees();

		bodyNode->yaw(Ogre::Degree(yawToGoal));
	}
}

Mine* Character::getMine()
{
	return mine;
}

bool Character::isMissileReady()
{
	return !missile->isVisible();
}

void Character::askMissile(int direction)
{
	askForMissile = true;
	if(missile && isMissileReady())
	{
		missile->init(position,static_cast<MapDirection::MapDirection>(direction));
	}
}

Missile* Character::getMissile()
{
	return missile;
}

void Character::hit()
{
	if(isAlive())
	{
		--life;

		if(!isAlive())
		{
			die();
		}
		else
		{
			char numstr[21];
			sprintf(numstr, "%d", life);
			std::string text = "Life: ";
			text += numstr;

			this->lifeOverlay->setText(text);
		}
	}
}

bool Character::isAlive()
{
	return life > 0;
}

bool Character::isVisible()
{
	return bodyNode->getAttachedObject(name)->isVisible();
}

void Character::die()
{
	bodyNode->setVisible(false);
	lifeOverlay->hide();
	nameOverlay->hide();
	
	if(Map::getInstance().getTileType(position) == MapEntity::CHARACTER_MINE)
	{
		Map::getInstance().getTile(position)->type = MapEntity::MINE;
	}
	else
	{
		Map::getInstance().setTile(position, MapEntity::EMPTY, 0, 0);
	}
}

void Character::deactivate()
{
	disable = true;
}

void Character::ToggleDebugFlag()
{
	toggleDebugFlag = !toggleDebugFlag;
}

Vector2 Character::getPosition()
{
	return position;
}
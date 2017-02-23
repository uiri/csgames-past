/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Character.h
** The Character that is controlled by the AI
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __Character_h_
#define __Character_h_

#include "TextOverlay.h"
#include "NetUtility.h"
#include "Map.h"
#include "Mine.h"
#include "Missile.h"
#include "QueueController.h"

class Character
{

private:
	// Character infos
	int teamId;
	int characterId;
	std::string name;
	int life;
	bool disable;

	// Action infos
	bool askForMine;
	bool askForMissile;
	Mine* mine;
	Missile* missile;
	Ogre::Real timeToWait;

	// 3D world infos
	Vector2 position;
	Vector2 lastPosition;
	Vector2 targetPosition;
	Ogre::Vector3 subStepPosition;
	Ogre::Real TANK_MESH_HEIGHT;

	// 3D world components
	Ogre::SceneNode* bodyNode;
	TextOverlay* nameOverlay;
	TextOverlay* lifeOverlay;

	//Debug flag
	bool toggleDebugFlag;

	void updateBody(Ogre::Real deltaTime);
	void dropMine();
	void throwMissile();
	void die();

public:
	Character(Ogre::SceneNode* bodyNode, Mine* mine, Missile* missile, TextOverlay* nameOverlay, TextOverlay* lifeOverlay, std::string name, int teamId, int characterId);
	virtual ~Character();

	void addTime(Ogre::Real deltaTime, Ogre::Camera* camera);

	// Getters
	int getId();
	std::string getName();
	bool isMineReady();
	bool isMissileReady();
	Mine* getMine();
	Missile* getMissile();
	bool isVisible();
	bool isAlive();
	Vector2 getPosition();

	// Setters
	void setTargetPosition(int x, int z);

	// Actions
	void askMine();
	void askMissile(int direction);
	void hit();
	void sendPosition();
	void deactivate();

	// Debug
	void ToggleDebugFlag();
};

#endif
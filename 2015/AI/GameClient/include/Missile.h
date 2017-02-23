/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Missile.h
** Missile that player can shoot
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __Missile_h_
#define __Missile_h_

#include "Map.h"

class Missile
{
private:
	// Missile Infos
	Ogre::Real MISSILE_MESH_HEIGHT;
	std::string name;
	Vector2 lastPosition;
	Vector2 position;
	Vector2 targetPosition;
	Ogre::Vector3 subStepPosition;
	MapDirection::MapDirection direction;
	int teamId, characterId;
	
	// 3D world components
	Ogre::SceneNode* bodyNode;
	void updateBody(Ogre::Real deltaTime);

public:
	Missile(Ogre::SceneNode* bodyNode, std::string name, int teamId, int characterId);
	virtual ~Missile() {}

	void addTime(Ogre::Real deltaTime);
	void sendPosition();
	void init(Vector2 position, MapDirection::MapDirection direction);
	Vector2 calculateTargetPosition(MapDirection::MapDirection direction);
	void launch();

	void setVisible(bool visible);
	bool isVisible();

	Vector2 calculateNextStep();
	MapDirection::MapDirection getDirection();
	Vector2 getPosition();
	void hitWall();
};

#endif // #ifndef __Missile_h_
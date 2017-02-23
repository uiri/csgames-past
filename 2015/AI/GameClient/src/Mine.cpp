/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Mine.cpp
** Implementation of the mine
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "Mine.h"

Mine::Mine(Ogre::SceneNode* bodyNode, std::string mineName)
{
	// 3d Infos
	MINE_MESH_HEIGHT = 0.0;
	this->bodyNode = bodyNode;
	this->name = mineName;
}

void Mine::setPosition(Vector2 position)
{
	Ogre::Vector3 newposition = position.toOgreVector3(MINE_MESH_HEIGHT);
	bodyNode->setPosition(newposition);
}

void Mine::setVisible(bool visible)
{
	bodyNode->setVisible(visible);
}

bool Mine::isVisible()
{
	return bodyNode->getAttachedObject(name)->isVisible();
}

/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Mine.h
** A mine that could be drop by tank
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __Mine_h_
#define __Mine_h_

#include "Map.h"

class Mine
{

private:
	Ogre::Real MINE_MESH_HEIGHT;
	Ogre::SceneNode* bodyNode;
	std::string name;

public:
	Mine(Ogre::SceneNode* bodyNode, std::string mineName);
	virtual ~Mine() {}
	void setPosition(Vector2 position);
	void setVisible(bool visible);
	bool isVisible();
};

#endif // #ifndef __Mine_h_
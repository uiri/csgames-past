/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** Map.h
** Map that containt the position of all entity
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __Map_h_
#define __Map_h_

#include "QueueController.h"
#include "NetUtility.h"
#include <cmath>

#define MAP_TILE_SIZE 20

#define HIGHEST_SCORE MAP_HEIGHT + MAP_WIDTH

namespace MapEntity
{
	enum MapEntity{EMPTY, BOX, CHARACTER, CHARACTER_MINE, MINE, MISSILE};
}

namespace MapDirection
{
	enum MapDirection{UP, DOWN, LEFT, RIGHT};

	static int DirectionToDegree(MapDirection direction)
	{
		if(direction == MapDirection::UP)
			return 90;
		else if(direction == MapDirection::DOWN)
			return 270;
		else if(direction == MapDirection::LEFT)
			return 0;
		else if(direction == MapDirection::RIGHT)
			return 180;
		return 0;
	}

	static Ogre::Vector3 DirectionToVector(MapDirection direction)
	{
		if(direction == MapDirection::UP)
			return Ogre::Vector3(0, 0, 1);
		else if(direction == MapDirection::DOWN)
			return Ogre::Vector3(0, 0, -1);
		else if(direction == MapDirection::LEFT)
			return Ogre::Vector3(1, 0, 0);
		else if(direction == MapDirection::RIGHT)
			return Ogre::Vector3(-1, 0, 0);
		return Ogre::Vector3(0, 0, 0);
	}
}

struct Vector2
{
	int x;
	int y;

	Vector2()
	{
		this->x = 0;
		this->y = 0;
	}

	Vector2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	bool operator==(Vector2 const& vector) const
	{
		if(x == vector.x && y == vector.y)
			return true;
		else
			return false;
	}

	Ogre::Vector3 toOgreVector3(Ogre::Real z)
	{
		return Ogre::Vector3( Ogre::Real(-x*MAP_TILE_SIZE), z, Ogre::Real(y*MAP_TILE_SIZE));
	}

	int distance(Vector2 const& vector)
	{
		return std::abs(vector.x - this->x) + std::abs(vector.y - this->y); 
	}
};

struct MapTile
{
	MapEntity::MapEntity type;
	int teamId;
	int characterId;

	MapTile()
	{
		type = MapEntity::EMPTY;
		teamId = 0;
		characterId = 0;
	}
};


class Map
{
private:
	MapTile map[MAP_HEIGHT][MAP_WIDTH];

	// Don't implement for singleton
	Map(Map const&);
    void operator=(Map const&);

public:
	Map();
    static Map& getInstance()
    {
        static Map instance;
        return instance;
    }

	MapEntity::MapEntity getTileType(const Vector2& position);
	MapTile* getTile(const Vector2& position);
	void setTile(const Vector2& position, MapEntity::MapEntity value, int teamId, int characterId);
	
	Vector2 calculateNextStep(const Vector2& currentPosition, const Vector2& targetPosition, const Vector2& lastPosition);
	int calculateLowestDirectionScore(const Vector2& position, const Vector2& targetPosition, const Vector2& lastPosition);
	int calculateScore(const Vector2& position, const Vector2& targetPosition, const Vector2& lastPosition);
	bool isTileEmpty(const Vector2& position);
	bool isPositionValid(const Vector2& position);
	Vector2 leftTile(const Vector2& position);
	Vector2 rightTile(const Vector2& position);
	Vector2 upTile(const Vector2& position);
	Vector2 downTile(const Vector2& position);

	void moveCharacterTile(const Vector2& position, const Vector2& newPosition);
	void moveMissileTile(const Vector2& position, const Vector2& newPosition);
	Vector2 getStartingPosition(int teamId, int characterId);

	// Debug functions
	void print();
};

#endif // #ifndef __Map_h_

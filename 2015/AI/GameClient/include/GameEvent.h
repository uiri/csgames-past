/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** GameEvent.h
** All the event that can happen in a game
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __GameEvent_h_
#define __GameEvent_h_

#include "NetUtility.h"

namespace EventType
{
	enum EventType{ NONE, ERROR_MESSAGE, DISCONNECT, ADD_TEAM, MOVE_CHARACTER,
					DROP_MINE, MINE_HIT, THROW_MISSILE, MISSILE_HIT};
}

struct GameEvent
{
	int convertCharToNumeral(std::string token);

	virtual EventType::EventType getType() {return EventType::NONE;}
	virtual bool fill(std::string arguments) {return false;}
};

struct ErrorEvent : GameEvent
{
	std::string message;

	ErrorEvent() {}
	virtual ~ErrorEvent() {}

	virtual EventType::EventType getType() {return EventType::ERROR_MESSAGE;}
	virtual bool fill(std::string arguments);
};

struct DisconnectEvent : GameEvent
{
	int teamId;

	DisconnectEvent() {}
	virtual ~DisconnectEvent() {}

	virtual EventType::EventType getType() {return EventType::DISCONNECT;}
	virtual bool fill(std::string arguments);
};

struct AddTeamEvent : public GameEvent
{
	int teamId;
	std::string teamName;
	std::string characterNames[MAX_CHARACTER_PER_TEAM];

	AddTeamEvent() {}
	virtual ~AddTeamEvent() {}

	virtual EventType::EventType getType() {return EventType::ADD_TEAM;}
	virtual bool fill(std::string arguments);
};

struct MoveCharacterEvent : public GameEvent
{
	int positionX, positionZ, characterId, teamId;

	MoveCharacterEvent() {}
	virtual ~MoveCharacterEvent() {}

	virtual EventType::EventType getType() {return EventType::MOVE_CHARACTER;}
	virtual bool fill(std::string arguments);
};

struct DropMineEvent : public GameEvent
{
	int characterId, teamId;

	DropMineEvent() {}
	virtual ~DropMineEvent() {}

	virtual EventType::EventType getType() {return EventType::DROP_MINE;}
	virtual bool fill(std::string arguments);
};

struct MineHitEvent : public GameEvent
{
	int hitTeamId, hitCharacterId, originTeamId, originCharacterId;

	MineHitEvent(int hitPlayerId, int hitCharacterId, int originPlayerId, int originCharacterId);
	MineHitEvent() {}
	virtual ~MineHitEvent() {}

	virtual EventType::EventType getType() {return EventType::MINE_HIT;}
};

struct ThrowMissileEvent : public GameEvent
{
	int characterId, direction, teamId;

	ThrowMissileEvent() {}
	virtual ~ThrowMissileEvent() {}

	virtual EventType::EventType getType() {return EventType::THROW_MISSILE;}
	virtual bool fill(std::string arguments);
};

namespace HitEntity
{
	enum HitEntity{NONE, CHARACTER, MINE, MISSILE};
}

struct MissileHitEvent : public GameEvent
{
	int hitTeamId, hitCharacterId, originTeamId, originCharacterId;
	HitEntity::HitEntity entity;

	MissileHitEvent(HitEntity::HitEntity entity, int hitPlayerId, int hitCharacterId, int originPlayerId, int originCharacterId);
	MissileHitEvent() {}
	virtual ~MissileHitEvent() {}

	virtual EventType::EventType getType() {return EventType::MISSILE_HIT;}
};

#endif // #ifndef __GameEvent_h_

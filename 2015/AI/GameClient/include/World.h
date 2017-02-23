/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** World.h
** World that contains all the information on the game
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __World_h_
#define __World_h_

#include "TextOverlay.h"
#include "Team.h"
#include "QueueController.h"

class World
{
private:
	Team* teams[MAX_TEAM];
	int teamCount;

	bool gameStarted;

	Ogre::Overlay* labelOverlay;
	Ogre::SceneManager* sceneManager;

	Ogre::OverlayContainer* panel;
	Ogre::TextAreaOverlayElement* textElement;

	TextOverlay* nameOverlay[3];

	// Don't implement for singleton
	World(World const&);
    void operator=(World const&);

	void generateMapDelimiter();
	void sendGameInfos();
	void startGame();
	void sendAllPosition();
	void generateMap();
	void sendMap();

	void endGame();
	Team* findWiningTeam();
	void showMessage(std::string message);

public:
	World();
	virtual ~World();
	void init(Ogre::SceneManager* sceneManager);

	static World& getInstance()
    {
        static World instance;
        return instance;
    }

	void createScene();
	void addTime(Ogre::Real deltaTime);
	
	// Event action
	void addTeam(int teamId, std::string teamName, std::string characterNames[MAX_CHARACTER_PER_TEAM]);
	void removeTeam(int teamId);

	void mineHit(int mineTeamId, int mineCharacterId);
	void missileHit(int missileTeamId, int missileCharacterId, bool backfire);
	void characterHit(int hitTeamId, int hitCharacterId);

	// Getters
	Team* getTeam(int teamId);
	bool isGameStarted();

	//Debug functions
	void printMap();
	void toggleDebugFlag();
};

#endif // #ifndef __World_h_
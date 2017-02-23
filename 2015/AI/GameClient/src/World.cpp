/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** World.cpp
** Implementation of the World
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "World.h"

const char* TANK_MESH_NAME = "Tank.mesh";
const char* MINE_MESH_NAME = "Mine.mesh";
const char* MISSILE_MESH_NAME = "Missile.mesh";

World::World()
{
	this->sceneManager = NULL;
	teamCount = 0;

	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		teams[i] = NULL;
	}

	this->gameStarted = false;
}

World::~World()
{
	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		if(teams[i])
		{
			delete teams[i];
		}
	}

	for(int x = 0; x < 3; ++x)
	{
		if(nameOverlay[x])
		{
			delete nameOverlay[x];
		}
	}
}

void World::init(Ogre::SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;
}

void World::createScene()
{
	// Set the scene's ambient light
	sceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	// Create a Light and set its position
	Ogre::Light* light = sceneManager->createLight("MainLight");
	light->setPosition(Vector2(-2, -2).toOgreVector3(Ogre::Real(80.0)));

	light = sceneManager->createLight("MainLight2");
	light->setPosition(Vector2(-2, MAP_HEIGHT).toOgreVector3(Ogre::Real(80.0)));

	light = sceneManager->createLight("MainLight3");
	light->setPosition(Vector2(MAP_WIDTH, -2).toOgreVector3(Ogre::Real(80.0)));

	light = sceneManager->createLight("MainLight4");
	light->setPosition(Vector2(MAP_WIDTH, MAP_HEIGHT).toOgreVector3(Ogre::Real(80.0)));

	sceneManager->setSkyDome(true, "Examples/CloudySky", 5, 8);

	// create a floor mesh resource
	Ogre::MeshManager::getSingleton().createPlane("floor", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
												  Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 1000.0, 1000.0,
												  10, 10, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);

	// create a floor entity, give it a material, and place it at the origin
	Ogre::SceneNode* floorNode = sceneManager->getRootSceneNode()->createChildSceneNode();
	Ogre::Entity* floor = sceneManager->createEntity("Floor", "floor");
	floor->setMaterialName("SceneMaterial/FloorSand");
	floor->setCastShadows(false);
	floorNode->attachObject(floor);
	floorNode->setPosition(87.5, 0.0, 87.5);

	labelOverlay = Ogre::OverlayManager::getSingleton().create("labelOverlay");

	generateMapDelimiter();
	generateMap();
}

void World::addTeam(int teamId, std::string teamName, std::string characterNames[MAX_CHARACTER_PER_TEAM])
{
	if(teamId == 0 || teamCount > 1)
		return;

	Team* team = new Team(teamName, teamId);
	teams[teamCount++] = team;

	for(int i = 0; i < MAX_CHARACTER_PER_TEAM; ++i)
	{
		char idstr[21];
		sprintf(idstr, "%d%d", teamId, i);
		
		std::string characterName = characterNames[i] + idstr;
		Ogre::SceneNode* bodyNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		Ogre::Entity* entity = sceneManager->createEntity(characterName, TANK_MESH_NAME);
		bodyNode->attachObject(entity);

		std::string mineName = "mine_" + characterNames[i] + idstr;
		Ogre::SceneNode* mineNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		Ogre::Entity* mineEntity = sceneManager->createEntity(mineName, MINE_MESH_NAME);
		mineNode->attachObject(mineEntity);
		mineNode->setScale(Ogre::Vector3(2.0, 2.0, 2.0));
		mineNode->setVisible(false);

		std::string missileName = "missile_" + characterNames[i] + idstr;
		Ogre::SceneNode* missileNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		Ogre::Entity* missileEntity = sceneManager->createEntity(missileName, MISSILE_MESH_NAME);
		missileNode->attachObject(missileEntity);
		missileNode->setVisible(false);

		Mine* mine = new Mine(mineNode, mineName);
		Missile* missile = new Missile(missileNode, missileName, teamId, i);
		TextOverlay* nameOverlay = new TextOverlay(labelOverlay, characterNames[i], characterName, bodyNode, sceneManager->getCamera("PlayerCam")->getViewport());
		TextOverlay* lifeOverlay = new TextOverlay(labelOverlay, "Life: ", "Life_" + characterNames[i]+ idstr, bodyNode, sceneManager->getCamera("PlayerCam")->getViewport(), Ogre::Vector3::UNIT_Y*15.0);
		lifeOverlay->setColors(Ogre::ColourValue(1.0, 0.25, 0.25), Ogre::ColourValue(1.0, 0.25, 0.25));

		Character* character = new Character(bodyNode, mine, missile, nameOverlay, lifeOverlay, characterNames[i], teamId, i);
		team->addCharacter(character);
	}

	if(teamCount == MAX_TEAM)
	{
		sendGameInfos();
		sendMap();
		sendAllPosition();
		startGame();
	}
}

void World::removeTeam(int teamId)
{
	//Do nothing just wait for the game to end
}

Team* World::getTeam(int teamId)
{
	for(int i = 0; i < MAX_TEAM; ++i)
	{
		if(teams[i] && teams[i]->getId() == teamId)
		{
			return teams[i];
		}
	}
	return NULL;
}

void World::addTime(Ogre::Real deltaTime)
{
	for(int i = 0; i < MAX_TEAM; ++i)
	{
		if(teams[i])
		{
			teams[i]->addTime(deltaTime, sceneManager->getCamera("PlayerCam"));
		}
	}

	for(int x = 0; x < 3; ++x)
	{
		if(nameOverlay[x])
		{
			nameOverlay[x]->update(sceneManager->getCamera("PlayerCam"));
		}
	}
}

void World::sendGameInfos()
{
	gameStarted = true;

	int teamsId[MAX_TEAM];
	for(int i = 0; i < MAX_TEAM; ++i)
	{
		teamsId[i] = teams[i]->getId();
	}

	std::string message = NetUtility::generateSendGameInfosMessage(teamsId);
	QueueController::getInstance().addMessage(message);
}

void World::startGame()
{
	gameStarted = true;

	std::string message = NetUtility::generateStartGameMessage();
	QueueController::getInstance().addMessage(message);
}

void World::sendAllPosition()
{
	for(int teamIndex = 0; teamIndex < MAX_TEAM; ++teamIndex)
	{
		for(int characterIndex = 0; characterIndex < MAX_CHARACTER_PER_TEAM; ++characterIndex)
		{
			teams[teamIndex]->getCharacter(characterIndex)->sendPosition();
		}
	}
}

void World::characterHit(int hitTeamId, int hitCharacterId)
{
	Team* hitTeam = getTeam(hitTeamId);
	if(hitTeam && hitTeam->isAlive())
	{
		hitTeam->characterHit(hitCharacterId);
		if(!hitTeam->isAlive())
		{
			--teamCount;
			if(teamCount < 2)
			{
				endGame();
			}
		}
	}
}

void World::mineHit(int mineTeamId, int mineCharacterId)
{
	Team* team = getTeam(mineTeamId);
	if(team)
	{
		Character* character = team->getCharacter(mineCharacterId);
		if(character)
		{
			character->getMine()->setVisible(false);
		}
	}
}

void World::missileHit(int missileTeamId, int missileCharacterId, bool backfire)
{
	Character* character = getTeam(missileTeamId)->getCharacter(missileCharacterId);
	Missile* missile = character->getMissile();
	missile->setVisible(false);

	// We shot near our position
	if(backfire)
	{
		characterHit(missileTeamId, missileCharacterId);
	}
}

void World::generateMap()
{
	Map& map = Map::getInstance();
	Ogre::Vector3 scaleVector(2.0, 2.0, 2.0);
	char numstr[21]; // Enough to hold all numbers up to 64-bits
	sprintf(numstr, "%d", MAX_TEAM);

	for(int x = 0; x < MAP_WIDTH; ++x)
	{
		for(int y = 0; y < MAP_HEIGHT; ++y)
		{
			Vector2 tilePosition(x, y);
			if(map.getTileType(tilePosition) == MapEntity::BOX)
			{
				sprintf(numstr, "%d%d", x, y);
				std::string name = "box_";
				name += numstr;

				Ogre::SceneNode* crateNode = sceneManager->getRootSceneNode()->createChildSceneNode();
				Ogre::Entity* crate = sceneManager->createEntity(name, "WoodCrate.mesh");
				crateNode->attachObject(crate);
				crateNode->setScale(scaleVector);
				crateNode->setPosition(tilePosition.toOgreVector3(Ogre::Real(10.0)));
			}
		}
	}
}

void World::sendMap()
{
	Map& map = Map::getInstance();
	char numstr[21]; // Enough to hold all numbers up to 64-bits
	for(int x = 0; x < MAP_WIDTH; ++x)
	{
		for(int y = 0; y < MAP_HEIGHT; ++y)
		{
			if(map.getTileType(Vector2(x, y)) == MapEntity::BOX)
			{
				std::string message = NetUtility::generateUpdateBoxMessage(x, y);
				QueueController::getInstance().addMessage(message);
			}
		}
	}
}

void World::generateMapDelimiter()
{
	char numstr[21]; // Enough to hold all numbers up to 64-bits
	Ogre::Vector3 scaleVector(2.0, 2.0, 2.0);

	for(int x = -1; x < MAP_WIDTH + 1; ++x)
	{
		sprintf(numstr, "%d", x);
		std::string name = "delimiter_down_";
		name += numstr;

		Ogre::SceneNode* crateNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		Ogre::Entity* crate = sceneManager->createEntity(name, "WoodCrate.mesh");
		crateNode->attachObject(crate);
		crateNode->setScale(scaleVector);
		crateNode->setPosition(Vector2(x,-1).toOgreVector3(Ogre::Real(10.0)));

		if(x == -1)
			nameOverlay[0] = new TextOverlay(labelOverlay, "O", "axes_origin", crateNode, sceneManager->getCamera("PlayerCam")->getViewport());
		if(x == MAP_WIDTH -1)
			nameOverlay[1] = new TextOverlay(labelOverlay, "X = 8", "X = 8", crateNode, sceneManager->getCamera("PlayerCam")->getViewport());

		sprintf(numstr, "%d", x);
		name = "delimiter_up_";
		name += numstr;

		crateNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		crate = sceneManager->createEntity(name, "WoodCrate.mesh");
		crateNode->attachObject(crate);
		crateNode->setScale(scaleVector);
		crateNode->setPosition(Vector2(x,MAP_HEIGHT).toOgreVector3(Ogre::Real(10.0)));
	}

	for(int y = 0; y < MAP_HEIGHT; ++y)
	{
		sprintf(numstr, "%d", y);
		std::string name = "delimiter_left_";
		name += numstr;

		Ogre::SceneNode* crateNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		Ogre::Entity* crate = sceneManager->createEntity(name, "WoodCrate.mesh");
		crateNode->attachObject(crate);
		crateNode->setScale(scaleVector);
		crateNode->setPosition(Vector2(-1,y).toOgreVector3(Ogre::Real(10.0)));

		if(y == MAP_HEIGHT -1)
			nameOverlay[2] = new TextOverlay(labelOverlay, "Y = 8", "Y = 8", crateNode, sceneManager->getCamera("PlayerCam")->getViewport());

		sprintf(numstr, "%d", y);
		name = "delimiter_right_";
		name += numstr;

		crateNode = sceneManager->getRootSceneNode()->createChildSceneNode();
		crate = sceneManager->createEntity(name, "WoodCrate.mesh");
		crateNode->attachObject(crate);
		crateNode->setScale(scaleVector);
		crateNode->setPosition(Vector2(MAP_WIDTH,y).toOgreVector3(Ogre::Real(10.0)));
	}
}

bool World::isGameStarted()
{
	return gameStarted;
}

void World::endGame()
{
	Team* winingTeam = findWiningTeam();

	if(winingTeam)
	{
		winingTeam->deactivate();

		std::string winingMessage = "Winner : ";
		winingMessage += winingTeam->getName();
		showMessage(winingMessage);
	}
	else
	{
		std::string winingMessage = "Tie : No winner";
		showMessage(winingMessage);
	}

	std::string message = NetUtility::generateEndGameMessage();
	QueueController::getInstance().addMessage(message);
}

Team* World::findWiningTeam()
{
	for(int teamIndex = 0; teamIndex < MAX_TEAM; ++teamIndex)
	{
		if(teams[teamIndex]->isAlive())
			return teams[teamIndex];
	}
	return NULL;
}


void World::showMessage(std::string message)
{
	if(!this->panel)
	{
		this->panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", "MainPanel"));
		this->panel->setMetricsMode(Ogre::GMM_PIXELS);
		this->panel->setPosition(300, 100);
		this->panel->setDimensions(300, 120);

		this->textElement = new Ogre::TextAreaOverlayElement("Label_MainPanel");
		this->textElement->setMetricsMode(Ogre::GMM_PIXELS);
		this->textElement->setAlignment(Ogre::TextAreaOverlayElement::Center);
		this->textElement->setCharHeight(40);
		this->textElement->setFontName("SdkTrays/Caption");
		this->textElement->setColourBottom(Ogre::ColourValue(0.25, 1.0, 0.25));
		this->textElement->setColourTop(Ogre::ColourValue(0.25, 1.0, 0.25));
		this->textElement->setDimensions(300, 120);
		this->textElement->setPosition(0, 0);

		Ogre::Overlay* labelOverlay = Ogre::OverlayManager::getSingleton().create("main_label");

		this->panel->addChild(this->textElement);
		labelOverlay->add2D(this->panel);
		labelOverlay->show();
	}
	this->textElement->setCaption(message);
}

void World::printMap()
{
	Map::getInstance().print();
}

void World::toggleDebugFlag()
{
	teams[0]->getCharacter(0)->ToggleDebugFlag();
	/*
	for(int teamIndex = 0; teamIndex < MAX_TEAM; ++teamIndex)
	{
		for(int characterIndex = 0; characterIndex < MAX_CHARACTER_PER_TEAM; ++characterIndex)
		{
			teams[teamIndex]->getCharacter(characterIndex)->toggleDebugFlag();
		}
	}
	*/
}

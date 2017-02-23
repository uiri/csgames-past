/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** GameClientAppliaction.h
** implementation of the GameClientAppliaction
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "GameClientApplication.h"

GameClientApplication::GameClientApplication()
{
	cumulateTime = 0.0;
}

GameClientApplication::~GameClientApplication()
{
	networkController->close();
	if(networkController)
	{
		delete networkController;
		networkController = NULL;
	}

	if(eventController)
	{
		delete eventController;
		eventController = NULL;
	}
}

void GameClientApplication::createScene()
{
	mCameraMan->getCamera()->setPosition(Vector2(4, 4).toOgreVector3(Ogre::Real(300.0)));
	mCameraMan->getCamera()->pitch(Ogre::Radian(Ogre::Degree(-90)));
	mCameraMan->getCamera()->yaw(Ogre::Radian(Ogre::Degree(180)));
	World::getInstance().createScene();
}

bool GameClientApplication::setup()
{
	mRoot = new Ogre::Root(mPluginsCfg);

	setupResources();

	bool carryOn = configure();
	if (!carryOn) return false;

	chooseSceneManager();
	createCamera();
	createViewports();

	// Set default mipmap level (NB some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Create any resource listeners (for loading screens)
	createResourceListener();
	// Load resources
	loadResources();

	// Create world & controller
	eventController = new EventController();
	networkController = new NetworkController();
	networkController->init();
	World::getInstance().init(mSceneMgr);

	// Create the scene
	createScene();
	createFrameListener();

	mTrayMgr->hideAll();

	return true;
};

bool GameClientApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

    // Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();

	mTrayMgr->frameRenderingQueued(evt);

	eventController->executeAllGameEvent();

	if(World::getInstance().isGameStarted())
	{
		cumulateTime += evt.timeSinceLastFrame;
		while(cumulateTime > Ogre::Real(0.033))
		{
			World::getInstance().addTime(Ogre::Real(0.033));
			cumulateTime -= Ogre::Real(0.033);
		}
	}

    mCameraMan->frameRenderingQueued(evt);

    // Limit the FPS to 60
	Ogre::Real ttW = 1000.0 / 60.0 - 1000.0 * evt.timeSinceLastFrame;
	if (ttW > 0)
	{
	    boost::this_thread::sleep(boost::posix_time::milliseconds(ttW));
	}

	return true;
}

void GameClientApplication::createFrameListener(void)
{
	BaseApplication::createFrameListener();
}

bool GameClientApplication::keyPressed( const OIS::KeyEvent &arg )
{
	BaseApplication::keyPressed(arg);

	if (arg.key == OIS::KC_ESCAPE)
	{
		networkController->close();
		mShutDown = true;
	}
	else if (arg.key == OIS::KC_M)
	{
		World::getInstance().printMap();
	}
	else if (arg.key == OIS::KC_P)
	{
		World::getInstance().toggleDebugFlag();
	}

	return true;
}

bool GameClientApplication::keyReleased( const OIS::KeyEvent &arg )
{
	BaseApplication::keyReleased(arg);

	return true;
}

bool GameClientApplication::mouseMoved( const OIS::MouseEvent &arg )
{
	BaseApplication::mouseMoved(arg);

	return true;
}

bool GameClientApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	BaseApplication::mousePressed(arg, id);

	return true;
}

bool GameClientApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	BaseApplication::mouseReleased(arg, id);

	return true;
}

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
	int main(int argc, char *argv[])
#endif
	{
		// Create application object
		GameClientApplication app;

		try {
			app.go();
		} catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occured: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif

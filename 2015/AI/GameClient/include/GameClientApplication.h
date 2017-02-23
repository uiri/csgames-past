/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**         \/        \/             \/         \/         \/        \/        \/ 
**
** GameClientAppliaction.h
** The game client appliaction
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __GameClientApplication_h_
#define __GameClientApplication_h_

#include "BaseApplication.h"

#include "NetworkController.h"
#include "EventController.h"
#include "World.h"

class GameClientApplication : public BaseApplication
{
private:
	NetworkController* networkController;
	EventController* eventController;
	Ogre::Real cumulateTime;

public:
    GameClientApplication();
    virtual ~GameClientApplication();

protected:
    virtual void createScene();
	virtual bool setup();

    // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	virtual void createFrameListener();

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );

	// OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
};

#endif // #ifndef __GameClientAppliaction_h_

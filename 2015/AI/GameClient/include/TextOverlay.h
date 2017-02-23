/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** TextOverlay.h
** Text that can show over a mesh
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __TextOverlay_h_
#define __TextOverlay_h_

#include <OgreOverlay.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayElement.h>
#include <OgreTextAreaOverlayElement.h>

class TextOverlay
{
private:
	Ogre::OverlayContainer* panel;
	Ogre::TextAreaOverlayElement* textElement;
	Ogre::SceneNode* node;

	Ogre::Real screenWidth, screenHeight;
	Ogre::Vector2 screenPosition;
	Ogre::Vector3 offset;

public:
	TextOverlay(Ogre::Overlay* overlay, std::string text, std::string name, Ogre::SceneNode* node, Ogre::Viewport* viewport, Ogre::Vector3 offset = Ogre::Vector3::ZERO);
	virtual ~TextOverlay();

	void update(Ogre::Camera* camera);
	bool getNodeScreenSpaceCoords(Ogre::Camera* camera);
	void setColors(Ogre::ColourValue topColor, Ogre::ColourValue bottomColor);
	void setText(std::string text);
	void hide();
};

#endif // #ifndef __TextOverlay_h_

/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** TextOverlay.cpp
** Implementation of TextOverlay
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#include "stdafx.h"

#include "TextOverlay.h"

TextOverlay::TextOverlay(Ogre::Overlay* overlay, std::string text, std::string name, Ogre::SceneNode* node, Ogre::Viewport* viewport, Ogre::Vector3 offset)
{
	this->screenWidth = viewport->getActualWidth();
	this->screenHeight = viewport->getActualHeight();
	this->screenPosition = Ogre::Vector2::ZERO;
	this->offset = offset;

	this->node = node;

	this->panel = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement("Panel", name));
	this->panel->setMetricsMode(Ogre::GMM_PIXELS);
	this->panel->setPosition(-100, -100);
	this->panel->setDimensions(160, 70);

	this->textElement = new Ogre::TextAreaOverlayElement("Label_" + name);
	this->textElement->setCaption(text);
	this->textElement->setMetricsMode(Ogre::GMM_PIXELS);
	this->textElement->setAlignment(Ogre::TextAreaOverlayElement::Center);
	this->textElement->setCharHeight(15);
	this->textElement->setFontName("SdkTrays/Caption");
	this->textElement->setColourBottom(Ogre::ColourValue(0.25, 1.0, 0.25));
	this->textElement->setColourTop(Ogre::ColourValue(0.25, 1.0, 0.25));
	this->textElement->setDimensions(100, 50);
	this->textElement->setPosition(120,10);

	this->panel->addChild(this->textElement);
	overlay->add2D(panel);
	overlay->show();
}

TextOverlay::~TextOverlay()
{
	if(textElement)
	{
		//delete textElement;
	}
}

void TextOverlay::update(Ogre::Camera* camera)
{
	bool isInView = getNodeScreenSpaceCoords(camera);
	if(isInView)
	{
		Ogre::Real x = (screenWidth * screenPosition.x) - 125;
		Ogre::Real y = (screenHeight * screenPosition.y) + offset.y;
		panel->setPosition(x, y);
	}
}

bool TextOverlay::getNodeScreenSpaceCoords(Ogre::Camera* camera)
{
	if(!node->isInSceneGraph())
	{
		return false;
	}

	Ogre::Vector3 nodePosition = node->getPosition();
	Ogre::Plane cameraPlane = Ogre::Plane(camera->getDerivedOrientation().zAxis(), camera->getDerivedPosition());
	if(cameraPlane.getSide(nodePosition) != Ogre::Plane::NEGATIVE_SIDE)
		return false;

	nodePosition = camera->getProjectionMatrix() * ( camera->getViewMatrix() * nodePosition);
	screenPosition.x = (nodePosition.x / 2) + 0.5;
	screenPosition.y = 1 - ((nodePosition.y / 2) + 0.5);
	return true;
}

void TextOverlay::setColors(Ogre::ColourValue topColor, Ogre::ColourValue bottomColor)
{
	textElement->setColourTop(topColor);
	textElement->setColourBottom(bottomColor);
}

void TextOverlay::setText(std::string text)
{
	this->textElement->setCaption(text);
}

void TextOverlay::hide()
{
	this->panel->hide();
}

/*
 -----------------------------------------------------------------------------
 This source file is part of OGRE
 (Object-oriented Graphics Rendering Engine)
 For the latest info, see http://www.ogre3d.org/
 
 Copyright (c) 2000-2013 Torus Knot Software Ltd
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 -----------------------------------------------------------------------------
 */
#ifndef __SdkCameraMan_H__
#define __SdkCameraMan_H__

#include "Ogre.h"
#include <limits>

namespace OgreBites
{
	/*=============================================================================
	| Utility class for controlling the camera in samples.
	=============================================================================*/
	class SdkCameraMan
    {
    public:
		SdkCameraMan(Ogre::Camera* cam)
		: mCamera(0)
		, mTopSpeed(150)
		, mVelocity(Ogre::Vector3::ZERO)
		, mGoingForward(false)
		, mGoingBack(false)
		, mGoingLeft(false)
		, mGoingRight(false)
		, mGoingUp(false)
		, mGoingDown(false)
		, mFirstVue(false)
		{

			setCamera(cam);
		}

		virtual ~SdkCameraMan() {}

		/*-----------------------------------------------------------------------------
		| Swaps the camera on our camera man for another camera.
		-----------------------------------------------------------------------------*/
		virtual void setCamera(Ogre::Camera* cam)
		{
			mCamera = cam;
		}

		virtual Ogre::Camera* getCamera()
		{
			return mCamera;
		}

		/*-----------------------------------------------------------------------------
		| Sets the camera's top speed. Only applies for free-look style.
		-----------------------------------------------------------------------------*/
		virtual void setTopSpeed(Ogre::Real topSpeed)
		{
			mTopSpeed = topSpeed;
		}

		virtual Ogre::Real getTopSpeed()
		{
			return mTopSpeed;
		}

		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt)
		{
			// build our acceleration vector based on keyboard input composite
			Ogre::Vector3 accel = Ogre::Vector3::ZERO;
			if (mGoingForward) accel += mCamera->getDirection();
			if (mGoingBack) accel -= mCamera->getDirection();
			if (mGoingRight) accel += mCamera->getRight();
			if (mGoingLeft) accel -= mCamera->getRight();
			if (mGoingUp) accel += mCamera->getUp();
			if (mGoingDown) accel -= mCamera->getUp();

			// if accelerating, try to reach top speed in a certain time
			Ogre::Real topSpeed = mTopSpeed;
			if (accel.squaredLength() != 0)
			{
				accel.normalise();
				mVelocity += accel * topSpeed * evt.timeSinceLastFrame * 10;
			}
			// if not accelerating, try to stop in a certain time
			else mVelocity -= mVelocity * evt.timeSinceLastFrame * 10;

			Ogre::Real tooSmall = std::numeric_limits<Ogre::Real>::epsilon();

			// keep camera velocity below top speed and above epsilon
			if (mVelocity.squaredLength() > topSpeed * topSpeed)
			{
				mVelocity.normalise();
				mVelocity *= topSpeed;
			}
			else if (mVelocity.squaredLength() < tooSmall * tooSmall)
				mVelocity = Ogre::Vector3::ZERO;

			if (mVelocity != Ogre::Vector3::ZERO) mCamera->move(mVelocity * evt.timeSinceLastFrame);

			return true;
		}

		/*-----------------------------------------------------------------------------
		| Processes key presses for free-look style movement.
		-----------------------------------------------------------------------------*/
		virtual void injectKeyDown(const OIS::KeyEvent& evt)
		{
			if(mFirstVue == true)
			{
				if (evt.key == OIS::KC_W || evt.key == OIS::KC_UP) mGoingForward = true;
				else if (evt.key == OIS::KC_S || evt.key == OIS::KC_DOWN) mGoingBack = true;
				else if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT) mGoingLeft = true;
				else if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT) mGoingRight = true;
				else if (evt.key == OIS::KC_E) mGoingUp = true;
				else if (evt.key == OIS::KC_Q) mGoingDown = true;
			}
			else
			{
				if (evt.key == OIS::KC_W || evt.key == OIS::KC_UP) mGoingUp = true;
				else if (evt.key == OIS::KC_S || evt.key == OIS::KC_DOWN) mGoingDown = true;
				else if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT) mGoingLeft = true;
				else if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT) mGoingRight = true;
				else if (evt.key == OIS::KC_E) mGoingForward = true;
				else if (evt.key == OIS::KC_Q) mGoingBack = true;
			}
		}

		/*-----------------------------------------------------------------------------
		| Processes key releases for free-look style movement.
		-----------------------------------------------------------------------------*/
		virtual void injectKeyUp(const OIS::KeyEvent& evt)
		{
			if(mFirstVue == true)
			{
				if (evt.key == OIS::KC_W || evt.key == OIS::KC_UP) mGoingForward = false;
				else if (evt.key == OIS::KC_S || evt.key == OIS::KC_DOWN) mGoingBack = false;
				else if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT) mGoingLeft = false;
				else if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT) mGoingRight = false;
				else if (evt.key == OIS::KC_E) mGoingUp = false;
				else if (evt.key == OIS::KC_Q) mGoingDown = false;
			}
			else
			{
				if (evt.key == OIS::KC_W || evt.key == OIS::KC_UP) mGoingUp = false;
				else if (evt.key == OIS::KC_S || evt.key == OIS::KC_DOWN) mGoingDown = false;
				else if (evt.key == OIS::KC_A || evt.key == OIS::KC_LEFT) mGoingLeft = false;
				else if (evt.key == OIS::KC_D || evt.key == OIS::KC_RIGHT) mGoingRight = false;
				else if (evt.key == OIS::KC_E) mGoingForward = false;
				else if (evt.key == OIS::KC_Q) mGoingBack = false;
			}
		}

		/*-----------------------------------------------------------------------------
		| Processes mouse movement differently for each style.
		-----------------------------------------------------------------------------*/
		virtual void injectMouseMove(const OIS::MouseEvent& evt)
		{
			if(mFirstVue == true)
			{
				mCamera->yaw(Ogre::Degree(-evt.state.X.rel * 0.15f));
				mCamera->pitch(Ogre::Degree(-evt.state.Y.rel * 0.15f));
			}
		}

		/*-----------------------------------------------------------------------------
		| Processes mouse presses. Only applies for orbit style.
		| Left button is for orbiting, and right button is for zooming.
		-----------------------------------------------------------------------------*/
		virtual void injectMouseDown(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
		{
			if (id == OIS::MB_Left) mFirstVue = true;
		}

		/*-----------------------------------------------------------------------------
		| Processes mouse releases. Only applies for orbit style.
		| Left button is for orbiting, and right button is for zooming.
		-----------------------------------------------------------------------------*/
		virtual void injectMouseUp(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
		{
			if (id == OIS::MB_Left) mFirstVue = false;
		}

    protected:

		Ogre::Camera* mCamera;
		Ogre::SceneNode* mTarget;
		Ogre::Real mTopSpeed;
		Ogre::Vector3 mVelocity;
		bool mGoingForward;
		bool mGoingBack;
		bool mGoingLeft;
		bool mGoingRight;
		bool mGoingUp;
		bool mGoingDown;
		bool mFirstVue;
    };
}

#endif

#ifndef IClever_H
#define IClever_H

#include "../../stdafx.h"

class IClever
{
	public:

		virtual ~IClever(){}

		virtual void configure() = 0;
		virtual void release() = 0;
		virtual bool frameStarted(const Ogre::Real aElapsedTime) = 0;	
		virtual bool frameEnded(const Ogre::Real aElapsedTime) = 0;
		virtual bool update(const Ogre::Real aElapsedTime) = 0;

		virtual bool keyPressed( const OIS::KeyEvent &e ){return true;}
		virtual bool keyReleased( const OIS::KeyEvent &e ){return true;}
		virtual bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ){return true;}
		virtual bool mouseMoved( const OIS::MouseEvent &e ){return true;}
};
#endif
#ifndef MyLogListener_H
#define MyLogListener_H

#pragma once

class MyLogListener: public Ogre::LogListener
{
	public:

		MyLogListener()		
		{
			Ogre::LogManager::getSingletonPtr()->getDefaultLog()->addListener(this);
		}

		~MyLogListener()
		{
			Ogre::LogManager::getSingletonPtr()->getDefaultLog()->removeListener(this);
		}

		virtual void messageLogged( const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage)
		{
			 std::cerr << "[" << logName << "] " << message << std::endl;
			//std::cerr << "Message: " << message << std::endl;
		}
};
#endif
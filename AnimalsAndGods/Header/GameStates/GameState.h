#ifndef GameState_H
#define GameState_H

#include "../../stdafx.h"
#include "GameManager.h"

class GameState
{
	public:

		virtual void enter() = 0;
		virtual void exit() = 0;

		virtual void postEnter() = 0;
		virtual void postExit() = 0;
 
		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual void createUI() = 0; 
		virtual void releaseUI() = 0; 
		
		virtual bool keyPressed( const OIS::KeyEvent &e ) = 0;
		virtual bool keyReleased( const OIS::KeyEvent &e ) = 0;
 
		virtual bool mouseMoved( const OIS::MouseEvent &e ) = 0;
		virtual bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ) = 0;
		virtual bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ) = 0;
 
		virtual bool povMoved( const OIS::JoyStickEvent &e, int pov ) = 0;
		virtual bool axisMoved( const OIS::JoyStickEvent &e, int axis ) = 0;
		virtual bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID ) = 0;
		virtual bool buttonPressed( const OIS::JoyStickEvent &e, int button ) = 0;
		virtual bool buttonReleased( const OIS::JoyStickEvent &e, int button ) = 0;

		virtual bool frameStarted(const Ogre::FrameEvent& evt) = 0;
		virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) = 0;
		virtual bool frameEnded(const Ogre::FrameEvent& evt) = 0;	

		virtual void changeState(GameState* state) = 0;
		virtual void pushState(GameState* state) = 0;
		virtual void popState() = 0;

		// ResourceGroupListener callbacks
		virtual void resourceGroupScriptingStarted(const Ogre::String& groupName, size_t scriptCount){};
		virtual void scriptParseStarted(const Ogre::String& scriptName, bool& skipThisScript){};
		virtual void scriptParseEnded(const Ogre::String& scriptName, bool skipped){};
		virtual void resourceGroupScriptingEnded(const Ogre::String& groupName){};
		virtual void resourceGroupLoadStarted(const Ogre::String& groupName, size_t resourceCount){};
		virtual void resourceLoadStarted(const Ogre::ResourcePtr& resource){};
		virtual void resourceLoadEnded(void){};
		virtual void worldGeometryStageStarted(const Ogre::String& description){};
		virtual void worldGeometryStageEnded(void){};
		virtual void resourceGroupLoadEnded(const Ogre::String& groupName){};

		// ResourceLoadingListener callbacks
		virtual bool resourceCollision(Ogre::Resource *resource, Ogre::ResourceManager *resourceManager){return true;} 
		virtual Ogre::DataStreamPtr resourceLoading(const Ogre::String &name, const Ogre::String &group, Ogre::Resource *resource){return Ogre::DataStreamPtr();};
		virtual void resourceStreamOpened(const Ogre::String &name, const Ogre::String &group, Ogre::Resource *resource, Ogre::DataStreamPtr &dataStream){}

	protected:

		GameState() { }

};
 
#endif
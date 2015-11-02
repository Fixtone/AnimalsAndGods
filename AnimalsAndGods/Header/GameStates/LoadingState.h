#ifndef LoadingState_H
#define LoadingState_H
 
#include "GameState.h"

class LoadingState : public GameState
{
	public:

		void enter();
		void exit();
 
		void pause();
		void resume();

		void postEnter();
		void postExit(){};
 
		void createUI(); 
		void releaseUI();

		bool keyPressed( const OIS::KeyEvent &e );
		bool keyReleased( const OIS::KeyEvent &e );
 
		bool mouseMoved( const OIS::MouseEvent &e );
		bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
		bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );

		bool povMoved( const OIS::JoyStickEvent &e, int pov );
		bool axisMoved( const OIS::JoyStickEvent &e, int axis );
		bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID );
		bool buttonPressed( const OIS::JoyStickEvent &e, int button );
		bool buttonReleased( const OIS::JoyStickEvent &e, int button );

		bool frameStarted(const Ogre::FrameEvent& evt);
		bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		bool frameEnded(const Ogre::FrameEvent& evt);		

		// ResourceGroupListener callbacks
		void resourceGroupScriptingStarted(const Ogre::String& groupName, size_t scriptCount);
		void scriptParseStarted(const Ogre::String& scriptName, bool& skipThisScript);
		void scriptParseEnded(const Ogre::String& scriptName, bool skipped);
		void resourceGroupScriptingEnded(const Ogre::String& groupName);
		void resourceGroupLoadStarted(const Ogre::String& groupName, size_t resourceCount);
		void resourceLoadStarted(const Ogre::ResourcePtr& resource);
		void resourceLoadEnded(void);
		void worldGeometryStageStarted(const Ogre::String& description);
		void worldGeometryStageEnded(void);
		void resourceGroupLoadEnded(const Ogre::String& groupName);

		// ResourceLoadingListener callbacks
		bool resourceCollision(Ogre::Resource *resource, Ogre::ResourceManager *resourceManager); 
		Ogre::DataStreamPtr resourceLoading(const Ogre::String &name, const Ogre::String &group, Ogre::Resource *resource);
		void resourceStreamOpened(const Ogre::String &name, const Ogre::String &group, Ogre::Resource *resource, Ogre::DataStreamPtr &dataStream); 

		void changeState(GameState* state){ GameManager::getSingletonPtr()->changeState(state); }
		void pushState(GameState* state){ GameManager::getSingletonPtr()->pushState(state); }
		void popState(){ GameManager::getSingletonPtr()->popState(); }

		static LoadingState* getInstance() { return &mLoadingState; }

	protected:

		LoadingState(){} 		

		Ogre::Root *mRoot;
		Ogre::SceneManager* mSceneMgr;
		Ogre::RenderWindow* mRenderwindow;
		Ogre::Viewport* mViewport;		
		Ogre::Camera* mCamera;

	private:		

		static LoadingState mLoadingState;
		
		//#####BACKGORUND#####
		Ogre::Rectangle2D*	_LoadingRect;
		Ogre::SceneNode*	_LoadingRectNode;

		//#####UI#####
		Gui3D::Gui3D*			_Gui3D;
		Ogre::Camera*			_CurrentCamera;
		Gui3D::Caption*			_ResourcesCaption;

		unsigned int			_MusicL_AmbientId;		
};
 
#endif
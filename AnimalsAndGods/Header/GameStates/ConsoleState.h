#ifndef ConsoleState_H
#define ConsoleState_H
 
#include "GameState.h"

class ConsoleState : public GameState
{
	public:

		void enter();
		void exit();
 
		void pause();
		void resume();

		void postEnter(){};
		void postExit(){};
 
		void createUI(){}; 
		void releaseUI(){};

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
 
		void changeState(GameState* state){ GameManager::getSingletonPtr()->changeState(state); }
		void pushState(GameState* state){ GameManager::getSingletonPtr()->pushState(state); }
		void popState(){ GameManager::getSingletonPtr()->popState(); }

		static ConsoleState* getInstance() { return &mConsoleState; }

	protected:

		ConsoleState(){} 		

		Ogre::Root *mRoot;
		Ogre::SceneManager* mSceneMgr;
		Ogre::RenderWindow* mRenderwindow;
		Ogre::Viewport* mViewport;		
		Ogre::Camera* mCamera;

	private:

		static ConsoleState mConsoleState;
		
};
 
#endif
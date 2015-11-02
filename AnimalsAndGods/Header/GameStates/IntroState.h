#ifndef IntroState_H
#define IntroState_H
 
class IntroState : public GameState
{
	public:		

		void enter();
		void exit();
 
		void pause();
		void resume(); 
		
		void postEnter(){};
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
 
		void changeState(GameState* state){ GameManager::getSingletonPtr()->changeState(state); }
		void pushState(GameState* state){ GameManager::getSingletonPtr()->pushState(state); }
		void popState(){ GameManager::getSingletonPtr()->popState(); }

		static IntroState* getInstance() { return &mIntroState; }

	protected:		
 
		IntroState(){}

		Ogre::Root *mRoot;
		Ogre::SceneManager* mSceneMgr;	

	private:

		static IntroState	mIntroState;
		bool				_TimeFinished;					
		unsigned int		_AudioIntroId;				
		Ogre::Real			_TimeToFinish;
		Ogre::Real			_AcumTimeToFinish;
};
 
#endif
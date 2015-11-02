#ifndef PauseState_H
#define PauseState_H
 
class PauseState : public GameState
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

		static PauseState* getInstance() { return &mPauseState; }

	protected:		
 
		PauseState(){}

		Ogre::Root *mRoot;
		Ogre::SceneManager* mSceneMgr;	

	private:

		static PauseState	mPauseState;
		bool				_Resume;		
		bool				_Restart;
		bool				_MainMenu;		

		//#####################UI########################
		Gui3D::Gui3D*			_Gui3D;
		Ogre::Camera*			_CurrentCamera;
		Gui3D::ScreenPanel*		_SPauseMenuPanel;		
		Gorilla::Layer*			_MousePointerLayer;
		Gorilla::Rectangle*		_MousePointer;
		Ogre::Vector2			_NormalizedMousePosition;

		Ogre::Vector2			_getScreenCenterMouseDistance();
		bool					_ButtonRemusePressed(Gui3D::PanelElement* e);	
		bool					_ButtonRestartPressed(Gui3D::PanelElement* e);	
		bool					_ButtonMainMenuPressed(Gui3D::PanelElement* e);	
};
 
#endif
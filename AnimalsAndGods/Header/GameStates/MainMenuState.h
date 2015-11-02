#ifndef MainMenuState_H
#define MainMenuState_H
 
#include "GameState.h"
#include "PlayState.h"
#include "LoadingState.h"


class MainMenuState : public GameState
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

		static MainMenuState* getInstance() { return &_MainMenuState; }		

	protected:		
 
		MainMenuState(){}

		Ogre::Root *mRoot;
		Ogre::SceneManager* mSceneMgr;	

	private:	
		
		Ogre::Vector2 _getScreenCenterMouseDistance();

		static MainMenuState			_MainMenuState;
		bool							_ExitGame;		
		bool							_ChangeGameState;

		ShareData::GameConfigurations::LoadersConfigurations::sMenuData	_MenuData;
		
		//#####BACKGORUND#####
		Ogre::Rectangle2D*	_MainMenuRect;
		Ogre::SceneNode*	_MainMenuRectNode;		
				
		//UI
		Gui3D::Gui3D*			_Gui3D;
		Ogre::Camera*			_CurrentCamera;
		Gui3D::ScreenPanel*		_SMenuPanelStory;
		Gui3D::ScreenPanel*		_SMenuPanelCredits;
		Gui3D::ScreenPanel*		_SMenuPanelHelp;
		
		//##BTN EXIT		
		Gui3D::ScreenPanel*		_SPanelExit;
		bool					_ButtonExitPressed(Gui3D::PanelElement* e);		

		//##BTN PLAY
		Gui3D::ScreenPanel*		_SPanelPlay;
		bool					_ButtonPlayPressed(Gui3D::PanelElement* e);		

		//##BTN Story
		Gui3D::ScreenPanel*		_SPanelStory;
		bool					_ButtonStoryPressed(Gui3D::PanelElement* e);	

		//##BTN Credits
		Gui3D::ScreenPanel*		_SPanelCredits;
		bool					_ButtonCreditsPressed(Gui3D::PanelElement* e);	

		//##BTN Options
		Gui3D::ScreenPanel*		_SPanelOptions;
		bool					_ButtonOptionsPressed(Gui3D::PanelElement* e);	

		//##BTN Help
		Gui3D::ScreenPanel*		_SPanelHelp;
		bool					_ButtonHelpPressed(Gui3D::PanelElement* e);	

		//##BTN Back		
		bool					_ButtonBackCreditsPressed(Gui3D::PanelElement* e);	
		bool					_ButtonBackHelpPressed(Gui3D::PanelElement* e);	

		//#####MENU STORY#####
		Gui3D::Caption*					_SrotyNumberPagCaption;
		std::vector<Gui3D::Caption*>	_StoryPageCaptions;
		int								_CurrentStoryPage;
		bool							_ButtonBackStoryPressed(Gui3D::PanelElement* e);	
		bool							_ButtonBackPageStoryPressed(Gui3D::PanelElement* e);		
		bool							_ButtonNextPageStoryPressed(Gui3D::PanelElement* e);
		void							_MakeStoryPage();
		//#####MENU STORY#####

		// As Gui3D doesn't fully abstract Gorilla, you still have to deal with it. 
		// See http://www.valentinfrechaud.fr/Gui3DWiki/index.php/Gui3D_and_Gorilla for more infos.
		Gorilla::Layer* mMousePointerLayer;
		Gorilla::Rectangle* mMousePointer;
		Ogre::Vector2 mNormalizedMousePosition;
						
		unsigned int		_MusicMM_AmbientId;		
		unsigned int		_SoundMM_ButtonClickId;		

};
 
#endif
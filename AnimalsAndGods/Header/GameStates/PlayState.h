#ifndef PlayState_H
#define PlayState_H
 
#include "GameState.h"
#include "ConsoleState.h"
#include "LoadingState.h"

#include "../Loaders/DotSceneLoader/DotSceneLoader.h"
#include "../Camera/CameraManager.h"
#include "../Particles/ParticleUniverse/ParticleUniverseManager.h"
#include "../Particles/OgreParticles/ParticleOgreManager.h"

class PlayState : public GameState
{
	public:

		void enter();
		void exit();
 
		void pause();
		void resume();

		void postEnter();
		void postExit();
 
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

		static PlayState* getInstance() { return &mPlayState; }

	protected:

		PlayState(){} 		

		Ogre::Root *mRoot;
		Ogre::SceneManager* mSceneMgr;
		Ogre::RenderWindow* mRenderwindow;	
		Ogre::Light*		mMoonLight;

	private:

		static PlayState mPlayState;

		void _SetupShadows();		
		
		bool _FinishGame;

		bool mSSAO;		
		bool mDeferred;
		bool mLights;
		bool mDisplayNodes;
		bool mAmbientLights;
		bool mStreetLights;
		Ogre::LiSPSMShadowCameraSetup* mLiSPSMSetup;

		Ogre::Camera*	_CurrentCamera;

		//##GUI
		Gui3D::Gui3D*			_Gui3D;
		Gui3D::ScreenPanel*		_Panel;

		GlowMaterialListener*	_Gml;

		unsigned int		_MusicP_AmbientId;		
};
 
#endif
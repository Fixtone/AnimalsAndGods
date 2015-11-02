#ifndef GameManager_H
#define GameManager_H

class GameState;
class GameManager : public Ogre::FrameListener
				  , public OIS::KeyListener
				  , public OIS::MouseListener
				  , public OIS::JoyStickListener 
				  , public Ogre::WindowEventListener
				  , public OgreBites::SdkTrayListener
				  , public Ogre::ResourceGroupListener
				  , public Ogre::ResourceLoadingListener
				  ,	public Ogre::Singleton<GameManager>
{
	public:

		GameManager();
		~GameManager();

		void start(GameState* state);
		void changeState(GameState* state);
		void pushState(GameState* state);
		void popState();

		static GameManager& getSingleton(void);
		static GameManager* getSingletonPtr(void);

		Ogre::SceneManager* getSceneManager(){return mSceneManager;}

		Ogre::Camera* getCamera(){return mCameraManager->getActiveCamera()->getCamera();}
		Ogre::RenderWindow*	getRenderWindow(){return mRenderWindow;}
		OgreBites::SdkTrayManager* getTrayManager(){return mTrayMgr;}
		
		OIS::InputManager*			GetInputManager(){return mInputManager;}
		OIS::Mouse*					GetMouse(){return mMouse;}
		OIS::Keyboard*				GetKeyboard(){return mKeyboard;}
		OgreBites::InputContext		GetInputContext(){return mInputContext;}

		Video::VideoManager*		GetVideoManager(){return mVideoManager;}
		Ogre::Profiler*				GetOgreProfiler(){return mOgreProfiler;}

		//Ogre::CSMGpuConstants*		GetCSMGpuConstants(){return mGpuConstants;}

	protected:

		Ogre::Root*							mRoot;
		Ogre::SceneManager*					mSceneManager;
		Ogre::RenderWindow*					mRenderWindow;
		Ogre::OverlaySystem*				mOverlaySystem;
		Ogre::LogManager*					mLogManager;		
				
		MyLogListener*								mMyLogListener;
		GOE::GameObjectEntityManager*				mGameObjectEntityManager;
		GON::GameObjectNodeManager*					mGameObjectNodeManager;
		GOL::GameObjectLightManager*				mGameObjectLightManager;
		GOPS::GameObjectParticleSystemsManager*		mGameObjectParticleSystemsManager;
		GOCH::GameObjectCharactersManager*			mGameObjectCharactersManager;
		GOWP::GameObjectWayPointsManager*			mGameObjectWayPointsManager;
		GOT::GameObjectTrainsManager*				mGameObjectTrainsManager;
		GOSS::GameObjectSpaceShipsManager*			mGameObjectSpaceShipsManager;

		PhysicsManager*						mPhysicsManager;	
		Shaders::DeferredShadingManager*	mDeferredShadingManager;
		Logic::LogicManager*				mLogicManager;
		Lua::LuaManager*					mLuaManager;
		Cameras::CameraManager*				mCameraManager;		
		Video::VideoManager*				mVideoManager;
		Levels::LevelManager*				mLevelManager;
		Particles::ParticleUniverseManager*	mParticleUniverseManager;
		Particles::ParticleOgreManager*		mParticleOgreManager;		
		UI::GUI3DManager*					mGUI3DManager;
		Music::SoundManager*				mSoundManager;
		Mind::MindManager*					mMindManager;

		//Shadows
		//Ogre::CSMGpuConstants*				mGpuConstants;

		//Profiler
		Ogre::Profiler*						mOgreProfiler;

		// OgreBites
		OgreBites::SdkTrayManager*			mTrayMgr;		       
		OgreBites::ParamsPanel*				mDetailsPanel;     
		OgreBites::SelectMenu*				mDisplayModeMenu;
		OgreBites::InputContext				mInputContext;

		//OIS Input devices
		OIS::InputManager*					mInputManager;
		OIS::Mouse*							mMouse;
		OIS::Keyboard*						mKeyboard;

		void setupResources(void);
		bool configure(void);
 
		bool keyPressed( const OIS::KeyEvent &arg );
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

		void windowResized(Ogre::RenderWindow* rw);    
		void windowClosed(Ogre::RenderWindow* rw);

		void messageLogged( const Ogre::String& message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage);
		void write(const Ogre::String& name, const Ogre::String& message, Ogre::LogMessageLevel lml = Ogre::LML_NORMAL, bool maskDebug = false);	

	private:

		bool _initialiseManagers();
		bool _clearManagers();

		size_t						getWindowHandle();
		std::vector<GameState*>		mStates;	

};
 
#endif
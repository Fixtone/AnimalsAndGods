#include "stdafx.h"
#include "../../Header/GameStates/GameManager.h"

template<> GameManager* Ogre::Singleton<GameManager>::msSingleton = 0;
GameManager* GameManager::getSingletonPtr(void)
{
	return msSingleton;
}
GameManager& GameManager::getSingleton(void)
{  
	assert( msSingleton );  return ( *msSingleton );  
}

GameManager::GameManager()
{
	mRoot = 0;
	mInputManager = 0;
	mLogManager = 0;
	mMyLogListener = 0;
	mOgreProfiler = 0;
	mVideoManager = 0;
	mLuaManager = 0;
	mPhysicsManager = 0;
	mGameObjectEntityManager = 0;
	mGameObjectNodeManager = 0;
	mGameObjectLightManager = 0;
	mGameObjectParticleSystemsManager = 0;
	mGameObjectCharactersManager = 0;
	mGameObjectWayPointsManager = 0;
	mGameObjectTrainsManager = 0;
	mGameObjectSpaceShipsManager = 0;
	mDeferredShadingManager = 0;
	mLogicManager = 0;
	mCameraManager = 0;
	mTrayMgr = 0;
	mOverlaySystem = 0;
	mLevelManager = 0;
	mGUI3DManager = 0;
	mSoundManager = 0;
	mMindManager = 0;
	//mGpuConstants = 0;
}
 
GameManager::~GameManager()
{
	if(mOgreProfiler)
	{
		Ogre::Profiler::getSingletonPtr()->setEnabled(true);
		delete mOgreProfiler;
	}

	if(mTrayMgr){delete mTrayMgr;}
	if(mOverlaySystem){delete mOverlaySystem;}

	// clean up all the states
	while (!mStates.empty())
	{
		mStates.back()->exit();
		mStates.pop_back();
	}
	
	_clearManagers();

	Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup("Essential");
	Ogre::ResourceGroupManager::getSingleton().clearResourceGroup("Essential");

	//Remove ourself as a Window listener
	Ogre::WindowEventUtilities::removeWindowEventListener(mRenderWindow, this);
	windowClosed(mRenderWindow);				
	
	if(mLuaManager){delete mLuaManager;}
	if(mPhysicsManager){delete mPhysicsManager;}
	if(mGameObjectEntityManager){delete mGameObjectEntityManager;}
	if(mGameObjectNodeManager){delete mGameObjectNodeManager;}
	if(mGameObjectLightManager){delete mGameObjectLightManager;}
	if(mGameObjectParticleSystemsManager){delete mGameObjectParticleSystemsManager;}
	if(mGameObjectCharactersManager){delete mGameObjectCharactersManager;}
	if(mGameObjectWayPointsManager){delete mGameObjectWayPointsManager;}
	if(mGameObjectTrainsManager){delete mGameObjectTrainsManager;}
	if(mGameObjectSpaceShipsManager){delete mGameObjectSpaceShipsManager;}
	//if(mDeferredShadingManager){delete mDeferredShadingManager;}
	if(mLogicManager){delete mLogicManager;}	
	if(mCameraManager){delete mCameraManager;}	
	if(mGUI3DManager){delete mGUI3DManager;}
	if(mSoundManager){delete mSoundManager;}
	if(mMindManager){delete mMindManager;}
	//if(mGpuConstants){delete mGpuConstants;}

	delete ShareData::DefferedShading::DefferedShadingSharedData::getSingletonPtr();		
	delete ShareData::GameConfigurations::PlayerConfigurations::GameConfigurationsSharedData::getSingletonPtr();
		
	if(mVideoManager){delete mVideoManager;}
	if(mLevelManager){delete mLevelManager;}

	if (mRoot)
	{
		mRoot->removeFrameListener(this);
		delete mRoot;
	}

	if(mMyLogListener){delete mMyLogListener;}
	if(mLogManager){delete mLogManager;}
}
 
void GameManager::start(GameState* state)
{
	mLogManager = new Ogre::LogManager();
	Ogre::LogManager::getSingletonPtr()->createLog("AnimalsAndGods.log",true,true,false);

	mMyLogListener = new MyLogListener();			

#ifdef _DEBUG
	mRoot = new Ogre::Root(".\\config\\plugins_d.cfg",".\\config\\ogre.cfg");
	//mResourcesCfg = "resources_d.cfg";
	//mPluginsCfg = "plugins_d.cfg";
#else
	mRoot = new Ogre::Root(".\\config\\plugins.cfg",".\\config\\ogre.cfg");
	//mResourcesCfg = "resources.cfg";
	//mPluginsCfg = "plugins.cfg";
#endif
	
	mSceneManager = mRoot->createSceneManager(Ogre::ST_EXTERIOR_REAL_FAR, "AnimalsAndGodsSceneManager");		
	//mSceneManager->setDisplaySceneNodes(true);

	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneManager->addRenderQueueListener(mOverlaySystem);	

	if (!configure()) return; 
		setupResources();		

	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	mRenderWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
		
	mInputContext.mKeyboard = mKeyboard;
	mInputContext.mMouse = mMouse;	

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

	//Set initial mouse clipping size
	windowResized(mRenderWindow);

	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mRenderWindow, this);	
	
	//Profiler
	mOgreProfiler = new Ogre::Profiler();
	Ogre::Timer* profileTimer = new Ogre::Timer(); // Don't forget to delete this later!
	Ogre::Profiler::getSingletonPtr()->setTimer(profileTimer);
	Ogre::Profiler::getSingletonPtr()->setEnabled(true);

	mVideoManager = new Video::VideoManager();
	mGameObjectEntityManager = new GOE::GameObjectEntityManager();
	mGameObjectNodeManager = new GON::GameObjectNodeManager();
	mGameObjectLightManager= new GOL::GameObjectLightManager();
	mGameObjectParticleSystemsManager = new GOPS::GameObjectParticleSystemsManager();
	mGameObjectCharactersManager = new GOCH::GameObjectCharactersManager();
	mGameObjectWayPointsManager = new GOWP::GameObjectWayPointsManager();
	mGameObjectTrainsManager = new GOT::GameObjectTrainsManager();
	mGameObjectSpaceShipsManager = new GOSS::GameObjectSpaceShipsManager();
	mPhysicsManager = new PhysicsManager();
	//mDeferredShadingManager = new Shaders::DeferredShadingManager();
	mLogicManager = new Logic::LogicManager();
	mLevelManager = new Levels::LevelManager();		
	mGUI3DManager = new UI::GUI3DManager();
	mLuaManager =  new Lua::LuaManager();
	mSoundManager = Music::SoundManager::createManager();
	mMindManager = new Mind::MindManager;

	// Setup shadow GPU parameters before we load the resource groups so materials can use the parameters
	/*static const int maxCascades = 4;
	mGpuConstants = 0;
	mGpuConstants = new Ogre::CSMGpuConstants(maxCascades);*/

	//Shared Data
	new ShareData::DefferedShading::DefferedShadingSharedData();
	new ShareData::GameConfigurations::PlayerConfigurations::GameConfigurationsSharedData();
	ShareData::GameConfigurations::PlayerConfigurations::GameConfigurationsSharedData::getSingletonPtr()->loadPlayerConfiguration();
		
	mCameraManager = new Cameras::CameraManager();	
	mParticleUniverseManager = new Particles::ParticleUniverseManager();
	mParticleOgreManager = new Particles::ParticleOgreManager();

	Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
	Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(8);

#ifdef _DEBUG_
	mTrayMgr = new OgreBites::SdkTrayManager("InterfaceCronoCasEE", mRenderWindow, mInputContext, this);	
	mTrayMgr->showFrameStats(OgreBites::TL_TOP);   
	mTrayMgr->toggleAdvancedFrameStats();
	mTrayMgr->hideCursor();

	// create a params panel for displaying sample details
	Ogre::StringVector items;
	items.push_back("cam.pX");
	items.push_back("cam.pY");
	items.push_back("cam.pZ");
	items.push_back("");
	items.push_back("cam.oW");
	items.push_back("cam.oX");
	items.push_back("cam.oY");
	items.push_back("cam.oZ");
	items.push_back("");
	items.push_back("Filtering");
	items.push_back("Poly Mode");

	mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
	mDetailsPanel->setParamValue(9, "Bilinear");
	mDetailsPanel->setParamValue(10, "Solid");
	mDetailsPanel->hide();
#endif
 
	mRoot->addFrameListener(this);

	_initialiseManagers();

	changeState(state);
 
	mRoot->startRendering();
}

bool GameManager::_initialiseManagers()
{
	try
	{
		
		//#CAMERAS
		mCameraManager->initializeCameraManager(mRoot, mSceneManager, mRenderWindow);

		//#ENTITIES
		mGameObjectEntityManager->initialiseManager(mSceneManager);
		mGameObjectNodeManager->initialiseManager(mSceneManager);
		mGameObjectLightManager->initialiseManager(mSceneManager);
		mGameObjectParticleSystemsManager->initialiseManager(mSceneManager);
		mGameObjectCharactersManager->initialiseManager(mSceneManager);
		mGameObjectWayPointsManager->initialiseGameObjectWayPointsManager(mSceneManager);
		mGameObjectTrainsManager->initialiseManager(mSceneManager);
		mGameObjectSpaceShipsManager->initialiseManager(mSceneManager);

		//#PHYSICS
		mPhysicsManager->InitializePhysicsManager(mSceneManager);

		//#LEVELS
		mLevelManager->initializeLevelManager(mRoot, mSceneManager, mRenderWindow);

		//#LOGIC
		mLogicManager->initializeLogicManager();

		//#LUA
		mLuaManager->registerInterface(mGameObjectNodeManager);
		mLuaManager->registerInterface(mGameObjectTrainsManager);
		mLuaManager->registerInterface(mGameObjectCharactersManager);
		mLuaManager->registerInterface(mLogicManager);		
		mLuaManager->initializeLuaManager();

		//#PARTICLE UNIVERSE
		mParticleUniverseManager->initializeParticleUniverseManager(mSceneManager);

		//#PARTICLE OGRE			
		mParticleOgreManager->initializeParticleOgreManagerManager(mSceneManager);

		//#DEFFERED SHADING		
		/*mDeferredShadingManager->initializeDeferredShadingManager(mSceneManager, 
								    							  mSceneManager->getCamera("GodCam")->getViewport(),
																  Ogre::SHADOWTYPE_TEXTURE_ADDITIVE,
																  "DeferredShading/Shadows/Caster",
																  1,
																  15000,
																  7500);

		mDeferredShadingManager->setActive(false);
		ShareData::DefferedShading::DefferedShadingSharedData::getSingletonPtr()->iDeferredShadingManager = mDeferredShadingManager;
		ShareData::DefferedShading::DefferedShadingSharedData::getSingletonPtr()->iRoot = mRoot;
		ShareData::DefferedShading::DefferedShadingSharedData::getSingletonPtr()->iWindow = mRenderWindow;
		ShareData::DefferedShading::DefferedShadingSharedData::getSingletonPtr()->iActivate = false;
		ShareData::DefferedShading::DefferedShadingSharedData::getSingletonPtr()->iGlobalActivate = false;
		ShareData::DefferedShading::DefferedShadingSharedData::getSingletonPtr()->iMainLight = Ilumination::IluminationManager::getSingletonPtr()->getLightByName("MainStaticDirectionalLight", Ogre::Light::LT_DIRECTIONAL);
			*/

		//#GUI
		mGUI3DManager->initializeManager();

		//#MUSIC
		Ogre::LogManager::getSingletonPtr()->logMessage(mSoundManager->listAvailableDevices());
		mSoundManager->init();
		mSoundManager->setAudioPath( (char*) ".\\Resources\\Common\\Audio\\" );

		//#MINDS
		mMindManager->initialiseManager();

		return true;

	}
	catch(Ogre::Exception &e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[GameManager]: " + e.getDescription());
		return false;
	}
	
}

bool GameManager::_clearManagers()
{
	try
	{
		//#DEFFERED SHADING		
		//mDeferredShadingManager->clearDeferredShadingManager();

		//#CAMERAS
		mCameraManager->clearCameraManager();

		//#ENTITIES
		mGameObjectEntityManager->clearManager();
		mGameObjectNodeManager->clearManager();
		mGameObjectLightManager->clearManager();
		mGameObjectParticleSystemsManager->clearManager();
		mGameObjectCharactersManager->clearManager();
		mGameObjectWayPointsManager->clearGameObjectWayPointsManager();
		mGameObjectTrainsManager->clearManager();
		mGameObjectSpaceShipsManager->clearManager();
		
		//#PHYSICS
		mPhysicsManager->ClearPhysicsManager();			

		//#LEVELS
		mLevelManager->clearLevelManager();

		//#LOGIC
		mLogicManager->finalize();

		//#LUA		
		mLuaManager->finalize();

		//#PARTICLE UNIVERSE
		mParticleUniverseManager->clearParticleUniverseManager();

		//#PARTICLE OGRE			
		mParticleOgreManager->clearParticleOgreManagerManager();		

		//#GUI MANAGER		
		mGUI3DManager->clearManager();

		//#MUSIC
		mSoundManager->stopAllAudio();

		//#MINDS
		mMindManager->clearManager();

		return true;

	}
	catch(Ogre::Exception &e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[GameManager]: " + e.getDescription());
		return false;
	}
	
}

void GameManager::changeState(GameState* state)
{
	// cleanup the current state
	if ( !mStates.empty() ) 
	{		
		mStates.back()->exit();		
		mStates.back()->releaseUI();
		mStates.back()->postExit();
		mStates.pop_back();
	}
 
	// store and init the new state
	mStates.push_back(state);	
	mStates.back()->enter();
	mStates.back()->createUI();
	mStates.back()->postEnter();
}
 
void GameManager::pushState(GameState* state)
{
	// pause current state
	if ( !mStates.empty() ) 
	{
		mStates.back()->pause();
	}
 
	// store and init the new state
	mStates.push_back(state);
	mStates.back()->enter();
	mStates.back()->createUI();	
	mStates.back()->postEnter();
}
 
void GameManager::popState()
{
	// cleanup the current state
	if ( !mStates.empty() ) 
	{		
		mStates.back()->exit();		
		mStates.back()->releaseUI();
		mStates.back()->postExit();
		mStates.pop_back();
	}
 
	// resume previous state
	if ( !mStates.empty() ) {
		mStates.back()->resume();
	}
}
 
void GameManager::setupResources(void)
{

	// load resource paths from config file
	Ogre::ConfigFile cf;
#ifdef _DEBUG
	#ifdef TESTING
		cf.load(".\\config\\resourcesTesting_d.cfg");
	#else
		cf.load(".\\config\\resources_d.cfg");
	#endif
#else
	#ifdef TESTING
		cf.load(".\\config\\resourcesTesting.cfg");
	#else
		cf.load(".\\config\\resources.cfg");
	#endif
#endif	
 
	// go through all settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
 
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin() ; i != settings->end() ; ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}	
	
	Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Essential");
	Ogre::ResourceGroupManager::getSingletonPtr()->loadResourceGroup("Essential");
}
 
bool GameManager::configure(void)
{
	// load config settings from ogre.cfg		
	if (!mRoot->restoreConfig())
	{
		// if there is no config file, show the configuration dialog
		if (!mRoot->showConfigDialog())
		{
			return false;
		}
	}
	
	// initialise and create a default rendering window
	mRenderWindow = mRoot->initialise(true, "Animals And Gods - Version " + ShareData::GameConfigurations::Verions::GAME_VERION);
	
	//Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(mRenderWindow, this);	

	return true;
}

bool GameManager::keyPressed( const OIS::KeyEvent &arg )
{
	
#ifdef _DEBUG_
	//call keyPressed of current state
	if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

	if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
	{
		mTrayMgr->toggleAdvancedFrameStats();
	}
	else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
	{
		if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
		{
			mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
			mDetailsPanel->show();
		}
		else
		{
			mTrayMgr->removeWidgetFromTray(mDetailsPanel);
			mDetailsPanel->hide();
		}
	}
	else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
	{
		Ogre::String newVal;
		Ogre::TextureFilterOptions tfo;
		unsigned int aniso;

		switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
		{
		case 'B':
			newVal = "Trilinear";
			tfo = Ogre::TFO_TRILINEAR;
			aniso = 1;
			break;
		case 'T':
			newVal = "Anisotropic";
			tfo = Ogre::TFO_ANISOTROPIC;
			aniso = 8;
			break;
		case 'A':
			newVal = "None";
			tfo = Ogre::TFO_NONE;
			aniso = 1;
			break;
		default:
			newVal = "Bilinear";
			tfo = Ogre::TFO_BILINEAR;
			aniso = 1;
		}

		Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
		Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
		mDetailsPanel->setParamValue(9, newVal);
	}
	else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
	{
		Ogre::String newVal;
		Ogre::PolygonMode pm;

		switch(mCameraManager->getActiveCamera()->getCamera()->getPolygonMode())
		{
		case Ogre::PM_SOLID:
			newVal = "Wireframe";
			pm = Ogre::PM_WIREFRAME;
			break;
		case Ogre::PM_WIREFRAME:
			newVal = "Points";
			pm = Ogre::PM_POINTS;
			break;
		default:
			newVal = "Solid";
			pm = Ogre::PM_SOLID;
		}

		mCameraManager->getActiveCamera()->getCamera()->setPolygonMode(pm);
		mDetailsPanel->setParamValue(10, newVal);
	}
	else if(arg.key == OIS::KC_F5)   // refresh all textures
	{
		Ogre::TextureManager::getSingleton().reloadAll();
	}   	
	else if (arg.key == OIS::KC_1)
	{		
		NxOgre::VisualDebuggerDescription visualDebbugger_desc;		
		visualDebbugger_desc.mCollision.edges = true;		
		PhysicsManager::getSingletonPtr()->ActivePhysicsVisualDebugger(visualDebbugger_desc);
	}
	else if (arg.key == OIS::KC_2)
	{
		NxOgre::VisualDebuggerDescription visualDebbugger_desc;
		visualDebbugger_desc.showMinimal();		
		PhysicsManager::getSingletonPtr()->ActivePhysicsVisualDebugger(visualDebbugger_desc);
	}	
	else if(arg.key == OIS::KC_3)
	{		
		PhysicsManager::getSingletonPtr()->DestroyPhysicsVisualDebugger();
	}
	else if(arg.key == OIS::KC_4)
	{		
		GOWP::GameObjectWayPointsManager::getSingletonPtr()->showDebug();
	}
	else if(arg.key == OIS::KC_5)
	{		
		GOWP::GameObjectWayPointsManager::getSingletonPtr()->hideDebug();
	}
#endif

	mStates.back()->keyPressed(arg);	

	return true;
}

bool GameManager::keyReleased( const OIS::KeyEvent &e )
{
	// call keyReleased of current state
	mStates.back()->keyReleased(e);
	return true;
}
 
bool GameManager::mouseMoved( const OIS::MouseEvent &e )
{	
	// call keyReleased of current state
	mStates.back()->mouseMoved(e);
#ifdef _DEBUG_
	if (mTrayMgr->injectMouseMove(e)) return true;
#endif
	return true;
}

bool GameManager::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	// call keyReleased of current state
	mStates.back()->mousePressed(e,id);
#ifdef _DEBUG_
	if (mTrayMgr->injectMouseMove(e)) return true;
#endif
	return true;
}

bool GameManager::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	// call mouseReleased of current state
	mStates.back()->mouseReleased(e,id);
#ifdef _DEBUG_
	if (mTrayMgr->injectMouseMove(e)) return true;
#endif
	return true;
}
 
bool GameManager::povMoved( const OIS::JoyStickEvent &e, int pov )
{
	// call keyReleased of current state
	mStates.back()->povMoved(e,pov);
	return true;
}
	
bool GameManager::axisMoved( const OIS::JoyStickEvent &e, int axis )
{
	// call keyReleased of current state
	mStates.back()->axisMoved(e,axis);	
	return true;
}
		
bool GameManager::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )
{
	// call keyReleased of current state
	mStates.back()->sliderMoved(e,sliderID);
	return true;
}
		
bool GameManager::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	// call keyReleased of current state
	mStates.back()->buttonPressed(e,button);
	return true;
}
		
bool GameManager::buttonReleased( const OIS::JoyStickEvent &e, int button )
{
	// call keyReleased of current state
	mStates.back()->buttonReleased(e,button);
	return true;
}

bool GameManager::frameStarted(const Ogre::FrameEvent& evt)
{
	// call frameStarted of current state	
	return mStates.back()->frameStarted(evt);
	return true;
}
 
bool GameManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
{	
	mInputContext.capture();
#ifdef _DEBUG_
	mTrayMgr->frameRenderingQueued(evt);

	if (!mTrayMgr->isDialogVisible())
	{			
		if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
		{
			mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCameraManager->getActiveCamera()->getCamera()->getDerivedPosition().x));
			mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCameraManager->getActiveCamera()->getCamera()->getDerivedPosition().y));
			mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCameraManager->getActiveCamera()->getCamera()->getDerivedPosition().z));
			mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(mCameraManager->getActiveCamera()->getCamera()->getDerivedOrientation().w));
			mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCameraManager->getActiveCamera()->getCamera()->getDerivedOrientation().x));
			mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCameraManager->getActiveCamera()->getCamera()->getDerivedOrientation().y));
			mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCameraManager->getActiveCamera()->getCamera()->getDerivedOrientation().z));
		}
	}
#endif
	return mStates.back()->frameRenderingQueued(evt);

	return true;
}

bool GameManager::frameEnded(const Ogre::FrameEvent& evt)
{
	// call frameEnded of current state
	return mStates.back()->frameEnded(evt);	
}

// ResourceGroupListener callbacks
void GameManager::resourceGroupScriptingStarted(const Ogre::String& groupName, size_t scriptCount)
{	
	mStates.back()->resourceGroupScriptingStarted(groupName,scriptCount);
}
void GameManager::scriptParseStarted(const Ogre::String& scriptName, bool& skipThisScript)
{
	mStates.back()->scriptParseStarted(scriptName,skipThisScript);
}
void GameManager::scriptParseEnded(const Ogre::String& scriptName, bool skipped)
{
	mStates.back()->scriptParseEnded(scriptName,skipped);	
}
void GameManager::resourceGroupScriptingEnded(const Ogre::String& groupName)
{
	mStates.back()->resourceGroupScriptingEnded(groupName);	
}
void GameManager::resourceGroupLoadStarted(const Ogre::String& groupName, size_t resourceCount)
{
	mStates.back()->resourceGroupLoadStarted(groupName,resourceCount);
}
void GameManager::resourceLoadStarted(const Ogre::ResourcePtr& resource)
{
	mStates.back()->resourceLoadStarted(resource);	
}
void GameManager::resourceLoadEnded(void)
{
	mStates.back()->resourceLoadEnded();	
}
void GameManager::worldGeometryStageStarted(const Ogre::String& description)
{
	mStates.back()->worldGeometryStageStarted(description);
}
void GameManager::worldGeometryStageEnded(void)
{
	mStates.back()->worldGeometryStageEnded();
}
void GameManager::resourceGroupLoadEnded(const Ogre::String& groupName)
{
	mStates.back()->resourceGroupLoadEnded(groupName);
}

bool GameManager::resourceCollision(Ogre::Resource *resource, Ogre::ResourceManager *resourceManager)
{
	return mStates.back()->resourceCollision(resource, resourceManager);		
}
Ogre::DataStreamPtr GameManager::resourceLoading(const Ogre::String &name, const Ogre::String &group, Ogre::Resource *resource)
{	
	return mStates.back()->resourceLoading(name,group,resource);		
}
void GameManager::resourceStreamOpened(const Ogre::String &name, const Ogre::String &group, Ogre::Resource *resource, Ogre::DataStreamPtr &dataStream)
{
	mStates.back()->resourceStreamOpened(name,group,resource,dataStream);		
}

//Adjust mouse clipping area
void GameManager::windowResized(Ogre::RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState &ms = mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void GameManager::windowClosed(Ogre::RenderWindow* rw)
{
	//Only close for window that created OIS (the main window in these demos)
	if( rw == mRenderWindow )
	{
		if( mInputManager )
		{
			mInputManager->destroyInputObject( mMouse );
			mInputManager->destroyInputObject( mKeyboard );

			OIS::InputManager::destroyInputSystem(mInputManager);
			mInputManager = 0;
		}
	}
}

size_t GameManager::getWindowHandle()
{
	size_t handle = 0;	
	mRenderWindow->getCustomAttribute("WINDOW", &handle);
	return handle;
}

/*
GameManager* GameManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
GameManager& GameManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}
*/
#include "stdafx.h"
#include "../../Header/GameStates/PlayState.h"

PlayState PlayState::mPlayState;

void PlayState::enter()
{
	mRoot = Ogre::Root::getSingletonPtr();		
	mSceneMgr = mRoot->getSceneManager("AnimalsAndGodsSceneManager");

	PhysicsManager::getSingletonPtr()->createScene();	 

	mSceneMgr->setSkyBox(true, "NightSkybox", 100);
	//mSceneMgr->setSkyDome(true, "SunsetSkyDome", 10, 16, 100);
	
	Cameras::CameraManager::getSingletonPtr()->createCamera(ShareData::GameConfigurations::CameraConfigurations::FREE,
															"FreePlayCam", Ogre::Vector3(0, 10, 30), Ogre::Quaternion::IDENTITY*Ogre::Vector3::NEGATIVE_UNIT_Z);
			
	//Shaders::DeferredShadingManager::getSingletonPtr()->setActive(true);

	DotSceneLoader loader;
	loader.parseDotScene("CityLevel.scene","Play", mSceneMgr);	
	
	GOE::GameObjectEntityManager::getSingletonPtr()->configureGOE();
	GON::GameObjectNodeManager::getSingletonPtr()->configureGON();
	GOT::GameObjectTrainsManager::getSingletonPtr()->configureGON();
	GOPS::GameObjectParticleSystemsManager::getSingletonPtr()->configureGOPS();	
	GOSS::GameObjectSpaceShipsManager::getSingletonPtr()->configureGON();
	GOCH::GameObjectCharactersManager::getSingletonPtr()->configureGOCH();

	Cameras::CameraManager::getSingletonPtr()->setActiveCamera("PlayerCameraFPS");
	GOCH::GameObjectCharactersManager::getSingletonPtr()->getGOCHPlayer()->setActive(true);
	_CurrentCamera = GameManager::getSingletonPtr()->getCamera();
	Mind::MindManager::getSingletonPtr()->configureMind();
	_Gui3D = UI::GUI3DManager::getSingletonPtr()->getGUI3D();	
	
	_FinishGame = false;
	mSSAO = true;
	mLights = true;
	mDeferred = true;
	mDisplayNodes = false;
	mAmbientLights = false;
	mStreetLights = false;

	Ogre::CompositorManager::getSingleton().addCompositor(Cameras::CameraManager::getSingletonPtr()->getActiveCamera()->getCamera()->getViewport(), "Glow");
	Ogre::CompositorManager::getSingleton().setCompositorEnabled(Cameras::CameraManager::getSingletonPtr()->getActiveCamera()->getCamera()->getViewport(), "Glow", true);
	_Gml = new GlowMaterialListener();
	Ogre::MaterialManager::getSingleton().addListener(_Gml);

	GameManager::getSingletonPtr()->getSceneManager()->setAmbientLight(Ogre::ColourValue(0.19f,0.21f,0.31f));
	GOL::GameObjectLightManager::getSingletonPtr()->GetGOLFarAmbient("NebulaLight")->mGOLLight->setVisible(true);
	GOL::GameObjectLightManager::getSingletonPtr()->GetGOLFarAmbient("NebulaLight")->mGOLLight->setCastShadows(true);
	
	this->_SetupShadows();

	mSceneMgr->setFog(Ogre::FOG_LINEAR, Ogre::ColourValue(0.12f, 0.2f, 0.3f), 0.47f, 0, 500);

	Music::SoundManager::getSingletonPtr()->loadAudio(".\\Resources\\Play\\Music\\MainMenu_TheKnowingandtheDarkMirror.ogg", &_MusicP_AmbientId, true);		
	Music::SoundManager::getSingletonPtr()->setListenerPosition(Ogre::Vector3::ZERO,Ogre::Vector3::ZERO,Ogre::Quaternion::IDENTITY);
	Music::SoundManager::getSingletonPtr()->playAudio(_MusicP_AmbientId, true);		
}
 
void PlayState::exit()
{
	Ogre::MaterialManager::getSingleton().removeListener(_Gml);	
	Ogre::CompositorManager::getSingleton().removeAll();	
	GOL::GameObjectLightManager::getSingletonPtr()->releaseGOL();
	GOPS::GameObjectParticleSystemsManager::getSingletonPtr()->releaseGOPS();
	GOE::GameObjectEntityManager::getSingletonPtr()->releaseGOE();	
	GOT::GameObjectTrainsManager::getSingletonPtr()->releaseGON();	
	GOSS::GameObjectSpaceShipsManager::getSingletonPtr()->releaseGON();
	GOCH::GameObjectCharactersManager::getSingletonPtr()->releaseGOCH();
	GON::GameObjectNodeManager::getSingletonPtr()->releaseGON();
	GOWP::GameObjectWayPointsManager::getSingletonPtr()->releaseGameObjectWayPointsManager();
	Mind::MindManager::getSingletonPtr()->releaseMind();
	PhysicsManager::getSingletonPtr()->destroyScene();	
	Cameras::CameraManager::getSingletonPtr()->clearCameraManager();
	Levels::LevelManager::getSingletonPtr()->unloadResourcesGameLevelScene(Levels::Play);	
	mSceneMgr->clearScene();

	Music::SoundManager::getSingletonPtr()->stopAudio(_MusicP_AmbientId);
	Music::SoundManager::getSingletonPtr()->stopAllAudio();
}
 
void PlayState::pause()
{
}
 
void PlayState::resume()
{		
}

void PlayState::createUI()
{
	Ogre::Real w = GameManager::getSingletonPtr()->getRenderWindow()->getWidth();
	Ogre::Real h = GameManager::getSingletonPtr()->getRenderWindow()->getHeight();

	Gorilla::Screen* myScreen = _Gui3D->createScreen(_CurrentCamera->getViewport(), "mindFont", "playScreen", "Play");	 

	_Gui3D->getPanelColors()->panelGradientType = Gorilla::Gradient_NorthSouth;
	_Gui3D->getPanelColors()->panelGradientColorStart = Gorilla::rgb(44, 43, 43, 125);
	_Gui3D->getPanelColors()->panelGradientColorEnd = Gorilla::rgb(44, 43, 43, 175);
	//_Gui3D->getPanelColors()->panelBorder = Gorilla::rgb(255, 255, 255, 0.75f);
	//_Gui3D->getPanelColors()->panelBorderSize = 4;
	_Panel = new Gui3D::ScreenPanel(_Gui3D, myScreen, Ogre::Vector2((w/2)-400, h-120), Ogre::Vector2(800, 100), "mindFont", "playScreenPanel");
	_Gui3D->getPanelColors()->captionTextSize = 27;
	Mind::MindManager::getSingletonPtr()->setGui3DPanelMindThoughts(_Panel);

	_Panel->hideInternalMousePointer();
}

void PlayState::releaseUI()
{
	_Gui3D->destroyScreen("playScreen");	
}

void PlayState::postEnter()
{
	//Mind::MindManager::getSingletonPtr()->setUICaptionMindThoughts(_UICaptionPlay);
}

void PlayState::postExit()
{
}

bool PlayState::keyPressed( const OIS::KeyEvent &e )
{	
	if (e.key == OIS::KC_ESCAPE)
	{
		pushState(PauseState::getInstance());
	}		
	else if (e.key == OIS::KC_9)
	{
		GOCH::GameObjectCharactersManager::getSingletonPtr()->getGOCHPlayer()->setActive(true);
		Cameras::CameraManager::getSingletonPtr()->setActiveCamera("PlayerCameraFPS");
	}
	else if (e.key == OIS::KC_0)
	{
		GOCH::GameObjectCharactersManager::getSingletonPtr()->getGOCHPlayer()->setActive(false);
		Cameras::CameraManager::getSingletonPtr()->setActiveCamera("FreePlayCam");
	}	
	else if (e.key == OIS::KC_N)
	{
		mDisplayNodes = !mDisplayNodes;
		mSceneMgr->setDisplaySceneNodes(mDisplayNodes);
	}
	else if(e.key == OIS::KC_DELETE)
	{
		GOE::GameObjectEntityManager::getSingletonPtr()->explodeAllBodies(25);
	}	
	else if(e.key == OIS::KC_END)
	{
		_FinishGame = true;
	}
	
	if(GOCH::GameObjectCharactersManager::getSingletonPtr()->getGOCHPlayer())
		GOCH::GameObjectCharactersManager::getSingletonPtr()->getGOCHPlayer()->keyPressed(e);

	Cameras::CameraManager::getSingletonPtr()->keyPressed(e);
	
	return true;
}	

bool PlayState::keyReleased( const OIS::KeyEvent &e )
{		
	if(GOCH::GameObjectCharactersManager::getSingletonPtr()->getGOCHPlayer())
		GOCH::GameObjectCharactersManager::getSingletonPtr()->getGOCHPlayer()->keyReleased(e);	

	Cameras::CameraManager::getSingletonPtr()->keyReleased(e);

	return true;
}
 
bool PlayState::mouseMoved( const OIS::MouseEvent &e )
{	
	if(GOCH::GameObjectCharactersManager::getSingletonPtr()->getGOCHPlayer())
		GOCH::GameObjectCharactersManager::getSingletonPtr()->getGOCHPlayer()->mouseMoved(e);

	Cameras::CameraManager::getSingletonPtr()->mouseMoved(e);

	return true;
}

bool PlayState::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{	
	if(!Ogre::StringUtil::match(Cameras::CameraManager::getSingletonPtr()->getActiveCamera()->getCamera()->getName(),"FreePlayCam"))
		Ogre::Vector2 mousePosition(e.state.X.abs/float(e.state.width), e.state.Y.abs/float(e.state.height));

	Cameras::CameraManager::getSingletonPtr()->mousePressed(e,id);

	return true;
}

bool PlayState::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{	
	Cameras::CameraManager::getSingletonPtr()->mouseReleased(e,id);	
	return true;
} 

bool PlayState::povMoved( const OIS::JoyStickEvent &e, int pov )
{
	return true;
}

bool PlayState::axisMoved( const OIS::JoyStickEvent &e, int axis )
{
	return true;
}

bool PlayState::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )
{
	return true;
}

bool PlayState::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool PlayState::buttonReleased( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool PlayState::frameStarted(const Ogre::FrameEvent& evt)
{	
	GOE::GameObjectEntityManager::getSingletonPtr()->frameStartedGOE(evt.timeSinceLastFrame);	
	GON::GameObjectNodeManager::getSingletonPtr()->frameStartedGON(evt.timeSinceLastFrame);	
	GOT::GameObjectTrainsManager::getSingletonPtr()->frameStartedGON(evt.timeSinceLastFrame);	
	GOPS::GameObjectParticleSystemsManager::getSingletonPtr()->frameStartedGOPS(evt.timeSinceLastFrame);	
	GOSS::GameObjectSpaceShipsManager::getSingletonPtr()->frameStartedGON(evt.timeSinceLastFrame);
	GOCH::GameObjectCharactersManager::getSingletonPtr()->frameStartedGOCH(evt.timeSinceLastFrame);	
	Mind::MindManager::getSingletonPtr()->frameStartedMind(evt.timeSinceLastFrame);

	return true;
}

bool PlayState::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	GOE::GameObjectEntityManager::getSingletonPtr()->updateLogicGOE(evt.timeSinceLastFrame);	
	GOE::GameObjectEntityManager::getSingletonPtr()->updateGOE(evt.timeSinceLastFrame);	
	GON::GameObjectNodeManager::getSingletonPtr()->updateLogicGON(evt.timeSinceLastFrame);
	GON::GameObjectNodeManager::getSingletonPtr()->updateGON(evt.timeSinceLastFrame);		
	GOT::GameObjectTrainsManager::getSingletonPtr()->updateGON(evt.timeSinceLastFrame);		
	GOPS::GameObjectParticleSystemsManager::getSingletonPtr()->updateLogicGOPS(evt.timeSinceLastFrame);		
	GOPS::GameObjectParticleSystemsManager::getSingletonPtr()->updateGOPS(evt.timeSinceLastFrame);	
	GOSS::GameObjectSpaceShipsManager::getSingletonPtr()->updateGON(evt.timeSinceLastFrame);
	GOCH::GameObjectCharactersManager::getSingletonPtr()->updateGOCH(evt.timeSinceLastFrame);	
	GOCH::GameObjectCharactersManager::getSingletonPtr()->updateLogicGOCH(evt.timeSinceLastFrame);	
	Mind::MindManager::getSingletonPtr()->updateMind(evt.timeSinceLastFrame);
	
	//Physcis
	GameManager::getSingletonPtr()->GetOgreProfiler()->getSingletonPtr()->beginProfile("UpdatePhysics");	
	PhysicsManager::getSingletonPtr()->updatePhysics(evt.timeSinceLastFrame);
	GameManager::getSingletonPtr()->GetOgreProfiler()->getSingletonPtr()->endProfile("UpdatePhysics");

	//Logic
	GameManager::getSingletonPtr()->GetOgreProfiler()->getSingletonPtr()->beginProfile("UpdateLogic");
	Logic::LogicManager::getSingletonPtr()->update(evt.timeSinceLastFrame);
	GameManager::getSingletonPtr()->GetOgreProfiler()->getSingletonPtr()->endProfile("UpdateLogic");

	//Cameras Update
	GameManager::getSingletonPtr()->GetOgreProfiler()->getSingletonPtr()->beginProfile("UpdateCameras");
	Cameras::CameraManager::getSingletonPtr()->update(evt);
	GameManager::getSingletonPtr()->GetOgreProfiler()->getSingletonPtr()->endProfile("UpdateCameras");		

	return true;
}

bool PlayState::frameEnded(const Ogre::FrameEvent& evt)
{ 
	GOE::GameObjectEntityManager::getSingletonPtr()->frameEndedGOE(evt.timeSinceLastFrame);	
	GON::GameObjectNodeManager::getSingletonPtr()->frameEndedGON(evt.timeSinceLastFrame);	
	GOT::GameObjectTrainsManager::getSingletonPtr()->frameEndedGON(evt.timeSinceLastFrame);	
	GOSS::GameObjectSpaceShipsManager::getSingletonPtr()->frameEndedGON(evt.timeSinceLastFrame);
	GOPS::GameObjectParticleSystemsManager::getSingletonPtr()->frameEndedGOPS(evt.timeSinceLastFrame);			
	GOCH::GameObjectCharactersManager::getSingletonPtr()->frameEndedGOCH(evt.timeSinceLastFrame);	
	Mind::MindManager::getSingletonPtr()->frameEndedMind(evt.timeSinceLastFrame);
	
	Critter::Node* playerNode(GOCH::GameObjectCharactersManager::getSingletonPtr()->getGOCHPlayer()->getCharacterNode());	
	
	Music::SoundManager::getSingletonPtr()->setListenerPosition(playerNode->getPosition(),
																Ogre::Vector3::ZERO,
																playerNode->getOrientation());

	if(Mind::MindManager::getSingletonPtr()->isFinishThoughts() || _FinishGame)
	{
		Levels::LevelManager::getSingletonPtr()->setGameLevelSceneToLoad(Levels::Finish);
		changeState(FinishState::getInstance()); 
	}
	
	return true;
}

void PlayState::_SetupShadows()
{
	mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);
	mSceneMgr->setShadowColour(ColourValue(0.4f, 0.4f, 0.4f));
	mSceneMgr->setShadowTextureSize(4096);
	mSceneMgr->setShadowTextureCount(1);	
}
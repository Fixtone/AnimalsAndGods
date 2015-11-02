 #include "stdafx.h"
#include "../../Header/GameStates/IntroState.h"

IntroState IntroState::mIntroState;
void IntroState::enter()
{  
	mRoot = Ogre::Root::getSingletonPtr();
	mSceneMgr = mRoot->getSceneManager("AnimalsAndGodsSceneManager");

	Levels::LevelManager::getSingletonPtr()->loadResourcesGameLevelScene(Levels::Intro);
	
	//GameManager::getSingletonPtr()->getSceneManager()->setAmbientLight(Ogre::ColourValue::White);
	
	// Create background rectangle covering the whole screen
	Ogre::Rectangle2D* rect = new Ogre::Rectangle2D(true);
	rect->setCorners(-1.0, 1.0, 1.0, -1.0);
	rect->setMaterial("VideoMaterial");
	rect->setRenderQueueGroup(Shaders::DeferredShadingManager::POST_GBUFFER_RENDER_QUEUE);
	
	// Use infinite AAB to always stay visible
	Ogre::AxisAlignedBox aabInf;	
	aabInf.setInfinite();
	rect->setBoundingBox(aabInf);

	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode("VideoRect");
	node->attachObject(rect);

	Video::VideoManager::VideoInfo videoInfo;
	videoInfo.videoMaterialName = "VideoMaterial";
	videoInfo.videoTextureUnitName = "VideoTextureUnit";
	videoInfo.bufferTarget = 1.5f;
	videoInfo.videoName = "./Resources/Intro/Videos/Intro.avi";
	videoInfo.lopping = false;
	videoInfo.forcedAudioChannelsNumber = 1;
	
	GameManager::getSingletonPtr()->GetVideoManager()->PlayVideo(videoInfo);	
	Cameras::CameraManager::getSingletonPtr()->createCamera(ShareData::GameConfigurations::CameraConfigurations::STATIC,
															"IntroCam", Ogre::Vector3(0, 0, 0), Ogre::Vector3(0,0,0));
	Cameras::CameraManager::getSingletonPtr()->setActiveCamera("IntroCam");	
	
 
	// We loop to be able to test the pause function
	Music::SoundManager::getSingletonPtr()->loadAudio(".\\Resources\\Intro\\Music\\Intro.ogg", &_AudioIntroId, false);
	Music::SoundManager::getSingletonPtr()->setListenerPosition(Ogre::Vector3::ZERO,Ogre::Vector3::ZERO,Ogre::Quaternion::IDENTITY);
	//NxOgre::Volume* volume = PhysicsManager::getSingletonPtr()->getScene()->createVolume(
	Music::SoundManager::getSingletonPtr()->playAudio(_AudioIntroId,true);	

	_TimeFinished = false;
	_TimeToFinish = 19;
	_AcumTimeToFinish = 0;
}
 
void IntroState::exit()
{	
	Music::SoundManager::getSingletonPtr()->stopAudio( _AudioIntroId );
	Music::SoundManager::getSingletonPtr()->stopAllAudio();

	Levels::LevelManager::getSingletonPtr()->unloadResourcesGameLevelScene(Levels::Intro);	
	Cameras::CameraManager::getSingletonPtr()->removeCustomCameraByName("IntroCam");
	GameManager::getSingletonPtr()->GetVideoManager()->StopVideo();

	mSceneMgr->clearScene();
}
 
void IntroState::pause()
{
}
 
void IntroState::resume()
{	
}

void IntroState::createUI()
{
}

void IntroState::releaseUI()
{
}

bool IntroState::keyPressed( const OIS::KeyEvent &e )
{	
	if (e.key == OIS::KC_ESCAPE)
	{		
		Levels::LevelManager::getSingletonPtr()->setGameLevelSceneToLoad(Levels::MainMenu);
		changeState(MainMenuState::getInstance()); 
	}

	return true;
}	

bool IntroState::keyReleased( const OIS::KeyEvent &e )
{	
	return true;
}
 
bool IntroState::mouseMoved( const OIS::MouseEvent &e )
{	
	return true;
}

bool IntroState::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	return true;
}

bool IntroState::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{	
	return true;
} 

bool IntroState::povMoved( const OIS::JoyStickEvent &e, int pov )
{
	return true;
}

bool IntroState::axisMoved( const OIS::JoyStickEvent &e, int axis )
{
	return true;
}

bool IntroState::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )
{
	return true;
}

bool IntroState::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool IntroState::buttonReleased( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool IntroState::frameStarted(const Ogre::FrameEvent& evt)
{	
	return true;
}

bool IntroState::frameRenderingQueued(const Ogre::FrameEvent& evt)
{	
	_AcumTimeToFinish+=evt.timeSinceLastFrame;
	if(_AcumTimeToFinish>_TimeToFinish)
		_TimeFinished = true;

	return true;
}

bool IntroState::frameEnded(const Ogre::FrameEvent& evt)
{
	if(_TimeFinished)
	{
		Levels::LevelManager::getSingletonPtr()->setGameLevelSceneToLoad(Levels::MainMenu);
		changeState(MainMenuState::getInstance()); 
	}
	return true;
}
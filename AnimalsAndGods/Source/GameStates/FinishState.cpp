 #include "stdafx.h"
#include "../../Header/GameStates/FinishState.h"

FinishState FinishState::mFinishState;

void FinishState::enter()
{  
	mRoot = Ogre::Root::getSingletonPtr();
	mSceneMgr = mRoot->getSceneManager("AnimalsAndGodsSceneManager");

	Levels::LevelManager::getSingletonPtr()->loadResourcesGameLevelScene(Levels::Finish);
	
	GameManager::getSingletonPtr()->getSceneManager()->setAmbientLight(Ogre::ColourValue::White);
	
	Cameras::CameraManager::getSingletonPtr()->createCamera(ShareData::GameConfigurations::CameraConfigurations::STATIC,
															"FinishCam", Ogre::Vector3(0, 0, 0), Ogre::Vector3(0,0,0));
	Cameras::CameraManager::getSingletonPtr()->setActiveCamera("FinishCam");	
	
 
	//Create background rectangle covering the whole screen
	_FinishRect = new Ogre::Rectangle2D(true);
	_FinishRect->setCorners(-1.0, 1.0, 1.0, -1.0);
	_FinishRect->setMaterial("FinishRect_Mat");
		
	// Use infinite AAB to always stay visible
	Ogre::AxisAlignedBox aabInf;	
	aabInf.setInfinite();
	_FinishRect->setBoundingBox(aabInf);

	_FinishRectNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MainMenu_Node");
	_FinishRectNode->attachObject(_FinishRect);			

	Music::SoundManager::getSingletonPtr()->loadAudio(".\\Resources\\Finish\\Music\\Finish_ActNatural.ogg", &_MusicF_AmbientId, true);		
	Music::SoundManager::getSingletonPtr()->setListenerPosition(Ogre::Vector3::ZERO,Ogre::Vector3::ZERO,Ogre::Quaternion::IDENTITY);
	Music::SoundManager::getSingletonPtr()->playAudio(_MusicF_AmbientId, true);		

	_CurrentCamera = GameManager::getSingletonPtr()->getCamera();
	_Gui3D = UI::GUI3DManager::getSingletonPtr()->getGUI3D();
	_MainMenuGame = false;
}
 
void FinishState::exit()
{	
	delete _FinishRect;
	Tools::Destroy(mSceneMgr,_FinishRectNode->getName());		
	
	Music::SoundManager::getSingletonPtr()->stopAllAudio();
	Music::SoundManager::getSingletonPtr()->stopAudio(_MusicF_AmbientId);

	Levels::LevelManager::getSingletonPtr()->unloadResourcesGameLevelScene(Levels::Finish);	
	Cameras::CameraManager::getSingletonPtr()->removeCustomCameraByName("FinishCam");
	Cameras::CameraManager::getSingletonPtr()->clearCameraManager();

	mSceneMgr->clearScene();
}
 
void FinishState::pause()
{
}
 
void FinishState::resume()
{	
}

void FinishState::createUI()
{
	Ogre::RenderWindow* window =  GameManager::getSingletonPtr()->getRenderWindow();

	Gorilla::Screen* myScreen = _Gui3D->createScreen(_CurrentCamera->getViewport(), "FinishStateAtlas", "finishScreen", "Finish");	 	
	
	_SFinishMenuPanel  = new Gui3D::ScreenPanel(_Gui3D, myScreen,
											    Ogre::Vector2::ZERO,
												Ogre::Vector2(186, 130),													   
												"FinishStateAtlas", "finishMenuPanel");
	
	_SFinishMenuPanel->makeCaption(10,10,800,30,"Presiona cualquier tecla para continuar", Gorilla::TextAlign_Left);	
	_SFinishMenuPanel->makeCaption(10,40,800,30,"Pulp Games Studio @ Fixtone - 2015", Gorilla::TextAlign_Left);

	_SFinishMenuPanel->hideInternalMousePointer();

}

void FinishState::releaseUI()
{
	_Gui3D->destroyScreen("finishScreen");
}

bool FinishState::keyPressed( const OIS::KeyEvent &e )
{
	_MainMenuGame = true;	

	return true;
}	

bool FinishState::keyReleased( const OIS::KeyEvent &e )
{	
	return true;
}
 
bool FinishState::mouseMoved( const OIS::MouseEvent &e )
{	
	return true;
}

bool FinishState::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	return true;
}

bool FinishState::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{	
	return true;
} 

bool FinishState::povMoved( const OIS::JoyStickEvent &e, int pov )
{
	return true;
}

bool FinishState::axisMoved( const OIS::JoyStickEvent &e, int axis )
{
	return true;
}

bool FinishState::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )
{
	return true;
}

bool FinishState::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool FinishState::buttonReleased( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool FinishState::frameStarted(const Ogre::FrameEvent& evt)
{	
	return true;
}

bool FinishState::frameRenderingQueued(const Ogre::FrameEvent& evt)
{	
	return true;
}

bool FinishState::frameEnded(const Ogre::FrameEvent& evt)
{
	if (_MainMenuGame)
	{
		Levels::LevelManager::getSingletonPtr()->setGameLevelSceneToLoad(Levels::MainMenu);
		changeState(MainMenuState::getInstance());
	}

	return true;
}
#include "stdafx.h"
#include "../../Header/GameStates/PauseState.h"

PauseState PauseState::mPauseState;
void PauseState::enter()
{  
	mRoot = Ogre::Root::getSingletonPtr();
	mSceneMgr = mRoot->getSceneManager("AnimalsAndGodsSceneManager");
	
	Levels::LevelManager::getSingletonPtr()->loadResourcesGameLevelScene(Levels::Pause);

	_CurrentCamera = GameManager::getSingletonPtr()->getCamera();
	_Gui3D = UI::GUI3DManager::getSingletonPtr()->getGUI3D();
	
	_Resume = false;		
	_Restart = false;
	_MainMenu = false;		
}
 
void PauseState::exit()
{	
	Levels::LevelManager::getSingletonPtr()->unloadResourcesGameLevelScene(Levels::Pause);	
}
 
void PauseState::pause()
{
}
 
void PauseState::resume()
{	
}

void PauseState::createUI()
{
	Gorilla::Screen* myScreen = _Gui3D->createScreen(_CurrentCamera->getViewport(), "PauseStateAtlas", "pauseScreen", "Pause");	 
	
	_Gui3D->getPanelColors()->panelBackgroundSpriteName = "none";
	_Gui3D->getPanelColors()->panelGradientType = Gorilla::Gradient_NorthSouth;
	_Gui3D->getPanelColors()->panelGradientColorStart = Gorilla::rgb(0, 0, 0, 225);
	_Gui3D->getPanelColors()->panelGradientColorEnd = Gorilla::rgb(0, 0, 0, 225);
	_Gui3D->getPanelColors()->captionTextSize = 27;
	_Gui3D->getPanelColors()->buttonTextSize = 27;

	Ogre::RenderWindow* window =  GameManager::getSingletonPtr()->getRenderWindow();

	_SPauseMenuPanel = new Gui3D::ScreenPanel(_Gui3D, myScreen,
											  Ogre::Vector2::ZERO,
											  Ogre::Vector2(window->getWidth(), window->getHeight()),													   
											  "PauseStateAtlas", "pauseMenuPanel");

	//#################################################BUTTONS########################################################
	Ogre::Vector2  ResumeButtonPosition((window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_PauseStateResumePosition.x)/
										 ShareData::GameConfigurations::UIConfigurations::NativeWResolition,
										(window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_PauseStateResumePosition.y)/
										 ShareData::GameConfigurations::UIConfigurations::NativeHResolition);

	Ogre::Vector2  ResumeButtonSize((window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_PauseStateResumeSize.x)/
									 ShareData::GameConfigurations::UIConfigurations::NativeWResolition,
									(window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_PauseStateResumeSize.y)/
									 ShareData::GameConfigurations::UIConfigurations::NativeHResolition);

	Gui3D::Button* ResumeButton = _SPauseMenuPanel->makeButton(ResumeButtonPosition.x, ResumeButtonPosition.y,
															   ResumeButtonSize.x, ResumeButtonSize.y,"");

	ResumeButton->setPressedCallback(this, &PauseState::_ButtonRemusePressed);
	ResumeButton->setBackgroundImage("ButtonResumeOvered","ButtonResumeNotOvered", "ButtonResumeInactive", "ButtonResumeClicked");

	Ogre::Vector2  RestartButtonPosition((window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_PauseStateRestartPosition.x)/
										  ShareData::GameConfigurations::UIConfigurations::NativeWResolition,
										 (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_PauseStateRestartPosition.y)/
										  ShareData::GameConfigurations::UIConfigurations::NativeHResolition);

	Ogre::Vector2  RestartButtonSize((window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_PauseStateRestartSize.x)/
									  ShareData::GameConfigurations::UIConfigurations::NativeWResolition,
									 (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_PauseStateRestartSize.y)/
									  ShareData::GameConfigurations::UIConfigurations::NativeHResolition);

	Gui3D::Button* ResartButton = _SPauseMenuPanel->makeButton(RestartButtonPosition.x, RestartButtonPosition.y,
															   RestartButtonSize.x, RestartButtonSize.y,"");

	ResartButton->setPressedCallback(this, &PauseState::_ButtonRestartPressed);
	ResartButton->setBackgroundImage("ButtonRestartOvered","ButtonRestartNotOvered", "ButtonRestartInactive", "ButtonRestartClicked");

	Ogre::Vector2  MainMenuButtonPosition((window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_PauseStateMainMenuPosition.x)/
										   ShareData::GameConfigurations::UIConfigurations::NativeWResolition,
										  (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_PauseStateMainMenuPosition.y)/
										   ShareData::GameConfigurations::UIConfigurations::NativeHResolition);

	Ogre::Vector2  MainMenuButtonSize((window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_PauseStateMainMenuSize.x)/
									   ShareData::GameConfigurations::UIConfigurations::NativeWResolition,
									  (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_PauseStateMainMenuSize.y)/
									   ShareData::GameConfigurations::UIConfigurations::NativeHResolition);

	Gui3D::Button* MainMenuButton = _SPauseMenuPanel->makeButton(MainMenuButtonPosition.x, MainMenuButtonPosition.y,
															     MainMenuButtonSize.x, MainMenuButtonSize.y,"");

	MainMenuButton->setPressedCallback(this, &PauseState::_ButtonMainMenuPressed);
	MainMenuButton->setBackgroundImage("ButtonMainMenuOvered","ButtonMainMenuNotOvered", "ButtonMainMenuInactive", "ButtonMainMenuClicked");
	//#################################################BUTTONS########################################################

	//#################################################MOUSE########################################################
	_NormalizedMousePosition = Ogre::Vector2(0.5, 0.5);

	_MousePointerLayer = _Gui3D->getScreen("pauseScreen")->createLayer(15);

	Ogre::Real xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Mouse_Size.x)/
					    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	Ogre::Real ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Mouse_Size.y)/
						ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	_MousePointer = _MousePointerLayer->createRectangle(_CurrentCamera->getViewport()->getActualWidth()/2, 
														_CurrentCamera->getViewport()->getActualHeight()/2, xSize, ySize);
	_MousePointer->background_image("mousepointer");

	_SPauseMenuPanel->hideInternalMousePointer();
	//#################################################MOUSE########################################################
}

void PauseState::releaseUI()
{
	_Gui3D->destroyScreen("pauseScreen");
}

bool PauseState::keyPressed( const OIS::KeyEvent &e )
{
	return true;
}	

bool PauseState::keyReleased( const OIS::KeyEvent &e )
{	
	return true;
}
 
bool PauseState::mouseMoved( const OIS::MouseEvent &e )
{		

	// Set the new camera smooth direction movement
	Ogre::Vector2 distance(_getScreenCenterMouseDistance());        
		
	// Raycast for the actual panel
	Ogre::Real xMove = static_cast<Ogre::Real>(e.state.X.rel);
	Ogre::Real yMove = static_cast<Ogre::Real>(e.state.Y.rel);
	
	_NormalizedMousePosition.x += xMove / _CurrentCamera->getViewport()->getActualWidth();
	_NormalizedMousePosition.y += yMove / _CurrentCamera->getViewport()->getActualHeight();

	_NormalizedMousePosition.x = std::max<Ogre::Real>(_NormalizedMousePosition.x, 0);
	_NormalizedMousePosition.y = std::max<Ogre::Real>(_NormalizedMousePosition.y, 0);
	_NormalizedMousePosition.x = std::min<Ogre::Real>(_NormalizedMousePosition.x, 1);
	_NormalizedMousePosition.y = std::min<Ogre::Real>(_NormalizedMousePosition.y, 1);

	_MousePointer->position(_NormalizedMousePosition.x * _CurrentCamera->getViewport()->getActualWidth(), 
							_NormalizedMousePosition.y * _CurrentCamera->getViewport()->getActualHeight());

	_SPauseMenuPanel->injectMouseMoved(_NormalizedMousePosition.x * _CurrentCamera->getViewport()->getActualWidth(), 
									   _NormalizedMousePosition.y * _CurrentCamera->getViewport()->getActualHeight());

	return true;
}

bool PauseState::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	_SPauseMenuPanel->injectMousePressed(e,id);
	return true;
}

bool PauseState::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{	
	_SPauseMenuPanel->injectMouseReleased(e,id);
	return true;
} 

bool PauseState::_ButtonRemusePressed(Gui3D::PanelElement* e)
{	
	_Resume = true;
	return true;
}

bool PauseState::_ButtonRestartPressed(Gui3D::PanelElement* e)
{	
	_Restart = true;
	return true;
}

bool PauseState::_ButtonMainMenuPressed(Gui3D::PanelElement* e)
{	
	_MainMenu = true;		
	return true;
}

bool PauseState::povMoved( const OIS::JoyStickEvent &e, int pov )
{
	return true;
}

bool PauseState::axisMoved( const OIS::JoyStickEvent &e, int axis )
{
	return true;
}

bool PauseState::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )
{
	return true;
}

bool PauseState::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool PauseState::buttonReleased( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool PauseState::frameStarted(const Ogre::FrameEvent& evt)
{	
	return true;
}

bool PauseState::frameRenderingQueued(const Ogre::FrameEvent& evt)
{	
	return true;
}

bool PauseState::frameEnded(const Ogre::FrameEvent& evt)
{
	if (_Resume)
		popState();

	if (_Restart)
	{
		popState();
		Levels::LevelManager::getSingletonPtr()->setGameLevelSceneToLoad(Levels::Play);
		changeState(LoadingState::getInstance());
	}

	if(_MainMenu)
	{
		popState();
		Levels::LevelManager::getSingletonPtr()->setGameLevelSceneToLoad(Levels::MainMenu);
		changeState(MainMenuState::getInstance());	
	}

	return true;
}

Ogre::Vector2 PauseState::_getScreenCenterMouseDistance()
{
	Ogre::Real posX = (_MousePointer->position().x - _CurrentCamera->getViewport()->getActualWidth()) / _CurrentCamera->getViewport()->getActualWidth();
	Ogre::Real posY = (_MousePointer->position().y - _CurrentCamera->getViewport()->getActualHeight()) / _CurrentCamera->getViewport()->getActualHeight();

	return Ogre::Vector2(posX + 0.5, posY + 0.5);
}
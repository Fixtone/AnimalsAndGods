#include "stdafx.h"
#include "../../Header/GameStates/MainMenuState.h"

MainMenuState MainMenuState::_MainMenuState;

void MainMenuState::enter()
{
	mRoot = Ogre::Root::getSingletonPtr();		
	mSceneMgr = mRoot->getSceneManager("AnimalsAndGodsSceneManager");	

	Levels::LevelManager::getSingletonPtr()->loadResourcesGameLevelScene(Levels::MainMenu);

	GameManager::getSingletonPtr()->getSceneManager()->setAmbientLight(Ogre::ColourValue::White);

	Cameras::CameraManager::getSingletonPtr()->createCamera(ShareData::GameConfigurations::CameraConfigurations::STATIC,
															"MainMenuCam", Ogre::Vector3(0, 10, 30), 
															Ogre::Quaternion::IDENTITY*Ogre::Vector3::NEGATIVE_UNIT_Z);
	
	Cameras::CameraManager::getSingletonPtr()->setActiveCamera("MainMenuCam");

	_CurrentCamera = GameManager::getSingletonPtr()->getCamera();
	_Gui3D = UI::GUI3DManager::getSingletonPtr()->getGUI3D();

	//Create background rectangle covering the whole screen
	_MainMenuRect = new Ogre::Rectangle2D(true);
	_MainMenuRect->setCorners(-1.0, 1.0, 1.0, -1.0);
	_MainMenuRect->setMaterial("MainMenu_Mat");
		
	// Use infinite AAB to always stay visible
	Ogre::AxisAlignedBox aabInf;	
	aabInf.setInfinite();
	_MainMenuRect->setBoundingBox(aabInf);

	_MainMenuRectNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MainMenu_Node");
	_MainMenuRectNode->attachObject(_MainMenuRect);			
	
	MenuLoader* menuLoader = new MenuLoader();
	_MenuData = menuLoader->loadMenuConfig("config.xml","MainMenu");
	delete menuLoader;

	Music::SoundManager::getSingletonPtr()->loadAudio(".\\Resources\\MainMenu\\Music\\Play_Coevolution.ogg", &_MusicMM_AmbientId, true);
	Music::SoundManager::getSingletonPtr()->loadAudio(".\\Resources\\MainMenu\\Sounds\\ButtonClick.ogg", &_SoundMM_ButtonClickId, false);
	
	Music::SoundManager::getSingletonPtr()->setListenerPosition(Ogre::Vector3::ZERO,Ogre::Vector3::ZERO,Ogre::Quaternion::IDENTITY);
	Music::SoundManager::getSingletonPtr()->playAudio(_MusicMM_AmbientId, true);		

	_ExitGame = false;
	_ChangeGameState = false;
	_CurrentStoryPage = 0;
}
 
void MainMenuState::exit()
{	
	Music::SoundManager::getSingletonPtr()->stopAudio(_MusicMM_AmbientId);
	Music::SoundManager::getSingletonPtr()->stopAudio(_SoundMM_ButtonClickId);
	Music::SoundManager::getSingletonPtr()->stopAllAudio();

	delete _MainMenuRect;
	Tools::Destroy(mSceneMgr,_MainMenuRectNode->getName());

	Cameras::CameraManager::getSingletonPtr()->removeCustomCameraByName("MainMenuCam");
	Levels::LevelManager::getSingletonPtr()->unloadResourcesGameLevelScene(Levels::MainMenu);
	mSceneMgr->clearScene();
}

void MainMenuState::pause()
{
}
 
void MainMenuState::resume()
{	
}

void MainMenuState::createUI()
{	
	 Gorilla::Screen* myScreen = _Gui3D->createScreen(_CurrentCamera->getViewport(), "MainMenu", "mainMenu_Screen", "MainMenu");	 
	
	_Gui3D->getPanelColors()->panelBackgroundSpriteName = "none";
	_Gui3D->getPanelColors()->panelGradientType = Gorilla::Gradient_NorthSouth;
	_Gui3D->getPanelColors()->panelGradientColorStart = Gorilla::rgb(0, 0, 0, 0);
	_Gui3D->getPanelColors()->panelGradientColorEnd = Gorilla::rgb(0, 0, 0, 0);
	_Gui3D->getPanelColors()->captionTextSize = 27;
	_Gui3D->getPanelColors()->buttonTextSize = 27;

	Ogre::RenderWindow* window =  GameManager::getSingletonPtr()->getRenderWindow();

	//##Button Exit	
	Ogre::Real xPos = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_ExitPositon.x)/
					   ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	Ogre::Real yPos = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_ExitPositon.y)/
					   ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	Ogre::Real xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_ExitSize.x)/
					    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	Ogre::Real ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_ExitSize.y)/
					    ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	_SPanelExit = new Gui3D::ScreenPanel(_Gui3D, myScreen,
										 Ogre::Vector2(xPos, yPos),
										 Ogre::Vector2(xSize, ySize),													   
										 "MainMenu", "buttonExit_Panel");	
	
	Gui3D::Button* mainMenuButton;
	mainMenuButton = _SPanelExit->makeButton(0, 0, xSize, ySize, "");
	mainMenuButton->setPressedCallback(this, &MainMenuState::_ButtonExitPressed);
	mainMenuButton->setBackgroundImage("buttonExitOvered","buttonExitNotOvered", "buttonExitInactive", "buttonExitClicked");

	//##Button Play
	xPos = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_PlayPositon.x)/
		   ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	yPos = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_PlayPositon.y)/
		   ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_PlaySize.x)/
		    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_PlaySize.y)/
		    ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	_SPanelPlay = new Gui3D::ScreenPanel(_Gui3D, myScreen,
										 Ogre::Vector2(xPos, yPos),
										 Ogre::Vector2(xSize, ySize),													   
										 "MainMenu", "buttonPlay_Panel");	
		
	mainMenuButton = _SPanelPlay->makeButton(0, 0, xSize, ySize, "");
	mainMenuButton->setPressedCallback(this, &MainMenuState::_ButtonPlayPressed);
	mainMenuButton->setBackgroundImage("buttonPlayOvered","buttonPlayNotOvered", "buttonPlayInactive", "buttonPlayClicked");


	//##Button Story
	xPos = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_StoryPositon.x)/
		   ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	yPos = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_StoryPositon.y)/
		   ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_StorySize.x)/
		    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_StorySize.y)/
		    ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	_SPanelStory = new Gui3D::ScreenPanel(_Gui3D, myScreen,
										  Ogre::Vector2(xPos, yPos),
										  Ogre::Vector2(xSize, ySize),													   
										  "MainMenu", "buttonStory_Panel");	
		
	mainMenuButton = _SPanelStory->makeButton(0, 0, xSize, ySize, "");
	mainMenuButton->setPressedCallback(this, &MainMenuState::_ButtonStoryPressed);
	mainMenuButton->setBackgroundImage("buttonStoryOvered","buttonStoryNotOvered", "buttonStoryInactive", "buttonStoryClicked");

	//##Button Credits
	xPos = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_CreditsPositon.x)/
		   ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	yPos = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_CreditsPositon.y)/
		   ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_CreditsSize.x)/
		    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_CreditsSize.y)/
		    ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	_SPanelCredits = new Gui3D::ScreenPanel(_Gui3D, myScreen,
											Ogre::Vector2(xPos, yPos),
										    Ogre::Vector2(xSize, ySize),													   
										    "MainMenu", "buttonCredits_Panel");	
		
	mainMenuButton = _SPanelCredits->makeButton(0, 0, xSize, ySize, "");
	mainMenuButton->setPressedCallback(this, &MainMenuState::_ButtonCreditsPressed);
	mainMenuButton->setBackgroundImage("buttonCreditsOvered","buttonCreditsNotOvered", "buttonCreditsInactive", "buttonCreditsClicked");

	//##Button Options
	xPos = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_OptionsPositon.x)/
		   ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	yPos = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_OptionsPositon.y)/
		   ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_OptionsSize.x)/
		    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_OptionsSize.y)/
		    ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	_SPanelOptions = new Gui3D::ScreenPanel(_Gui3D, myScreen,
											Ogre::Vector2(xPos, yPos),
										    Ogre::Vector2(xSize, ySize),													   
										    "MainMenu", "buttonOptions_Panel");	
		
	mainMenuButton = _SPanelOptions->makeButton(0, 0, xSize, ySize, "");
	mainMenuButton->setPressedCallback(this, &MainMenuState::_ButtonOptionsPressed);
	mainMenuButton->setBackgroundImage("buttonOptionsOvered","buttonOptionsNotOvered", "buttonOptionsInactive", "buttonOptionsClicked");

	//##Button Help
	xPos = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_HelpPositon.x)/
		   ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	yPos = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_HelpPositon.y)/
		   ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_HelpsSize.x)/
		    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_HelpsSize.y)/
		    ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	_SPanelHelp = new Gui3D::ScreenPanel(_Gui3D, myScreen,
										 Ogre::Vector2(xPos, yPos),
										 Ogre::Vector2(xSize, ySize),													   
										 "MainMenu", "buttonHelp_Panel");	
		
	mainMenuButton = _SPanelHelp->makeButton(0, 0, xSize, ySize, "");
	mainMenuButton->setPressedCallback(this, &MainMenuState::_ButtonHelpPressed);
	mainMenuButton->setBackgroundImage("buttonHelpOvered","buttonHelpNotOvered", "buttonHelpInactive", "buttonHelpClicked");

	//#################################################################################################################### MENU STORY
	_Gui3D->getPanelColors()->panelGradientType = Gorilla::Gradient_NorthSouth;
	_Gui3D->getPanelColors()->panelGradientColorStart = Gorilla::rgb(0, 0, 0, 240);
	_Gui3D->getPanelColors()->panelGradientColorEnd = Gorilla::rgb(0, 0, 0, 240);
	_SMenuPanelStory = new Gui3D::ScreenPanel(_Gui3D, myScreen, Ogre::Vector2((window->getWidth()/2)-400, (window->getHeight()/2)-300), 
											  Ogre::Vector2(800, 600), "MainMenu", "storyMenu_Panel");
	

	xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_BackSize.x)/
		    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_BackSize.y)/
		    ShareData::GameConfigurations::UIConfigurations::NativeHResolition;
	
	mainMenuButton = _SMenuPanelStory->makeButton(400 - xSize/2,
												  600 - ySize, xSize, ySize,"");
	mainMenuButton->setPressedCallback(this, &MainMenuState::_ButtonBackStoryPressed);
	mainMenuButton->setBackgroundImage("buttonBackOvered","buttonBackNotOvered", "buttonBackInactive", "buttonBackClicked");
			
	xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_LeftSize.x)/
		    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_LeftSize.y)/
		    ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	mainMenuButton = _SMenuPanelStory->makeButton(0,600-ySize,xSize,ySize,"");	
	mainMenuButton->setPressedCallback(this, &MainMenuState::_ButtonBackPageStoryPressed);
	mainMenuButton->setBackgroundImage("buttonLeftPagOvered","buttonLeftPagNotOvered", "buttonLeftPagInactive", "buttonLeftPagClicked");
	
	xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_RightSize.x)/
		    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_RightSize.y)/
		    ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	mainMenuButton = _SMenuPanelStory->makeButton(800-xSize,600-ySize,xSize,ySize,"");
	mainMenuButton->setPressedCallback(this, &MainMenuState::_ButtonNextPageStoryPressed);
	mainMenuButton->setBackgroundImage("buttonRightPagOvered","buttonRightPagNotOvered", "buttonRightPagInactive", "buttonRightPagClicked");

	_SrotyNumberPagCaption = _SMenuPanelStory->makeCaption(370,500,60,20,"-" + Ogre::StringConverter::toString(_CurrentStoryPage+1) + "-",Gorilla::TextAlign_Centre, Gorilla::VerticalAlign_Top);

	for(Ogre::uint i = 0; i<_MenuData.mStory["ESP"][_CurrentStoryPage].mLines.size(); i++)
	{
		Ogre::String line = _MenuData.mStory["ESP"][_CurrentStoryPage].mLines[i];
		_StoryPageCaptions.push_back(_SMenuPanelStory->makeCaption(10,(26*i),780,40,line,Gorilla::TextAlign_Centre, Gorilla::VerticalAlign_Top));
	}

	_SMenuPanelStory->hideInternalMousePointer(); 
	_SMenuPanelStory->getGUILayer()->setVisible(false);	
	//#################################################################################################################### MENU STORY
	//#################################################################################################################### MENU CREDITS
	_Gui3D->getPanelColors()->panelGradientType = Gorilla::Gradient_NorthSouth;
	_Gui3D->getPanelColors()->panelGradientColorStart = Gorilla::rgb(0, 0, 0, 240);
	_Gui3D->getPanelColors()->panelGradientColorEnd = Gorilla::rgb(0, 0, 0, 240);
	_SMenuPanelCredits = new Gui3D::ScreenPanel(_Gui3D, myScreen, Ogre::Vector2((window->getWidth()/2)-400, (window->getHeight()/2)-300), 
											    Ogre::Vector2(800, 600), "MainMenu", "creditsMenu_Panel");
	
	Gui3D::Button* creditsSplash = _SMenuPanelCredits->makeButton(0,0,800,530,"");
	creditsSplash->setBackgroundImage("creditsSplashImg","creditsSplashImg", "creditsSplashImg", "creditsSplashImg");

	xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_BackSize.x)/
		    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_BackSize.y)/
		    ShareData::GameConfigurations::UIConfigurations::NativeHResolition;
	
	mainMenuButton = _SMenuPanelCredits->makeButton(400 - xSize/2,
												    600 - ySize, xSize, ySize,"");
	mainMenuButton->setPressedCallback(this, &MainMenuState::_ButtonBackCreditsPressed);
	mainMenuButton->setBackgroundImage("buttonBackOvered","buttonBackNotOvered", "buttonBackInactive", "buttonBackClicked");

	_SMenuPanelCredits->hideInternalMousePointer();
	_SMenuPanelCredits->getGUILayer()->setVisible(false);
	//#################################################################################################################### MENU CREDITS
	//#################################################################################################################### MENU HELP
	_Gui3D->getPanelColors()->panelGradientType = Gorilla::Gradient_NorthSouth;
	_Gui3D->getPanelColors()->panelGradientColorStart = Gorilla::rgb(0, 0, 0, 240);
	_Gui3D->getPanelColors()->panelGradientColorEnd = Gorilla::rgb(0, 0, 0, 240);
	_SMenuPanelHelp = new Gui3D::ScreenPanel(_Gui3D, myScreen, Ogre::Vector2((window->getWidth()/2)-400, (window->getHeight()/2)-300), 
											 Ogre::Vector2(800, 600), "MainMenu", "helpMenu_Panel");	

	Gui3D::Button* helpSplash = _SMenuPanelHelp->makeButton(0,0,800,530,"");
	helpSplash->setBackgroundImage("helpSplashImg","helpSplashImg", "helpSplashImg", "helpSplashImg");

	xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Btn_BackSize.x)/
		    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Btn_BackSize.y)/
		    ShareData::GameConfigurations::UIConfigurations::NativeHResolition;
	
	mainMenuButton = _SMenuPanelHelp->makeButton(400 - xSize/2,
												 600 - ySize, xSize, ySize,"");
	mainMenuButton->setPressedCallback(this, &MainMenuState::_ButtonBackHelpPressed);
	mainMenuButton->setBackgroundImage("buttonBackOvered","buttonBackNotOvered", "buttonBackInactive", "buttonBackClicked");

	_SMenuPanelHelp->hideInternalMousePointer();
	_SMenuPanelHelp->getGUILayer()->setVisible(false);
	//#################################################################################################################### MENU HELP

	// Create a layer for the mousePointer
	mNormalizedMousePosition = Ogre::Vector2(0.5, 0.5);

	mMousePointerLayer = _Gui3D->getScreen("mainMenu_Screen")->createLayer(15);

	xSize = (window->getWidth()*ShareData::GameConfigurations::UIConfigurations::Mouse_Size.x)/
		    ShareData::GameConfigurations::UIConfigurations::NativeWResolition;
	ySize = (window->getHeight()*ShareData::GameConfigurations::UIConfigurations::Mouse_Size.y)/
		    ShareData::GameConfigurations::UIConfigurations::NativeHResolition;

	mMousePointer = mMousePointerLayer->createRectangle(_CurrentCamera->getViewport()->getActualWidth()/2, 
														_CurrentCamera->getViewport()->getActualHeight()/2, xSize, ySize);
	mMousePointer->background_image("mousepointer");

	_SPanelExit->hideInternalMousePointer();	
	_SPanelPlay->hideInternalMousePointer();
	_SPanelStory->hideInternalMousePointer();
	_SPanelCredits->hideInternalMousePointer();
	_SPanelOptions->hideInternalMousePointer();
}

void MainMenuState::releaseUI()
{
	_Gui3D->destroyScreen("mainMenu_Screen");
	_StoryPageCaptions.clear();
}

bool MainMenuState::keyPressed( const OIS::KeyEvent &e )
{	
#ifdef _DEBUG_
	if (e.key == OIS::KC_ESCAPE)	
		_ExitGame = true;
#endif
	return true;
}	

bool MainMenuState::keyReleased( const OIS::KeyEvent &e )
{		
	return true;
}
 
bool MainMenuState::mouseMoved( const OIS::MouseEvent &e )
{	
	// Set the new camera smooth direction movement
	Ogre::Vector2 distance(_getScreenCenterMouseDistance());        
		
	// Raycast for the actual panel
	Ogre::Real xMove = static_cast<Ogre::Real>(e.state.X.rel);
	Ogre::Real yMove = static_cast<Ogre::Real>(e.state.Y.rel);
	
	mNormalizedMousePosition.x += xMove / _CurrentCamera->getViewport()->getActualWidth();
	mNormalizedMousePosition.y += yMove / _CurrentCamera->getViewport()->getActualHeight();

	mNormalizedMousePosition.x = std::max<Ogre::Real>(mNormalizedMousePosition.x, 0);
	mNormalizedMousePosition.y = std::max<Ogre::Real>(mNormalizedMousePosition.y, 0);
	mNormalizedMousePosition.x = std::min<Ogre::Real>(mNormalizedMousePosition.x, 1);
	mNormalizedMousePosition.y = std::min<Ogre::Real>(mNormalizedMousePosition.y, 1);

	mMousePointer->position(mNormalizedMousePosition.x * _CurrentCamera->getViewport()->getActualWidth(), 
							mNormalizedMousePosition.y * _CurrentCamera->getViewport()->getActualHeight());

	_SPanelExit->injectMouseMoved(mNormalizedMousePosition.x * _CurrentCamera->getViewport()->getActualWidth(),
								  mNormalizedMousePosition.y * _CurrentCamera->getViewport()->getActualHeight());


	_SPanelPlay->injectMouseMoved(mNormalizedMousePosition.x * _CurrentCamera->getViewport()->getActualWidth(),
								  mNormalizedMousePosition.y * _CurrentCamera->getViewport()->getActualHeight());

	_SPanelStory->injectMouseMoved(mNormalizedMousePosition.x * _CurrentCamera->getViewport()->getActualWidth(),
								   mNormalizedMousePosition.y * _CurrentCamera->getViewport()->getActualHeight());

	_SPanelCredits->injectMouseMoved(mNormalizedMousePosition.x * _CurrentCamera->getViewport()->getActualWidth(),
								     mNormalizedMousePosition.y * _CurrentCamera->getViewport()->getActualHeight());

	_SPanelOptions->injectMouseMoved(mNormalizedMousePosition.x * _CurrentCamera->getViewport()->getActualWidth(),
								     mNormalizedMousePosition.y * _CurrentCamera->getViewport()->getActualHeight());

	_SPanelHelp->injectMouseMoved(mNormalizedMousePosition.x * _CurrentCamera->getViewport()->getActualWidth(),
				 			      mNormalizedMousePosition.y * _CurrentCamera->getViewport()->getActualHeight());

	_SMenuPanelStory->injectMouseMoved(mNormalizedMousePosition.x * _CurrentCamera->getViewport()->getActualWidth(),
				 					   mNormalizedMousePosition.y * _CurrentCamera->getViewport()->getActualHeight());

	_SMenuPanelCredits->injectMouseMoved(mNormalizedMousePosition.x * _CurrentCamera->getViewport()->getActualWidth(),
				 						 mNormalizedMousePosition.y * _CurrentCamera->getViewport()->getActualHeight());

	_SMenuPanelHelp->injectMouseMoved(mNormalizedMousePosition.x * _CurrentCamera->getViewport()->getActualWidth(),
				 					  mNormalizedMousePosition.y * _CurrentCamera->getViewport()->getActualHeight());

	return true;
}

bool MainMenuState::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{	
	_SPanelExit->injectMousePressed(e, id);
	_SPanelPlay->injectMousePressed(e, id);
	_SPanelStory->injectMousePressed(e, id);
	_SPanelCredits->injectMousePressed(e, id);
	_SPanelOptions->injectMousePressed(e, id);
	_SPanelHelp->injectMousePressed(e, id);
	_SMenuPanelStory->injectMousePressed(e, id);
	_SMenuPanelCredits->injectMousePressed(e, id);
	_SMenuPanelHelp->injectMousePressed(e, id);
	return true;
}

bool MainMenuState::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{	
	_SPanelExit->injectMouseReleased(e, id);
	_SPanelPlay->injectMouseReleased(e, id);
	_SPanelStory->injectMouseReleased(e, id);
	_SPanelCredits->injectMouseReleased(e, id);
	_SPanelOptions->injectMouseReleased(e, id);
	_SPanelHelp->injectMouseReleased(e, id);
	_SMenuPanelStory->injectMouseReleased(e, id);
	_SMenuPanelCredits->injectMouseReleased(e, id);
	_SMenuPanelHelp->injectMouseReleased(e, id);
	return true;
} 

bool MainMenuState::povMoved( const OIS::JoyStickEvent &e, int pov )
{
	return true;
}

bool MainMenuState::axisMoved( const OIS::JoyStickEvent &e, int axis )
{
	return true;
}

bool MainMenuState::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )
{
	return true;
}

bool MainMenuState::buttonPressed( const OIS::JoyStickEvent &e, int button )
{

	return true;
}

bool MainMenuState::_ButtonExitPressed(Gui3D::PanelElement* e)
{
	_ExitGame = true;
	return true;
}

bool MainMenuState::_ButtonPlayPressed(Gui3D::PanelElement* e)
{
	_ChangeGameState = true;	
	return true;
}

bool MainMenuState::_ButtonStoryPressed(Gui3D::PanelElement* e)
{	
	_SPanelExit->getGUILayer()->hide();
	_SPanelPlay->getGUILayer()->hide();
	_SPanelStory->getGUILayer()->hide();
	_SPanelCredits->getGUILayer()->hide();
	_SPanelOptions->getGUILayer()->hide();
	_SPanelHelp->getGUILayer()->hide();
	_SMenuPanelStory->getGUILayer()->show();
	Music::SoundManager::getSingletonPtr()->playAudio(_SoundMM_ButtonClickId, true);	
	return true;
}

bool MainMenuState::_ButtonBackStoryPressed(Gui3D::PanelElement* e)
{
	_SPanelExit->getGUILayer()->show();
	_SPanelPlay->getGUILayer()->show();
	_SPanelStory->getGUILayer()->show();
	_SPanelCredits->getGUILayer()->show();
	_SPanelOptions->getGUILayer()->show();
	_SPanelHelp->getGUILayer()->show();
	_SMenuPanelStory->getGUILayer()->hide();
	Music::SoundManager::getSingletonPtr()->playAudio(_SoundMM_ButtonClickId, true);	
	return true;
}

bool MainMenuState::_ButtonBackCreditsPressed(Gui3D::PanelElement* e)
{
	_SPanelExit->getGUILayer()->show();
	_SPanelPlay->getGUILayer()->show();
	_SPanelStory->getGUILayer()->show();
	_SPanelCredits->getGUILayer()->show();
	_SPanelOptions->getGUILayer()->show();
	_SPanelHelp->getGUILayer()->show();
	_SMenuPanelCredits->getGUILayer()->hide();
	Music::SoundManager::getSingletonPtr()->playAudio(_SoundMM_ButtonClickId, true);	
	return true;
}

bool MainMenuState::_ButtonCreditsPressed(Gui3D::PanelElement* e)
{	
	_SPanelExit->getGUILayer()->hide();
	_SPanelPlay->getGUILayer()->hide();
	_SPanelStory->getGUILayer()->hide();
	_SPanelCredits->getGUILayer()->hide();
	_SPanelOptions->getGUILayer()->hide();
	_SPanelHelp->getGUILayer()->hide();
	_SMenuPanelCredits->getGUILayer()->show();
	Music::SoundManager::getSingletonPtr()->playAudio(_SoundMM_ButtonClickId, true);	
	return true;
}

bool MainMenuState::_ButtonOptionsPressed(Gui3D::PanelElement* e)
{		
	return true;
}

bool MainMenuState::_ButtonBackHelpPressed(Gui3D::PanelElement* e)
{
	_SPanelExit->getGUILayer()->show();
	_SPanelPlay->getGUILayer()->show();
	_SPanelStory->getGUILayer()->show();
	_SPanelCredits->getGUILayer()->show();
	_SPanelOptions->getGUILayer()->show();
	_SPanelHelp->getGUILayer()->show();
	_SMenuPanelHelp->getGUILayer()->hide();
	Music::SoundManager::getSingletonPtr()->playAudio(_SoundMM_ButtonClickId, true);	
	return true;
}

bool MainMenuState::_ButtonHelpPressed(Gui3D::PanelElement* e)
{	
	_SPanelExit->getGUILayer()->hide();
	_SPanelPlay->getGUILayer()->hide();
	_SPanelStory->getGUILayer()->hide();
	_SPanelCredits->getGUILayer()->hide();
	_SPanelOptions->getGUILayer()->hide();
	_SPanelHelp->getGUILayer()->hide();
	_SMenuPanelHelp->getGUILayer()->show();
	Music::SoundManager::getSingletonPtr()->playAudio(_SoundMM_ButtonClickId, true);	
	return true;
}

bool MainMenuState::_ButtonBackPageStoryPressed(Gui3D::PanelElement* e)
{
	_CurrentStoryPage--;
	if(_CurrentStoryPage<0)
		_CurrentStoryPage = _MenuData.mStory["ESP"].size()-1;
	
	_SrotyNumberPagCaption->text("-" + Ogre::StringConverter::toString(_CurrentStoryPage+1) + "-");
	this->_MakeStoryPage();
	
	Music::SoundManager::getSingletonPtr()->playAudio(_SoundMM_ButtonClickId, true);	

	return true;
}

bool MainMenuState::_ButtonNextPageStoryPressed(Gui3D::PanelElement* e)
{
	_CurrentStoryPage++;
	if(_CurrentStoryPage==_MenuData.mStory["ESP"].size())
		_CurrentStoryPage = 0;
	
	_SrotyNumberPagCaption->text("-" + Ogre::StringConverter::toString(_CurrentStoryPage+1) + "-");
	this->_MakeStoryPage();

	Music::SoundManager::getSingletonPtr()->playAudio(_SoundMM_ButtonClickId, true);	

	return true;
}

bool MainMenuState::buttonReleased( const OIS::JoyStickEvent &e, int button )
{	
	return true;
}

bool MainMenuState::frameStarted(const Ogre::FrameEvent& evt)
{
	return true;
}

bool MainMenuState::frameRenderingQueued(const Ogre::FrameEvent& evt)
{	
	return true;
}

bool MainMenuState::frameEnded(const Ogre::FrameEvent& evt)
{
	if (_ExitGame)
		return false;

	if (_ChangeGameState)
	{
		Levels::LevelManager::getSingletonPtr()->setGameLevelSceneToLoad(Levels::Play);
		changeState(LoadingState::getInstance());	
	}


	return true;
}

// Calculate and normalize the distance between the middle of the screen 
//  and the mouse on both X and Y axis.
// This is used for the smooth movement of the camera
//  when the mouse is moving.
Ogre::Vector2 MainMenuState::_getScreenCenterMouseDistance()
{
	Ogre::Real posX = (mMousePointer->position().x - _CurrentCamera->getViewport()->getActualWidth()) / _CurrentCamera->getViewport()->getActualWidth();
	Ogre::Real posY = (mMousePointer->position().y - _CurrentCamera->getViewport()->getActualHeight()) / _CurrentCamera->getViewport()->getActualHeight();

	return Ogre::Vector2(posX + 0.5, posY + 0.5);
}

void MainMenuState::_MakeStoryPage()
{
	for(std::vector<Gui3D::Caption*>::iterator it = _StoryPageCaptions.begin(); it<_StoryPageCaptions.end(); it++)
		(*it)->text("");	

	for(Ogre::uint i = 0; i<_MenuData.mStory["ESP"][_CurrentStoryPage].mLines.size(); i++)		
		_StoryPageCaptions[i]->text(_MenuData.mStory["ESP"][_CurrentStoryPage].mLines[i]);

}

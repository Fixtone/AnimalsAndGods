#include "stdafx.h"
#include "../../Header/GameStates/LoadingState.h"
  
LoadingState LoadingState::mLoadingState; 

void LoadingState::enter()
{ 	
	mRoot = Ogre::Root::getSingletonPtr();		
	mSceneMgr = mRoot->getSceneManager("AnimalsAndGodsSceneManager");
	
	GameManager::getSingletonPtr()->getSceneManager()->setAmbientLight(Ogre::ColourValue::White);	
	
	Cameras::CameraManager::getSingletonPtr()->createCamera(ShareData::GameConfigurations::CameraConfigurations::STATIC,
															"LoadingCam", Ogre::Vector3::ZERO, Ogre::Vector3::ZERO);
	Cameras::CameraManager::getSingletonPtr()->setActiveCamera("LoadingCam");

	_CurrentCamera = GameManager::getSingletonPtr()->getCamera();
	_Gui3D = UI::GUI3DManager::getSingletonPtr()->getGUI3D();

	Levels::LevelManager::getSingletonPtr()->loadResourcesGameLevelScene(Levels::Loading);					

	// Create a manual object for 2D
	Ogre::ManualObject* manualIcon = mSceneMgr->createManualObject("manualIcon");

	// Use identity view/projection matrices
	manualIcon->setUseIdentityProjection(true);
	manualIcon->setUseIdentityView(true);

	manualIcon->begin("Loading_Mat", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
	manualIcon->position(0.7f, -0.9f, 0.0);
	manualIcon->textureCoord(0, 1);
	manualIcon->position(0.9f, -0.9f, 0.0);
	manualIcon->textureCoord(1, 1);
	manualIcon->position(0.9f,  -0.7f, 0.0);
	manualIcon->textureCoord(1, 0);
	manualIcon->position(0.7f,  -0.7f, 0.0);
	manualIcon->textureCoord(0, 0);
	manualIcon->index(0);
	manualIcon->index(1);
	manualIcon->index(2);
	manualIcon->index(3);
	manualIcon->index(0);
	manualIcon->end();

	// Use infinite AAB to always stay visible
	Ogre::AxisAlignedBox aabInf;
	aabInf.setInfinite();
	manualIcon->setBoundingBox(aabInf);

	// Render just before overlays
	manualIcon->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);

	//Create a manual object for 2D
	Ogre::ManualObject* manualBack = mSceneMgr->createManualObject("manualBackground");

	// Use identity view/projection matrices
	manualBack->setUseIdentityProjection(true);
	manualBack->setUseIdentityView(true);

	manualBack->begin("LoadingBackground_Mat", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
	manualBack->position(-1, -1, 0);
	manualBack->textureCoord(0, 1);
	manualBack->position(1, -1, 0);
	manualBack->textureCoord(1, 1);
	manualBack->position(1,  1, 0);
	manualBack->textureCoord(1, 0);
	manualBack->position(-1,  1, 0);
	manualBack->textureCoord(0, 0);
	manualBack->index(0);
	manualBack->index(1);
	manualBack->index(2);
	manualBack->index(3);
	manualBack->index(0);
	manualBack->end();

	// Use infinite AAB to always stay visible
	Ogre::AxisAlignedBox aabInfBack;
	aabInfBack.setInfinite();
	manualBack->setBoundingBox(aabInfBack);

	// Render just before overlays
	manualBack->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);

	// Attach to scene
	Ogre::SceneNode* sN = mSceneMgr->getRootSceneNode()->createChildSceneNode("LoadingNodeManuaoObjects#Master");
	sN->createChildSceneNode("LoadingIcon")->attachObject(manualIcon);
	sN->createChildSceneNode("LoadingCharacter")->attachObject(manualBack);		
		
	/*Music::SoundManager::getSingletonPtr()->loadAudio(".\\Resources\\Loading\\Music\\Loading_InnerSanctum.ogg", &_MusicL_AmbientId, true);	
	Music::SoundManager::getSingletonPtr()->setListenerPosition(Ogre::Vector3::ZERO,Ogre::Vector3::ZERO,Ogre::Quaternion::IDENTITY);
	Music::SoundManager::getSingletonPtr()->playAudio(_MusicL_AmbientId,true);*/
}
 
void LoadingState::postEnter()
{	
	Ogre::ResourceGroupManager::getSingletonPtr()->addResourceGroupListener(GameManager::getSingletonPtr());
	Ogre::ResourceGroupManager::getSingletonPtr()->setLoadingListener(GameManager::getSingletonPtr());
	Levels::LevelManager::getSingletonPtr()->loadResourcesGameLevelScene(Levels::LevelManager::getSingletonPtr()->getGameLevelSceneToLoad());

	switch(Levels::LevelManager::getSingletonPtr()->getGameLevelSceneToLoad())
	{		
		case Levels::Play:			
			changeState(PlayState::getInstance());
		break;
	};	
}

void LoadingState::exit()
{	
	/*Music::SoundManager::getSingletonPtr()->stopAudio(_MusicL_AmbientId);
	Music::SoundManager::getSingletonPtr()->stopAllAudio();*/

	Tools::Destroy(mSceneMgr,"LoadingNodeManuaoObjects#Master");

	Cameras::CameraManager::getSingletonPtr()->removeCustomCameraByName("LoadingCam");
	Levels::LevelManager::getSingletonPtr()->unloadResourcesGameLevelScene(Levels::Loading);
	Ogre::ResourceGroupManager::getSingletonPtr()->removeResourceGroupListener(GameManager::getSingletonPtr());
	Ogre::ResourceGroupManager::getSingletonPtr()->setLoadingListener(0);
}
 
void LoadingState::pause()
{
}
 
void LoadingState::resume()
{
}
 
void LoadingState::createUI()
{
	Gorilla::Screen* myScreen = _Gui3D->createScreen(_CurrentCamera->getViewport(), "LoadingAtlas", "loading_Screen", "Loading");	 
	
	_Gui3D->getPanelColors()->panelBackgroundSpriteName = "none";
	_Gui3D->getPanelColors()->panelGradientType = Gorilla::Gradient_NorthSouth;
	_Gui3D->getPanelColors()->panelGradientColorStart = Gorilla::rgb(0, 0, 0, 0);
	_Gui3D->getPanelColors()->panelGradientColorEnd = Gorilla::rgb(0, 0, 0, 0);
	_Gui3D->getPanelColors()->captionTextSize = 27;
	_Gui3D->getPanelColors()->buttonTextSize = 27;

	Ogre::RenderWindow* window =  GameManager::getSingletonPtr()->getRenderWindow();

	Gui3D::ScreenPanel* Panel = new Gui3D::ScreenPanel(_Gui3D, myScreen, 
													   Ogre::Vector2((window->getWidth()/2)-250, 
																	 window->getHeight()-80), 
													   Ogre::Vector2(500, 30), "LoadingAtlas", "loadingScreenPanel");
	
	_ResourcesCaption = Panel->makeCaption(0,0,500,30,"",Gorilla::TextAlign_Centre,Gorilla::VerticalAlign_Middle);
	
	Panel->hideInternalMousePointer();
	mRoot->renderOneFrame();
}

void LoadingState::releaseUI()
{
	_Gui3D->destroyScreen("loading_Screen");	
}

bool LoadingState::keyPressed( const OIS::KeyEvent &e )
{
	return true;
}

bool LoadingState::keyReleased( const OIS::KeyEvent &e )
{
	return true;
}
 
bool LoadingState::mouseMoved( const OIS::MouseEvent &e )
{
	return true;
}

bool LoadingState::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	return true;
}

bool LoadingState::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{	
	return true;
}

bool LoadingState::povMoved( const OIS::JoyStickEvent &e, int pov )
{
	return true;
}

bool LoadingState::axisMoved( const OIS::JoyStickEvent &e, int axis )
{
	return true;
}

bool LoadingState::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )
{
	return true;
}

bool LoadingState::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool LoadingState::buttonReleased( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool LoadingState::frameStarted(const Ogre::FrameEvent& evt)
{	
	/*if(_TotalRousourcesToLoad!=0)
	{		
		float value  = (float) _CurrentRousourcesToLoad/_TotalRousourcesToLoad;		
	}*/

	return true;
}

bool LoadingState::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return true;
}

bool LoadingState::frameEnded(const Ogre::FrameEvent& evt)
{
	return true;
}

// ResourceGroupListener callbacks
void LoadingState::resourceGroupScriptingStarted(const Ogre::String& groupName, size_t scriptCount)
{	
	_ResourcesCaption->text("Assets: Resource Group Scripting Started");
	mRoot->renderOneFrame();
}
void LoadingState::scriptParseStarted(const Ogre::String& scriptName, bool& skipThisScript)
{
	_ResourcesCaption->text("Assets: " + scriptName);
	mRoot->renderOneFrame();
}
void LoadingState::scriptParseEnded(const Ogre::String& scriptName, bool skipped)
{
	_ResourcesCaption->text("Assets: " + scriptName);	
	mRoot->renderOneFrame();
}
void LoadingState::resourceGroupScriptingEnded(const Ogre::String& groupName)
{	
	_ResourcesCaption->text("Assets: Resource Group Scripting Ended");
	mRoot->renderOneFrame();
}
void LoadingState::resourceGroupLoadStarted(const Ogre::String& groupName, size_t resourceCount)
{
	//_TotalRousourcesToLoad +=resourceCount;
	_ResourcesCaption->text("Assets: " + groupName);
	mRoot->renderOneFrame();
}
void LoadingState::resourceLoadStarted(const Ogre::ResourcePtr& resource)
{	
	//_CurrentRousourcesToLoad++;
	_ResourcesCaption->text("FILE: Resource Load Started");
	mRoot->renderOneFrame();
}
void LoadingState::resourceLoadEnded(void)
{	
	_ResourcesCaption->text("Assets: Resource Load Ended");
	mRoot->renderOneFrame();
}
void LoadingState::worldGeometryStageStarted(const Ogre::String& description)
{
	_ResourcesCaption->text("Assets: " + description);
	mRoot->renderOneFrame();
}
void LoadingState::worldGeometryStageEnded(void)
{
	_ResourcesCaption->text("Assets: World Geometry Stage Ended");
	mRoot->renderOneFrame();
}
void LoadingState::resourceGroupLoadEnded(const Ogre::String& groupName)
{
	_ResourcesCaption->text("Assets: Resource Group Load Ended");
	_ResourcesCaption->text("...Creating World...");
	mRoot->renderOneFrame();
}

bool LoadingState::resourceCollision(Ogre::Resource *resource, Ogre::ResourceManager *resourceManager)
{	
	_ResourcesCaption->text("Assets: " + resource->getName());
	mRoot->renderOneFrame();
	return true;
}
Ogre::DataStreamPtr LoadingState::resourceLoading(const Ogre::String &name, const Ogre::String &group, Ogre::Resource *resource)
{	
	_ResourcesCaption->text("Assets: " + name);
	mRoot->renderOneFrame();
	return Ogre::DataStreamPtr();
}
void LoadingState::resourceStreamOpened(const Ogre::String &name, const Ogre::String &group, Ogre::Resource *resource, Ogre::DataStreamPtr &dataStream)
{
	_ResourcesCaption->text("Assets: " + name);
	mRoot->renderOneFrame();
}
#include "stdafx.h"
#include "../../../Header/Loaders/Levels/LevelManager.h"

using namespace Levels;

template<> LevelManager* Ogre::Singleton<LevelManager>::msSingleton = 0;
LevelManager* LevelManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
LevelManager& LevelManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

LevelManager::LevelManager()
{
	_SceneManager = 0;
}

LevelManager::~LevelManager()
{
}

void LevelManager::initializeLevelManager(Ogre::Root* aRoot, Ogre::SceneManager* aSceneManager, Ogre::RenderWindow* aRenderWindow)
{
	_SceneManager = aSceneManager;	
	_Root = aRoot;
	_RenderWindow = aRenderWindow;	
}

void LevelManager::clearLevelManager()
{	
}

void LevelManager::createResourceGroupListener()
{
	Ogre::ResourceGroupManager::getSingleton().addResourceGroupListener(this);
}

void LevelManager::removeResourceGroupListener()
{
	Ogre::ResourceGroupManager::getSingleton().removeResourceGroupListener(this);
}

void LevelManager::loadResourcesGameLevelScene(GameLevelScene aGameLevelSceneToLoad)
{	
	switch(aGameLevelSceneToLoad)
	{
		case Play:
			Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Play");
			Ogre::ResourceGroupManager::getSingleton().loadResourceGroup("Play",true,false);						
		break;
		case Pause:
			Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Pause");
			Ogre::ResourceGroupManager::getSingleton().loadResourceGroup("Pause",true,false);						
		break;
		case MainMenu:
			Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("MainMenu");
			Ogre::ResourceGroupManager::getSingleton().loadResourceGroup("MainMenu",true,false);									
		break;
		case Loading:
			Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Loading");
			Ogre::ResourceGroupManager::getSingleton().loadResourceGroup("Loading",true,false);	
		break;
		case Intro:		
			Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Intro");
			Ogre::ResourceGroupManager::getSingletonPtr()->loadResourceGroup("Intro",true,false);			
		break;
		case Finish:		
			Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Finish");
			Ogre::ResourceGroupManager::getSingletonPtr()->loadResourceGroup("Finish",true,false);			
		break;
		case None:
		break;
	};
}

void LevelManager::unloadResourcesGameLevelScene(GameLevelScene aGameLevelSceneToLoad)
{
	switch(aGameLevelSceneToLoad)
	{
		case Play:
			Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup("Play");
			Ogre::ResourceGroupManager::getSingleton().clearResourceGroup("Play");
		break;
		case Pause:
			Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup("Pause");
			Ogre::ResourceGroupManager::getSingleton().clearResourceGroup("Pause");
		break;
		case MainMenu:
			Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup("MainMenu");
			Ogre::ResourceGroupManager::getSingleton().clearResourceGroup("MainMenu");
		break;
		case Loading:
			Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup("Loading");
			Ogre::ResourceGroupManager::getSingleton().clearResourceGroup("Loading");
		break;
		case Intro:
			Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup("Intro");
			Ogre::ResourceGroupManager::getSingleton().clearResourceGroup("Intro");
		break;
		case Finish:
			Ogre::ResourceGroupManager::getSingleton().unloadResourceGroup("Finish");
			Ogre::ResourceGroupManager::getSingleton().clearResourceGroup("Finish");
		break;
		case None:
		break;
	};
}

// ResourceGroupListener callbacks
void LevelManager::resourceGroupScriptingStarted(const Ogre::String& groupName, size_t scriptCount)
{	
	_Root->renderOneFrame();
}
void LevelManager::scriptParseStarted(const Ogre::String& scriptName, bool& skipThisScript)
{
	_Root->renderOneFrame();
}
void LevelManager::scriptParseEnded(const Ogre::String& scriptName, bool skipped)
{
	_Root->renderOneFrame();
}
void LevelManager::resourceGroupScriptingEnded(const Ogre::String& groupName)
{
	_Root->renderOneFrame();
}
void LevelManager::resourceGroupLoadStarted(const Ogre::String& groupName, size_t resourceCount)
{
	_Root->renderOneFrame();
}
void LevelManager::resourceLoadStarted(const Ogre::ResourcePtr& resource)
{
	_Root->renderOneFrame();
}
void LevelManager::resourceLoadEnded(void)
{
	_Root->renderOneFrame();
}
void LevelManager::worldGeometryStageStarted(const Ogre::String& description)
{
	_Root->renderOneFrame();
}
void LevelManager::worldGeometryStageEnded(void)
{
	_Root->renderOneFrame();
}
void LevelManager::resourceGroupLoadEnded(const Ogre::String& groupName)
{
	_Root->renderOneFrame();
}

bool LevelManager::resourceCollision(Ogre::Resource *resource, Ogre::ResourceManager *resourceManager)
{
	_Root->renderOneFrame();
	return true;
}
Ogre::DataStreamPtr LevelManager::resourceLoading(const Ogre::String &name, const Ogre::String &group, Ogre::Resource *resource)
{	
	_Root->renderOneFrame();
	return Ogre::DataStreamPtr();
}
void LevelManager::resourceStreamOpened(const Ogre::String &name, const Ogre::String &group, Ogre::Resource *resource, Ogre::DataStreamPtr &dataStream)
{
	_Root->renderOneFrame();
}
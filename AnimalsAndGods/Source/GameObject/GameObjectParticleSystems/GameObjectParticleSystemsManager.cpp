#include "stdafx.h"
#include "../../Header/GameObject/GameObjectParticleSystems/GameObjectParticleSystemsManager.h"

using namespace GOPS;

template<> GameObjectParticleSystemsManager* Ogre::Singleton<GameObjectParticleSystemsManager>::msSingleton = 0;
GameObjectParticleSystemsManager* GameObjectParticleSystemsManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
GameObjectParticleSystemsManager& GameObjectParticleSystemsManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

GameObjectParticleSystemsManager::GameObjectParticleSystemsManager()
{
}

GameObjectParticleSystemsManager::~GameObjectParticleSystemsManager()
{
}

void GameObjectParticleSystemsManager::initialiseManager(Ogre::SceneManager* aSceneManager)
{
	_SceneManager = aSceneManager;	
}

void GameObjectParticleSystemsManager::clearManager()
{	
}

void GameObjectParticleSystemsManager::configureGOPS()
{
}

void GameObjectParticleSystemsManager::releaseGOPS()
{	
	BOOST_FOREACH(MapGameObjectPU::value_type& gameObjectPU, _MapGameObjectPU)
		delete gameObjectPU.second;
	
	_MapGameObjectPU.clear();	
}

bool GameObjectParticleSystemsManager::frameStartedGOPS(const Ogre::Real aElapsedTime)
{
	try
	{
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[frameStartedGON]: " + e.getDescription());
		return false;
	}	
}

bool GameObjectParticleSystemsManager::frameEndedGOPS(const Ogre::Real aElapsedTime)
{
	try
	{
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[frameEndedGON]: " + e.getDescription());
		return false;
	}	
}

bool GameObjectParticleSystemsManager::updateGOPS(const Ogre::Real aElapsedTime)
{
	try
	{
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[updateGON]: " + e.getDescription());
		return false;
	}	
}

bool GameObjectParticleSystemsManager::updateLogicGOPS(const Ogre::Real aElapsedTime)
{
	try
	{
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[updateLogicGON]: " + e.getDescription());
		return false;
	}
}

bool GameObjectParticleSystemsManager::createGOPSParticleUnivers(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aPUScriptName)
{
	try
	{
		GameObjectPU* gameObjectPU = new GameObjectPU(aGameObjectId,
													  aGONSceneNode,
													  aPUScriptName);		

		boost::unordered_map<Ogre::int32, GameObjectPU*>::value_type gameObjectPU_Type(aGameObjectId,
											 										   gameObjectPU);
		_MapGameObjectPU.insert(gameObjectPU_Type);			

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("GameObjectEntityManager::createGONLighter || Desc: " + e.getDescription());
		return false;
	}
}

GameObjectPU* GameObjectParticleSystemsManager::GetGOPSParticleUnivers(Ogre::String aGameObjectSceneNodePUName)
{
	GameObjectPU* gOPU = 0;	
	BOOST_FOREACH(MapGameObjectPU::value_type& gameObjectPU, _MapGameObjectPU)
	{		
		if(Ogre::StringUtil::match(gameObjectPU.second->getGOPUSceneNode()->getName(),aGameObjectSceneNodePUName))
		{
			gOPU = gameObjectPU.second;	
			break;
		}
		else
			continue;
	}
	
	return gOPU;
}

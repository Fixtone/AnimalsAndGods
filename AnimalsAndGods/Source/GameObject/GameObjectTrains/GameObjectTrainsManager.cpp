#include "stdafx.h"
#include "../../Header/GameObject/GameObjectTrains/GameObjectTrainsManager.h"

using namespace GOT;

template<> GameObjectTrainsManager* Ogre::Singleton<GameObjectTrainsManager>::msSingleton = 0;
GameObjectTrainsManager* GameObjectTrainsManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
GameObjectTrainsManager& GameObjectTrainsManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

GameObjectTrainsManager::GameObjectTrainsManager()
{
}

GameObjectTrainsManager::~GameObjectTrainsManager()
{
}

void GameObjectTrainsManager::initialiseManager(Ogre::SceneManager* aSceneManager)
{
	_SceneManager = aSceneManager;	
}

void GameObjectTrainsManager::clearManager()
{
}

void GameObjectTrainsManager::configureGON()
{
	for(std::vector<sGOTrainData>::iterator it = _GOTrainVector.begin(); it!= _GOTrainVector.end(); it++)	
		it->GOTrain->configure();
}

void GameObjectTrainsManager::releaseGON()
{
	for(std::vector<sGOTrainData>::iterator it = _GOTrainVector.begin(); it!= _GOTrainVector.end(); it++)	
	{
		it->GOTrain->release();
		delete it->GOTrain;
	}
	_GOTrainVector.clear();

}

bool GameObjectTrainsManager::createGONTrain(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, const Ogre::String &aTrainLightName, 
										 	 const Ogre::String &aWayPointsRouteName, GameObjectTrain::GONTrainStates aGONTrainState,
											 Ogre::Real aSpeed, Ogre::Real aMinStopTime, Ogre::Real aMaxStopTime)
{
	try
	{
		
		GameObjectTrain* gameObjectTrain = new GameObjectTrain(aGameObjectId, aGONSceneNode, aTrainLightName, aWayPointsRouteName,
															   aGONTrainState, aSpeed, aMinStopTime, aMaxStopTime);

		sGOTrainData GOTrainData;
		GOTrainData.TrainName = aGONSceneNode->getName();
		GOTrainData.GOTrain = gameObjectTrain;
		
		_GOTrainVector.push_back(GOTrainData);

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[GameObjectWayPointsManager]: " + e.getDescription());
		assert(0);
		return false;
	}	
}

bool GameObjectTrainsManager::frameStartedGON(const Ogre::Real aElapsedTime)
{
	try
	{
		for(std::vector<sGOTrainData>::iterator it = _GOTrainVector.begin(); it!= _GOTrainVector.end(); it++)
			it->GOTrain->frameStarted(aElapsedTime);
	
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[frameStartedGON]: " + e.getDescription());
		return false;
	}	
}

bool GameObjectTrainsManager::frameEndedGON(const Ogre::Real aElapsedTime)
{
	try
	{
		for(std::vector<sGOTrainData>::iterator it = _GOTrainVector.begin(); it!= _GOTrainVector.end(); it++)
			it->GOTrain->frameEnded(aElapsedTime);

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[frameEndedGON]: " + e.getDescription());
		return false;
	}	
}

bool GameObjectTrainsManager::updateGON(const Ogre::Real aElapsedTime)
{
	try
	{
		for(std::vector<sGOTrainData>::iterator it = _GOTrainVector.begin(); it!= _GOTrainVector.end(); it++)
			it->GOTrain->update(aElapsedTime);	

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[updateGON]: " + e.getDescription());
		return false;
	}	
}
			
bool GameObjectTrainsManager::updateLogicGON(const Ogre::Real aElapsedTime)
{
	try
	{
		for(std::vector<sGOTrainData>::iterator it = _GOTrainVector.begin(); it!= _GOTrainVector.end(); it++)
			it->GOTrain->updateLogic(L, aElapsedTime);				

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[updateLogicGON]: " + e.getDescription());
		return false;
	}
}

LUA_BEGIN_BINDING(GameObjectTrainsManager, gameObjectTrainsManagerLib)
LUA_END_BINDING()

//
// Load lua scripts that will be used by this manager
//
LUA_BEGIN_LOAD_SCRIPTS(GameObjectTrainsManager)
LUA_END_LOAD_SCRIPTS()
#include "stdafx.h"
#include "../../Header/GameObject/GameObjectSpaceShips/GameObjectSpaceShipsManager.h"

using namespace GOSS;

template<> GameObjectSpaceShipsManager* Ogre::Singleton<GameObjectSpaceShipsManager>::msSingleton = 0;
GameObjectSpaceShipsManager* GameObjectSpaceShipsManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
GameObjectSpaceShipsManager& GameObjectSpaceShipsManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

GameObjectSpaceShipsManager::GameObjectSpaceShipsManager()
{
}

GameObjectSpaceShipsManager::~GameObjectSpaceShipsManager()
{
}

void GameObjectSpaceShipsManager::initialiseManager(Ogre::SceneManager* aSceneManager)
{
	_SceneManager = aSceneManager;	
}

void GameObjectSpaceShipsManager::clearManager()
{
}

void GameObjectSpaceShipsManager::configureGON()
{
	BOOST_FOREACH(MapGameObjectSpaceShip::value_type& gameObjectSpaceShip, _MapGameObjectSpaceShip)
		gameObjectSpaceShip.second->configure();
}

void GameObjectSpaceShipsManager::releaseGON()
{
	BOOST_FOREACH(MapGameObjectSpaceShip::value_type& gameObjectSpaceShip, _MapGameObjectSpaceShip)
	{
		gameObjectSpaceShip.second->release();
		delete gameObjectSpaceShip.second;
	}
	_MapGameObjectSpaceShip.clear();

}

bool GameObjectSpaceShipsManager::createGONSpaceShip(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, const Ogre::String &aGOESpaceShipName,const Ogre::String &aSpaceShipNodeTrackAnimationName,
													 const Ogre::String &aSpaceShipWayPointsRouteName, Ogre::Real aSpaceShipSpeed, Ogre::Real aSpaceShipLandMinStopTime,
													 Ogre::Real aSpaceShipLandMaxStopTime, GameObjectSpaceShip::GONSpaceShipStates aGONSpaceShipState)
{
	try
	{
		
		GameObjectSpaceShip* gameObjectSpaceShip = new GameObjectSpaceShip(aGameObjectId, aGONSceneNode, aGOESpaceShipName, aSpaceShipNodeTrackAnimationName,
																		   aSpaceShipWayPointsRouteName, aSpaceShipSpeed, aSpaceShipLandMinStopTime,
																		   aSpaceShipLandMaxStopTime, aGONSpaceShipState);

		boost::unordered_map<Ogre::String, GameObjectSpaceShip*>::value_type gameObjectSpaceShipType(aGONSceneNode->getName(), 
																									 gameObjectSpaceShip);

		_MapGameObjectSpaceShip.insert(gameObjectSpaceShipType);
		
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[GameObjectWayPointsManager]: " + e.getDescription());
		assert(0);
		return false;
	}	
}

bool GameObjectSpaceShipsManager::frameStartedGON(const Ogre::Real aElapsedTime)
{
	try
	{
		BOOST_FOREACH(MapGameObjectSpaceShip::value_type& gameObjectSpaceShip, _MapGameObjectSpaceShip)
			gameObjectSpaceShip.second->frameStarted(aElapsedTime);
	
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[frameStartedGON]: " + e.getDescription());
		return false;
	}	
}

bool GameObjectSpaceShipsManager::frameEndedGON(const Ogre::Real aElapsedTime)
{
	try
	{
		BOOST_FOREACH(MapGameObjectSpaceShip::value_type& gameObjectSpaceShip, _MapGameObjectSpaceShip)
			gameObjectSpaceShip.second->frameEnded(aElapsedTime);		

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[frameEndedGON]: " + e.getDescription());
		return false;
	}	
}

bool GameObjectSpaceShipsManager::updateGON(const Ogre::Real aElapsedTime)
{
	try
	{
		BOOST_FOREACH(MapGameObjectSpaceShip::value_type& gameObjectSpaceShip, _MapGameObjectSpaceShip)
			gameObjectSpaceShip.second->update(aElapsedTime);		

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[updateGON]: " + e.getDescription());
		return false;
	}	
}
			
bool GameObjectSpaceShipsManager::updateLogicGON(const Ogre::Real aElapsedTime)
{
	try
	{
		BOOST_FOREACH(MapGameObjectSpaceShip::value_type& gameObjectSpaceShip, _MapGameObjectSpaceShip)
			gameObjectSpaceShip.second->updateLogic(L, aElapsedTime);		

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[updateLogicGON]: " + e.getDescription());
		return false;
	}
}

LUA_BEGIN_BINDING(GameObjectSpaceShipsManager, gameObjectSpaceShipsManagerLib)
LUA_END_BINDING()

//
// Load lua scripts that will be used by this manager
//
LUA_BEGIN_LOAD_SCRIPTS(GameObjectSpaceShipsManager)
LUA_END_LOAD_SCRIPTS()
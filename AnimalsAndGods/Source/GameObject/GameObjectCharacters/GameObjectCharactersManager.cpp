#include "stdafx.h"
#include "../../Header/GameObject/GameObjectCharacters/GameObjectCharactersManager.h"

using namespace GOCH;

template<> GameObjectCharactersManager* Ogre::Singleton<GameObjectCharactersManager>::msSingleton = 0;
GameObjectCharactersManager* GameObjectCharactersManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
GameObjectCharactersManager& GameObjectCharactersManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

GameObjectCharactersManager::GameObjectCharactersManager()
{
}

GameObjectCharactersManager::~GameObjectCharactersManager()
{
}

void GameObjectCharactersManager::initialiseManager(Ogre::SceneManager* aSceneManager)
{
	_SceneManager = aSceneManager;	
}

void GameObjectCharactersManager::clearManager()
{
}

void GameObjectCharactersManager::configureGOCH()
{
	BOOST_FOREACH(MapGameObjectPlayer::value_type& gameObjectPlayer, _MapGameObjectPlayer)
		gameObjectPlayer.second->configure();

	BOOST_FOREACH(MapGameObjectPolice::value_type& gameObjectPolice, _MapGameObjectPolice)
		gameObjectPolice.second->configure();
}

void GameObjectCharactersManager::releaseGOCH()
{
	BOOST_FOREACH(MapGameObjectPlayer::value_type& gameObjectPlayer, _MapGameObjectPlayer)
	{
		gameObjectPlayer.second->release();
		delete gameObjectPlayer.second;
	}
	_MapGameObjectPlayer.clear();

	BOOST_FOREACH(MapGameObjectPolice::value_type& gameObjectPolice, _MapGameObjectPolice)
	{
		gameObjectPolice.second->release();
		delete gameObjectPolice.second;
	}
	_MapGameObjectPolice.clear();

}

bool GameObjectCharactersManager::createGOCHPlayer(Ogre::SceneNode* aGONSceneNode, Ogre::String aPlayerCameraNodeName)
{
	try
	{
		Critter::Node* playerNode;
		playerNode = PhysicsManager::getSingletonPtr()->getPhysicsRenderSystem()->createNode();			
		playerNode->addSceneNode(aGONSceneNode);

		Critter::AnimatedCharacterDescription desc;
		desc.mShape = NxOgre::SimpleCapsule(1,0.5f);
		desc.mCollisionMask = (ShareData::GameConfigurations::PhysicsConfigurations::Walls << 1) | (ShareData::GameConfigurations::PhysicsConfigurations::Objects << 1);
		desc.mMaxGroundSpeed = 25.0f;		
		desc.setJumpVelocityFromMaxHeight(PhysicsManager::getSingletonPtr()->getPhysicsRenderSystem()->getScene()->getGravity().y, 0.75f);

		GameObjectPlayer* gameObjectPlayer = new GameObjectPlayer(playerNode, aPlayerCameraNodeName,
																  PhysicsManager::getSingletonPtr()->getPhysicsRenderSystem(),
																  desc, NxOgre::Vec3(0,5,0), Ogre::Radian(0));

		boost::unordered_map<Ogre::String, GameObjectPlayer*>::value_type gameObjectPlayerType(aGONSceneNode->getName(), 
																							   gameObjectPlayer);

		_MapGameObjectPlayer.insert(gameObjectPlayerType);
		
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[GameObjectCharactersManager]: " + e.getDescription());
		assert(0);
		return false;
	}	
}

bool GameObjectCharactersManager::createGOCHPolice(Ogre::uint32 aPoliceId, Ogre::SceneNode* aGONSceneNode, Ogre::String aPoliceEntityMeshName, 
												   Ogre::String aPoliceTalkCameraNodeName, GameObjectPolice::GOCHPoliceStates aGOCHPoliceState)
{
	try
	{
		Critter::Node* policeNode = new Critter::Node(_SceneManager,PhysicsManager::getSingletonPtr()->getPhysicsRenderSystem());
		policeNode->setSceneNode(aGONSceneNode);

		Critter::AnimatedCharacterDescription desc;
		desc.mShape = NxOgre::SimpleCapsule(1.6f,0.5f);
		desc.mCollisionMask = (ShareData::GameConfigurations::PhysicsConfigurations::Walls << 1) | (ShareData::GameConfigurations::PhysicsConfigurations::Objects << 1);
		desc.mMaxGroundSpeed = 25.0f;		
		desc.setJumpVelocityFromMaxHeight(PhysicsManager::getSingletonPtr()->getPhysicsRenderSystem()->getScene()->getGravity().y, 0.75f);

		GameObjectPolice* gameObjectPolice = new GameObjectPolice(aPoliceId, policeNode, aPoliceEntityMeshName, aPoliceTalkCameraNodeName,
																  PhysicsManager::getSingletonPtr()->getPhysicsRenderSystem(),
																  desc, NxOgre::Vec3(policeNode->getSceneNode()->getPosition().x,
																					 policeNode->getSceneNode()->getPosition().y+5,
																					 policeNode->getSceneNode()->getPosition().z), 
																  Ogre::Radian(policeNode->getSceneNode()->getOrientation().getYaw()),
																  aGOCHPoliceState);

		boost::unordered_map<Ogre::uint32, GameObjectPolice*>::value_type gameObjectPoliceType(aPoliceId, 
																							   gameObjectPolice);

		_MapGameObjectPolice.insert(gameObjectPoliceType);
		
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[createGOCHPolice]: " + e.getDescription());
		assert(0);
		return false;
	}	
}

bool GameObjectCharactersManager::frameStartedGOCH(const Ogre::Real aElapsedTime)
{
	try
	{
		BOOST_FOREACH(MapGameObjectPlayer::value_type& gameObjectPlayer, _MapGameObjectPlayer)
			gameObjectPlayer.second->frameStarted(aElapsedTime);

		BOOST_FOREACH(MapGameObjectPolice::value_type& gameObjectPolice, _MapGameObjectPolice)
			gameObjectPolice.second->frameStarted(aElapsedTime);
	
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[frameStartedGON]: " + e.getDescription());
		return false;
	}	
}

bool GameObjectCharactersManager::frameEndedGOCH(const Ogre::Real aElapsedTime)
{
	try
	{
		BOOST_FOREACH(MapGameObjectPlayer::value_type& gameObjectPlayer, _MapGameObjectPlayer)
			gameObjectPlayer.second->frameEnded(aElapsedTime);	

		BOOST_FOREACH(MapGameObjectPolice::value_type& gameObjectPolice, _MapGameObjectPolice)
				gameObjectPolice.second->frameEnded(aElapsedTime);	


		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[frameEndedGON]: " + e.getDescription());
		return false;
	}	
}

bool GameObjectCharactersManager::updateGOCH(const Ogre::Real aElapsedTime)
{
	try
	{
		BOOST_FOREACH(MapGameObjectPlayer::value_type& gameObjectPlayer, _MapGameObjectPlayer)
			gameObjectPlayer.second->update(aElapsedTime);		

		BOOST_FOREACH(MapGameObjectPolice::value_type& gameObjectPolice, _MapGameObjectPolice)
			gameObjectPolice.second->update(aElapsedTime);		

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[updateGON]: " + e.getDescription());
		return false;
	}	
}
			
bool GameObjectCharactersManager::updateLogicGOCH(const Ogre::Real aElapsedTime)
{
	try
	{
		BOOST_FOREACH(MapGameObjectPlayer::value_type& gameObjectPlayer, _MapGameObjectPlayer)
			gameObjectPlayer.second->updateLogic(L, aElapsedTime);	

		BOOST_FOREACH(MapGameObjectPolice::value_type& gameObjectPolice, _MapGameObjectPolice)
			gameObjectPolice.second->updateLogic(L, aElapsedTime);	

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[updateLogicGON]: " + e.getDescription());
		return false;
	}
}

GameObjectPlayer* GameObjectCharactersManager::getGOCHPlayer()
{
	GameObjectPlayer* gameObjectplayer = 0;

	if(!_MapGameObjectPlayer.empty())
		gameObjectplayer = (*_MapGameObjectPlayer.begin()).second;

	return gameObjectplayer;
}

GameObjectPolice* GameObjectCharactersManager::_GetGOPoliceById(Ogre::uint32 aId)
{
	GameObjectPolice* gOPolice = 0;	
	BOOST_FOREACH(MapGameObjectPolice::value_type& gameObjectPolice, _MapGameObjectPolice)
	{
		if(gameObjectPolice.first == aId)					
		{
			gOPolice = gameObjectPolice.second;
			break;
		}
	}
	
	return gOPolice;
}

LUA_BEGIN_BINDING(GameObjectCharactersManager, gameObjectCharactersManagerLib)
LUA_BIND(GameObjectCharactersManager, getCameraDistanceToGameObjectPolice)
LUA_END_BINDING()

//
// Load lua scripts that will be used by this manager
//
LUA_BEGIN_LOAD_SCRIPTS(GameObjectCharactersManager)
LUA_LOAD_SCRIPT(".\\Resources\\Play\\Scripts\\SC_GameObjectPoliceLogic.lua")
LUA_END_LOAD_SCRIPTS()

LUA_DEFINE_FUNCTION(GameObjectCharactersManager, getCameraDistanceToGameObjectPolice)
{		
	/* get number of arguments */
	int n = lua_gettop(L);	
	
	Ogre::uint32 id = luaL_checknumber(L,1);

	Ogre::Vector3 cameraPosition = Ogre::Vector3::ZERO;
	CustomCamera* customCam = Cameras::CameraManager::getSingletonPtr()->getActiveCamera();
	switch(customCam->getCustomCameraType())
	{
		case ShareData::GameConfigurations::CameraConfigurations::FPS:
			cameraPosition = Ogre::Vector3(customCam->getCamera()->getParentSceneNode()->_getDerivedPosition());
		break;
		case ShareData::GameConfigurations::CameraConfigurations::FREE:
			cameraPosition = Ogre::Vector3(customCam->getCamera()->getPosition());
		break;
		case ShareData::GameConfigurations::CameraConfigurations::STATIC:
			cameraPosition = Ogre::Vector3(customCam->getCamera()->getParentSceneNode()->_getDerivedPosition());
		break;
	};	

	GameObjectPolice* GOPolice = GOCH::GameObjectCharactersManager::getSingletonPtr()->_GetGOPoliceById(id);

	Ogre::Vector3 positionGOPolice = Ogre::Vector3(GOPolice->getPosition().x,GOPolice->getPosition().y,GOPolice->getPosition().z);

	double range = cameraPosition.distance(positionGOPolice);

	/* push the distance */
	lua_pushnumber(L, range);

	/* return the number of results */
	return 1;	
}
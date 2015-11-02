#include "stdafx.h"
#include "../../Header/GameObject/GameObjectNodes/GameObjectNodeManager.h"

using namespace GON;

template<> GameObjectNodeManager* Ogre::Singleton<GameObjectNodeManager>::msSingleton = 0;
GameObjectNodeManager* GameObjectNodeManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
GameObjectNodeManager& GameObjectNodeManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

GameObjectNodeManager::GameObjectNodeManager()
{
}

GameObjectNodeManager::~GameObjectNodeManager()
{
}

void GameObjectNodeManager::initialiseManager(Ogre::SceneManager* aSceneManager)
{
	_SceneManager = aSceneManager;	
}

void GameObjectNodeManager::clearManager()
{	
}

void GameObjectNodeManager::configureGON()
{
	BOOST_FOREACH(MapGameObjectNodeLighter::value_type& gameObjectNodeLighter, _MapGameObjectNodeLighter)
		gameObjectNodeLighter.second->configure();

	BOOST_FOREACH(MapGameObjectNodeStreetLight::value_type& gameObjectNodeStreetLight, _MapGameObjectNodeStreetLight)
		gameObjectNodeStreetLight.second->configure();

	BOOST_FOREACH(MapGameObjectNodeSewer::value_type& gameObjectNodeSewer, _MapGameObjectNodeSewer)
		gameObjectNodeSewer.second->configure();

	BOOST_FOREACH(MapGameObjectNodeHydrant::value_type& gameObjectNodeHydrant, _MapGameObjectNodeHydrant)
		gameObjectNodeHydrant.second->configure();

	BOOST_FOREACH(MapGameObjectNodeFloorSign::value_type& gameObjectNodeFloorSign, _MapGameObjectNodeFloorSign)
		gameObjectNodeFloorSign.second->configure();

	BOOST_FOREACH(MapGameObjectNodeStreetAddonOne::value_type& gameObjectNodeStreetAddonOne, _MapGameObjectNodeStreetAddonOne)
		gameObjectNodeStreetAddonOne.second->configure();

	BOOST_FOREACH(MapGameObjectNodeStreetAddonTwo::value_type& gameObjectNodeStreetAddonTwo, _MapGameObjectNodeStreetAddonTwo)
		gameObjectNodeStreetAddonTwo.second->configure();

	BOOST_FOREACH(MapGameObjectNodeStreetAddonThree::value_type& gameObjectNodeStreetAddonThree, _MapGameObjectNodeStreetAddonThree)
		gameObjectNodeStreetAddonThree.second->configure();
	
}

void GameObjectNodeManager::releaseGON()
{		
	BOOST_FOREACH(MapGameObjectNodeLighter::value_type& gameObjectNodeLighter, _MapGameObjectNodeLighter)
	{
		gameObjectNodeLighter.second->release();
		delete gameObjectNodeLighter.second;
	}
	_MapGameObjectNodeLighter.clear();

	BOOST_FOREACH(MapGameObjectNodeStreetLight::value_type& gameObjectNodeStreetLight, _MapGameObjectNodeStreetLight)
	{
		gameObjectNodeStreetLight.second->release();
		delete gameObjectNodeStreetLight.second;
	}
	_MapGameObjectNodeStreetLight.clear();	

	BOOST_FOREACH(MapGameObjectNodeSewer::value_type& gameObjectNodeSewer, _MapGameObjectNodeSewer)
	{
		gameObjectNodeSewer.second->release();
		delete gameObjectNodeSewer.second;
	}
	_MapGameObjectNodeSewer.clear();	

	BOOST_FOREACH(MapGameObjectNodeHydrant::value_type& gameObjectNodeHydrant, _MapGameObjectNodeHydrant)
	{
		gameObjectNodeHydrant.second->release();
		delete gameObjectNodeHydrant.second;
	}
	_MapGameObjectNodeHydrant.clear();		

	BOOST_FOREACH(MapGameObjectNodeFloorSign::value_type& gameObjectNodeFloorSign, _MapGameObjectNodeFloorSign)
	{
		gameObjectNodeFloorSign.second->release();
		delete gameObjectNodeFloorSign.second;
	}
	_MapGameObjectNodeFloorSign.clear();

	BOOST_FOREACH(MapGameObjectNodeStreetAddonOne::value_type& gameObjectNodeStreetAddonOne, _MapGameObjectNodeStreetAddonOne)
	{
		gameObjectNodeStreetAddonOne.second->release();
		delete gameObjectNodeStreetAddonOne.second;
	}
	_MapGameObjectNodeStreetAddonOne.clear();

	BOOST_FOREACH(MapGameObjectNodeStreetAddonTwo::value_type& gameObjectNodeStreetAddonTwo, _MapGameObjectNodeStreetAddonTwo)
	{
		gameObjectNodeStreetAddonTwo.second->release();
		delete gameObjectNodeStreetAddonTwo.second;
	}
	_MapGameObjectNodeStreetAddonTwo.clear();

	BOOST_FOREACH(MapGameObjectNodeStreetAddonThree::value_type& gameObjectNodeStreetAddonThree, _MapGameObjectNodeStreetAddonThree)
	{
		gameObjectNodeStreetAddonThree.second->release();
		delete gameObjectNodeStreetAddonThree.second;
	}
	_MapGameObjectNodeStreetAddonThree.clear();
}

bool GameObjectNodeManager::frameStartedGON(const Ogre::Real aElapsedTime)
{
	try
	{
		BOOST_FOREACH(MapGameObjectNodeLighter::value_type& gameObjectNodeLighter, _MapGameObjectNodeLighter)
			gameObjectNodeLighter.second->frameStarted(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetLight::value_type& gameObjectNodeStreetLight, _MapGameObjectNodeStreetLight)
			gameObjectNodeStreetLight.second->frameStarted(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeSewer::value_type& gameObjectNodeSewer, _MapGameObjectNodeSewer)
			gameObjectNodeSewer.second->frameStarted(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeHydrant::value_type& gameObjectNodeHydrant, _MapGameObjectNodeHydrant)
			gameObjectNodeHydrant.second->frameStarted(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeFloorSign::value_type& gameObjectNodeFloorSign, _MapGameObjectNodeFloorSign)
			gameObjectNodeFloorSign.second->frameStarted(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetAddonOne::value_type& gameObjectNodeStreetAddonOne, _MapGameObjectNodeStreetAddonOne)
			gameObjectNodeStreetAddonOne.second->frameStarted(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetAddonTwo::value_type& gameObjectNodeStreetAddonTwo, _MapGameObjectNodeStreetAddonTwo)
			gameObjectNodeStreetAddonTwo.second->frameStarted(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetAddonThree::value_type& gameObjectNodeStreetAddonThree, _MapGameObjectNodeStreetAddonThree)
			gameObjectNodeStreetAddonThree.second->frameStarted(aElapsedTime);		

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[frameStartedGON]: " + e.getDescription());
		return false;
	}	
}

bool GameObjectNodeManager::frameEndedGON(const Ogre::Real aElapsedTime)
{
	try
	{
		BOOST_FOREACH(MapGameObjectNodeLighter::value_type& gameObjectNodeLighter, _MapGameObjectNodeLighter)
			gameObjectNodeLighter.second->frameEnded(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetLight::value_type& gameObjectNodeStreetLight, _MapGameObjectNodeStreetLight)
			gameObjectNodeStreetLight.second->frameEnded(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeSewer::value_type& gameObjectNodeSewer, _MapGameObjectNodeSewer)
			gameObjectNodeSewer.second->frameEnded(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeHydrant::value_type& gameObjectNodeHydrant, _MapGameObjectNodeHydrant)
			gameObjectNodeHydrant.second->frameEnded(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeFloorSign::value_type& gameObjectNodeFloorSign, _MapGameObjectNodeFloorSign)
			gameObjectNodeFloorSign.second->frameEnded(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetAddonOne::value_type& gameObjectNodeStreetAddonOne, _MapGameObjectNodeStreetAddonOne)
			gameObjectNodeStreetAddonOne.second->frameEnded(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetAddonTwo::value_type& gameObjectNodeStreetAddonTwo, _MapGameObjectNodeStreetAddonTwo)
			gameObjectNodeStreetAddonTwo.second->frameEnded(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetAddonThree::value_type& gameObjectNodeStreetAddonThree, _MapGameObjectNodeStreetAddonThree)
			gameObjectNodeStreetAddonThree.second->frameEnded(aElapsedTime);

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[frameEndedGON]: " + e.getDescription());
		return false;
	}	
}

bool GameObjectNodeManager::updateGON(const Ogre::Real aElapsedTime)
{
	try
	{
		BOOST_FOREACH(MapGameObjectNodeLighter::value_type& gameObjectNodeLighter, _MapGameObjectNodeLighter)
			gameObjectNodeLighter.second->update(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetLight::value_type& gameObjectNodeStreetLight, _MapGameObjectNodeStreetLight)
			gameObjectNodeStreetLight.second->update(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeSewer::value_type& gameObjectNodeSewer, _MapGameObjectNodeSewer)
			gameObjectNodeSewer.second->update(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeHydrant::value_type& gameObjectNodeHydrant, _MapGameObjectNodeHydrant)
			gameObjectNodeHydrant.second->update(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeFloorSign::value_type& gameObjectNodeFloorSign, _MapGameObjectNodeFloorSign)
			gameObjectNodeFloorSign.second->update(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetAddonOne::value_type& gameObjectNodeStreetAddonOne, _MapGameObjectNodeStreetAddonOne)
			gameObjectNodeStreetAddonOne.second->update(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetAddonTwo::value_type& gameObjectNodeStreetAddonTwo, _MapGameObjectNodeStreetAddonTwo)
			gameObjectNodeStreetAddonTwo.second->update(aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetAddonThree::value_type& gameObjectNodeStreetAddonThree, _MapGameObjectNodeStreetAddonThree)
			gameObjectNodeStreetAddonThree.second->update(aElapsedTime);

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[updateGON]: " + e.getDescription());
		return false;
	}	
}
			
bool GameObjectNodeManager::updateLogicGON(const Ogre::Real aElapsedTime)
{
	try
	{
		BOOST_FOREACH(MapGameObjectNodeLighter::value_type& gameObjectNodeLighter, _MapGameObjectNodeLighter)
			gameObjectNodeLighter.second->updateLogic(L, aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetLight::value_type& gameObjectNodeStreetLight, _MapGameObjectNodeStreetLight)
			gameObjectNodeStreetLight.second->updateLogic(L, aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeSewer::value_type& gameObjectNodeSewer, _MapGameObjectNodeSewer)
			gameObjectNodeSewer.second->updateLogic(L, aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeHydrant::value_type& gameObjectNodeHydrant, _MapGameObjectNodeHydrant)
			gameObjectNodeHydrant.second->updateLogic(L, aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeFloorSign::value_type& gameObjectNodeFloorSign, _MapGameObjectNodeFloorSign)
			gameObjectNodeFloorSign.second->updateLogic(L, aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetAddonOne::value_type& gameObjectNodeStreetAddonOne, _MapGameObjectNodeStreetAddonOne)
			gameObjectNodeStreetAddonOne.second->updateLogic(L, aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetAddonTwo::value_type& gameObjectNodeStreetAddonTwo, _MapGameObjectNodeStreetAddonTwo)
			gameObjectNodeStreetAddonTwo.second->updateLogic(L, aElapsedTime);

		BOOST_FOREACH(MapGameObjectNodeStreetAddonThree::value_type& gameObjectNodeStreetAddonThree, _MapGameObjectNodeStreetAddonThree)
			gameObjectNodeStreetAddonThree.second->updateLogic(L, aElapsedTime);

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[updateLogicGON]: " + e.getDescription());
		return false;
	}
}

bool GameObjectNodeManager::createGONLighter(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
											 Ogre::String aLPanelInfoName, Ogre::String aLCarLighterName, Ogre::String aLPedrastianLighterName, 
											 GameObjectNodeLighter::GONLighterStates aGONLighterState)
{
	try
	{
		GameObjectNodeLighter* gameObjectNodeLighter = new GameObjectNodeLighter(aGameObjectId,																		  
																				 aGONSceneNode,																				 
																				 aLPanelInfoName,																				 
																				 aLCarLighterName,																				 
																				 aLPedrastianLighterName,
																				 aGONLighterState);																		

		boost::unordered_map<Ogre::int32, GameObjectNodeLighter*>::value_type gameObjectNodeLighter_Type(aGameObjectId,
																										 gameObjectNodeLighter);
		_MapGameObjectNodeLighter.insert(gameObjectNodeLighter_Type);			
		
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("GameObjectEntityManager::createGONLighter || Desc: " + e.getDescription());
		return false;
	}
}

bool GameObjectNodeManager::createGONStreetLight(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
												Ogre::String aGONLightName, Ogre::String aGONStreetLightName, GameObjectNodeStreetLight::GONStreetLightStates aGONStreetLightState)
{
	try
	{
		GameObjectNodeStreetLight* gameObjectNodeStreetLight = new GameObjectNodeStreetLight(aGameObjectId,																		  
																							 aGONSceneNode,																							 
																							 aGONStreetLightName,
																							 aGONLightName,
																							 aGONStreetLightState);
																						

		boost::unordered_map<Ogre::int32, GameObjectNodeStreetLight*>::value_type gameObjectNodeStreetLight_Type(aGameObjectId,
																												 gameObjectNodeStreetLight);
		_MapGameObjectNodeStreetLight.insert(gameObjectNodeStreetLight_Type);			
		
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("GameObjectEntityManager::createGONStreetLight || Desc: " + e.getDescription());
		return false;
	}
}

bool GameObjectNodeManager::createGONSewer(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aSewerEntityName, Ogre::String aSewerPUName, 
										   GameObjectNodeSewer::GONSewerStates aGONSewerState)
{
	try
	{

		GameObjectNodeSewer* gameObjectNodeSewer = new GameObjectNodeSewer(aGameObjectId,																		  
																		   aGONSceneNode,																							 
																		   aSewerEntityName,
																		   aSewerPUName,
																		   aGONSewerState);
																						

		boost::unordered_map<Ogre::int32, GameObjectNodeSewer*>::value_type gameObjectNodeSewer_Type(aGameObjectId,
																									 gameObjectNodeSewer);
		_MapGameObjectNodeSewer.insert(gameObjectNodeSewer_Type);			
		
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("GameObjectEntityManager::createGONStreetLight || Desc: " + e.getDescription());
		return false;
	}
}

bool GameObjectNodeManager::createGONHydrant(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aHydrantEntityName, Ogre::String aHydrantLeftPUName,
											 Ogre::String aHydrantRightPUName, GameObjectNodeHydrant::GONHydrantStates aGONHydrantState)
{
	try
	{

		GameObjectNodeHydrant* gameObjectNodeHydrant = new GameObjectNodeHydrant(aGameObjectId,																		  
																				 aGONSceneNode,																							 
																				 aHydrantEntityName,
																				 aHydrantLeftPUName,
																				 aHydrantRightPUName,
																				 aGONHydrantState);
																						

		boost::unordered_map<Ogre::int32, GameObjectNodeHydrant*>::value_type gameObjectNodeHydrant_Type(aGameObjectId,
																										 gameObjectNodeHydrant);
		_MapGameObjectNodeHydrant.insert(gameObjectNodeHydrant_Type);			
		
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("GameObjectEntityManager::createGONStreetLight || Desc: " + e.getDescription());
		return false;
	}
}

bool GameObjectNodeManager::createGONFloorSign(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
											   Ogre::String aFloorSignEntityName, Ogre::String aFloorSignBackEntityName, Ogre::String aFloorSignFrontEntityName, 
											   GameObjectNodeFloorSign::GONFloorSignStates aGONFloorSignState)
{
	try
	{
		GameObjectNodeFloorSign* gameObjectNodeFloorSign = new GameObjectNodeFloorSign(aGameObjectId,																		  
																					   aGONSceneNode,																				 
																					   aFloorSignEntityName,																				 
																					   aFloorSignBackEntityName,																				 
																					   aFloorSignFrontEntityName,
																					   aGONFloorSignState);																		

		boost::unordered_map<Ogre::int32, GameObjectNodeFloorSign*>::value_type gameObjectNodeFloorSign_Type(aGameObjectId,
																											 gameObjectNodeFloorSign);
		_MapGameObjectNodeFloorSign.insert(gameObjectNodeFloorSign_Type);			
		
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("GameObjectEntityManager::createGONFloorSign || Desc: " + e.getDescription());
		return false;
	}
}

bool GameObjectNodeManager::createGONStreetAddonOne(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
													Ogre::String aStreetAddonOneEntityName,
													GameObjectNodeStreetAddonOne::GONStreetAddonOneStates aGONStreetAddonOneState)
{
	try
	{
		GameObjectNodeStreetAddonOne* gameObjectNodeStreetAddonOne = new GameObjectNodeStreetAddonOne(aGameObjectId,																		  
																									  aGONSceneNode,																				 
																									  aStreetAddonOneEntityName,
																									  aGONStreetAddonOneState);																		

		boost::unordered_map<Ogre::int32, GameObjectNodeStreetAddonOne*>::value_type gameObjectNodeStreetAddonOne_Type(aGameObjectId,
																													   gameObjectNodeStreetAddonOne);
		_MapGameObjectNodeStreetAddonOne.insert(gameObjectNodeStreetAddonOne_Type);			
		
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("GameObjectEntityManager::createGONStreetAddonOne || Desc: " + e.getDescription());
		return false;
	}
}

bool GameObjectNodeManager::createGONStreetAddonTwo(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
													Ogre::String aStreetAddonTwoEntityName,
													GameObjectNodeStreetAddonTwo::GONStreetAddonTwoStates aGONStreetAddonTwoState)
{
	try
	{
		GameObjectNodeStreetAddonTwo* gameObjectNodeStreetAddonTwo = new GameObjectNodeStreetAddonTwo(aGameObjectId,																		  
																									  aGONSceneNode,																				 
																									  aStreetAddonTwoEntityName,	
																									  aGONStreetAddonTwoState);																		

		boost::unordered_map<Ogre::int32, GameObjectNodeStreetAddonTwo*>::value_type gameObjectNodeStreetAddonTwo_Type(aGameObjectId,
																													   gameObjectNodeStreetAddonTwo);
		_MapGameObjectNodeStreetAddonTwo.insert(gameObjectNodeStreetAddonTwo_Type);			
		
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("GameObjectEntityManager::createGONStreetAddonTwo || Desc: " + e.getDescription());
		return false;
	}
}

bool GameObjectNodeManager::createGONStreetAddonThree(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
													  Ogre::String aStreetAddonThreeEntityName,
													  GameObjectNodeStreetAddonThree::GONStreetAddonThreeStates aGONStreetAddonThreeState)
{
	try
	{
		GameObjectNodeStreetAddonThree* gameObjectNodeStreetAddonThree = new GameObjectNodeStreetAddonThree(aGameObjectId,																		  
																											aGONSceneNode,																				 
																											aStreetAddonThreeEntityName,
																											aGONStreetAddonThreeState);																		

		boost::unordered_map<Ogre::int32, GameObjectNodeStreetAddonThree*>::value_type gameObjectNodeStreetAddonThree_Type(aGameObjectId,
																														   gameObjectNodeStreetAddonThree);
		_MapGameObjectNodeStreetAddonThree.insert(gameObjectNodeStreetAddonThree_Type);			
		
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("GameObjectEntityManager::createGONStreetAddonThree || Desc: " + e.getDescription());
		return false;
	}
}

GameObjectNodeLighter* GameObjectNodeManager::GetGONLighter(Ogre::String aGONLighterName)
{
	GameObjectNodeLighter* gONLighter = 0;	
	BOOST_FOREACH(MapGameObjectNodeLighter::value_type& gameObjectNodeLighter, _MapGameObjectNodeLighter)
	{
		if(Ogre::StringUtil::match(gameObjectNodeLighter.second->getSceneNode()->getName(),aGONLighterName))		
		{
			gONLighter = gameObjectNodeLighter.second;	
			break;
		}
	}
	
	return gONLighter;
}

GameObjectNodeLighter* GameObjectNodeManager::GetGONLighterById(Ogre::uint32 aId)
{
	GameObjectNodeLighter* gONLighter = 0;	
	BOOST_FOREACH(MapGameObjectNodeLighter::value_type& gameObjectNodeLighter, _MapGameObjectNodeLighter)
	{
		if(gameObjectNodeLighter.first == aId)					
		{
			gONLighter = gameObjectNodeLighter.second;
			break;
		}
	}
	
	return gONLighter;
}

GameObjectNodeFloorSign* GameObjectNodeManager::GetGONFloorSign(Ogre::String aGONFloorSignName)
{
	GameObjectNodeFloorSign* gONFloorSign = 0;	
	BOOST_FOREACH(MapGameObjectNodeFloorSign::value_type& gameObjectNodeFloorSign, _MapGameObjectNodeFloorSign)
	{
		if(Ogre::StringUtil::match(gameObjectNodeFloorSign.second->getSceneNode()->getName(),aGONFloorSignName))		
		{
			gONFloorSign = gameObjectNodeFloorSign.second;	
			break;
		}
	}
	
	return gONFloorSign;
}

GameObjectNodeFloorSign* GameObjectNodeManager::GetGONFloorSignById(Ogre::uint32 aId)
{
	GameObjectNodeFloorSign* gONFloorSign = 0;	
	BOOST_FOREACH(MapGameObjectNodeFloorSign::value_type& gameObjectNodeFloorSign, _MapGameObjectNodeFloorSign)
	{
		if(gameObjectNodeFloorSign.first == aId)					
		{
			gONFloorSign = gameObjectNodeFloorSign.second;
			break;
		}
	}
	
	return gONFloorSign;
}

GameObjectNodeStreetLight* GameObjectNodeManager::GetGONStreetLight(Ogre::String aGONStreetLightName)
{
	GameObjectNodeStreetLight* gONStreetLight = 0;	
	BOOST_FOREACH(MapGameObjectNodeStreetLight::value_type& gameObjectNodeStreetLight, _MapGameObjectNodeStreetLight)
	{
		if(Ogre::StringUtil::match(gameObjectNodeStreetLight.second->getSceneNode()->getName(),aGONStreetLightName))		
		{
			gONStreetLight = gameObjectNodeStreetLight.second;	
			break;
		}
	}
	
	return gONStreetLight;
}

GameObjectNodeStreetLight* GameObjectNodeManager::GetGONStreetLightById(Ogre::uint32 aId)
{
	GameObjectNodeStreetLight* gONStreetLight = 0;	
	BOOST_FOREACH(MapGameObjectNodeStreetLight::value_type& gameObjectNodeStreetLight, _MapGameObjectNodeStreetLight)
	{
		if(gameObjectNodeStreetLight.first == aId)					
		{
			gONStreetLight = gameObjectNodeStreetLight.second;
			break;
		}
	}
	
	return gONStreetLight;
}

GameObjectNodeStreetAddonOne* GameObjectNodeManager::GetGONStreetAddonOne(Ogre::String aGONStreetAddonOneName)
{
	GameObjectNodeStreetAddonOne* gONStreetAddonOne = 0;	
	BOOST_FOREACH(MapGameObjectNodeStreetAddonOne::value_type& gameObjectNodeStreetAddonOne, _MapGameObjectNodeStreetAddonOne)
	{
		if(Ogre::StringUtil::match(gameObjectNodeStreetAddonOne.second->getSceneNode()->getName(),aGONStreetAddonOneName))		
		{
			gONStreetAddonOne = gameObjectNodeStreetAddonOne.second;	
			break;
		}
	}
	
	return gONStreetAddonOne;
}

GameObjectNodeStreetAddonOne* GameObjectNodeManager::GetGONStreetAddonOneById(Ogre::uint32 aId)
{
	GameObjectNodeStreetAddonOne* gONStreetAddonOne = 0;	
	BOOST_FOREACH(MapGameObjectNodeStreetAddonOne::value_type& gameObjectNodeStreetAddonOne, _MapGameObjectNodeStreetAddonOne)
	{
		if(gameObjectNodeStreetAddonOne.first == aId)					
		{
			gONStreetAddonOne = gameObjectNodeStreetAddonOne.second;
			break;
		}
	}
	
	return gONStreetAddonOne;
}

GameObjectNodeStreetAddonTwo* GameObjectNodeManager::GetGONStreetAddonTwo(Ogre::String aGONStreetAddonTwoName)
{
	GameObjectNodeStreetAddonTwo* gONStreetAddonTwo = 0;	
	BOOST_FOREACH(MapGameObjectNodeStreetAddonTwo::value_type& gameObjectNodeStreetAddonTwo, _MapGameObjectNodeStreetAddonTwo)
	{
		if(Ogre::StringUtil::match(gameObjectNodeStreetAddonTwo.second->getSceneNode()->getName(),aGONStreetAddonTwoName))		
		{
			gONStreetAddonTwo = gameObjectNodeStreetAddonTwo.second;	
			break;
		}
	}
	
	return gONStreetAddonTwo;
}

GameObjectNodeStreetAddonTwo* GameObjectNodeManager::GetGONStreetAddonTwoById(Ogre::uint32 aId)
{
	GameObjectNodeStreetAddonTwo* gONStreetAddonTwo = 0;	
	BOOST_FOREACH(MapGameObjectNodeStreetAddonTwo::value_type& gameObjectNodeStreetAddonTwo, _MapGameObjectNodeStreetAddonTwo)
	{
		if(gameObjectNodeStreetAddonTwo.first == aId)					
		{
			gONStreetAddonTwo = gameObjectNodeStreetAddonTwo.second;
			break;
		}
	}
	
	return gONStreetAddonTwo;
}

GameObjectNodeStreetAddonThree* GameObjectNodeManager::GetGONStreetAddonThree(Ogre::String aGONStreetAddonThreeName)
{
	GameObjectNodeStreetAddonThree* gONStreetAddonThree = 0;	
	BOOST_FOREACH(MapGameObjectNodeStreetAddonThree::value_type& gameObjectNodeStreetAddonThree, _MapGameObjectNodeStreetAddonThree)
	{
		if(Ogre::StringUtil::match(gameObjectNodeStreetAddonThree.second->getSceneNode()->getName(),aGONStreetAddonThreeName))		
		{
			gONStreetAddonThree = gameObjectNodeStreetAddonThree.second;	
			break;
		}
	}
	
	return gONStreetAddonThree;
}

GameObjectNodeStreetAddonThree* GameObjectNodeManager::GetGONStreetAddonThreeById(Ogre::uint32 aId)
{
	GameObjectNodeStreetAddonThree* gONStreetAddonThree = 0;	
	BOOST_FOREACH(MapGameObjectNodeStreetAddonThree::value_type& gameObjectNodeStreetAddonThree, _MapGameObjectNodeStreetAddonThree)
	{
		if(gameObjectNodeStreetAddonThree.first == aId)					
		{
			gONStreetAddonThree = gameObjectNodeStreetAddonThree.second;
			break;
		}
	}
	
	return gONStreetAddonThree;
}

LUA_BEGIN_BINDING(GameObjectNodeManager, gameObjectNodeManagerLib)
LUA_BIND(GameObjectNodeManager, getCameraDistanceToGameObjectNodeLighter)
LUA_BIND(GameObjectNodeManager, getCameraDistanceToGameObjectNodeFloorSign)
LUA_BIND(GameObjectNodeManager, getCameraDistanceToGameObjectNodeStreetLight)
LUA_BIND(GameObjectNodeManager, getCameraDistanceToGameObjectNodeStreetAddonOne)
LUA_BIND(GameObjectNodeManager, getCameraDistanceToGameObjectNodeStreetAddonTwo)
LUA_BIND(GameObjectNodeManager, getCameraDistanceToGameObjectNodeStreetAddonThree)
LUA_END_BINDING()

//
// Load lua scripts that will be used by this manager
//
LUA_BEGIN_LOAD_SCRIPTS(GameObjectNodeManager)
LUA_LOAD_SCRIPT(".\\Resources\\Play\\Scripts\\SC_GameObjectNodeLighterLogic.lua")
LUA_LOAD_SCRIPT(".\\Resources\\Play\\Scripts\\SC_GameObjectNodeFloorSignLogic.lua")
LUA_LOAD_SCRIPT(".\\Resources\\Play\\Scripts\\SC_GameObjectLightStreetLightLogic.lua")
LUA_LOAD_SCRIPT(".\\Resources\\Play\\Scripts\\SC_GameObjectNodeStreetAddonOneLogic.lua")
LUA_LOAD_SCRIPT(".\\Resources\\Play\\Scripts\\SC_GameObjectNodeStreetAddonTwoLogic.lua")
LUA_LOAD_SCRIPT(".\\Resources\\Play\\Scripts\\SC_GameObjectNodeStreetAddonThreeLogic.lua")
LUA_END_LOAD_SCRIPTS()

LUA_DEFINE_FUNCTION(GameObjectNodeManager, getCameraDistanceToGameObjectNodeLighter)
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

	GameObjectNodeLighter* GONLighter = GON::GameObjectNodeManager::getSingletonPtr()->GetGONLighterById(id);

	Ogre::Vector3 positionGONLighter = Ogre::Vector3(GONLighter->getSceneNode()->_getDerivedPosition());

	double range = cameraPosition.distance(positionGONLighter);

	/* push the distance */
	lua_pushnumber(L, range);

	/* return the number of results */
	return 1;	
}

LUA_DEFINE_FUNCTION(GameObjectNodeManager, getCameraDistanceToGameObjectNodeFloorSign)
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

	GameObjectNodeFloorSign* GONFloorSign = GON::GameObjectNodeManager::getSingletonPtr()->GetGONFloorSignById(id);

	Ogre::Vector3 positionGONFloorSign = Ogre::Vector3(GONFloorSign->getSceneNode()->_getDerivedPosition());

	double range = cameraPosition.distance(positionGONFloorSign);

	/* push the distance */
	lua_pushnumber(L, range);

	/* return the number of results */
	return 1;	
}

LUA_DEFINE_FUNCTION(GameObjectNodeManager, getCameraDistanceToGameObjectNodeStreetLight)
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

	GameObjectNodeStreetLight* GONStreetLight = GON::GameObjectNodeManager::getSingletonPtr()->GetGONStreetLightById(id);

	Ogre::Vector3 positionGONStreetLight = Ogre::Vector3(GONStreetLight->getSceneNode()->_getDerivedPosition());

	double range = cameraPosition.distance(positionGONStreetLight);

	/* push the distance */
	lua_pushnumber(L, range);

	/* return the number of results */
	return 1;	
}

LUA_DEFINE_FUNCTION(GameObjectNodeManager, getCameraDistanceToGameObjectNodeStreetAddonOne)
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

	GameObjectNodeStreetAddonOne* GONStreetAddonOne = GON::GameObjectNodeManager::getSingletonPtr()->GetGONStreetAddonOneById(id);

	Ogre::Vector3 positionGONStreetAddonOne = Ogre::Vector3(GONStreetAddonOne->getSceneNode()->_getDerivedPosition());

	double range = cameraPosition.distance(positionGONStreetAddonOne);

	/* push the distance */
	lua_pushnumber(L, range);

	/* return the number of results */
	return 1;	
}

LUA_DEFINE_FUNCTION(GameObjectNodeManager, getCameraDistanceToGameObjectNodeStreetAddonTwo)
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

	GameObjectNodeStreetAddonTwo* GONStreetAddonTwo = GON::GameObjectNodeManager::getSingletonPtr()->GetGONStreetAddonTwoById(id);

	Ogre::Vector3 positionGONStreetAddonTwo = Ogre::Vector3(GONStreetAddonTwo->getSceneNode()->_getDerivedPosition());

	double range = cameraPosition.distance(positionGONStreetAddonTwo);

	/* push the distance */
	lua_pushnumber(L, range);

	/* return the number of results */
	return 1;	
}

LUA_DEFINE_FUNCTION(GameObjectNodeManager, getCameraDistanceToGameObjectNodeStreetAddonThree)
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

	GameObjectNodeStreetAddonThree* GONStreetAddonThree = GON::GameObjectNodeManager::getSingletonPtr()->GetGONStreetAddonThreeById(id);

	Ogre::Vector3 positionGONStreetAddonThree = Ogre::Vector3(GONStreetAddonThree->getSceneNode()->_getDerivedPosition());

	double range = cameraPosition.distance(positionGONStreetAddonThree);

	/* push the distance */
	lua_pushnumber(L, range);

	/* return the number of results */
	return 1;	
}
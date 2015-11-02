#include "stdafx.h"
#include "../../Header/GameObject/GameObjectLights/GameObjectLightManager.h"

using namespace GOL;

template<> GameObjectLightManager* Ogre::Singleton<GameObjectLightManager>::msSingleton = 0;
GameObjectLightManager* GameObjectLightManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
GameObjectLightManager& GameObjectLightManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

GameObjectLightManager::GameObjectLightManager()
{
}

GameObjectLightManager::~GameObjectLightManager()
{
}

void GameObjectLightManager::initialiseManager(Ogre::SceneManager* aSceneManager)
{
	_SceneManager = aSceneManager;	
}

void GameObjectLightManager::clearManager()
{	
}

void GameObjectLightManager::configureGOL()
{	
}

void GameObjectLightManager::releaseGOL()
{
	for(std::vector<sGameLight>::iterator it = _GOLStreetLightVector.begin(); it!= _GOLStreetLightVector.end(); it++)
		delete it->GOLight;
	
	_GOLStreetLightVector.clear();

	for(std::vector<sGameLight>::iterator it = _GOLAmbientVector.begin(); it!= _GOLAmbientVector.end(); it++)
		delete it->GOLight;	
	
	_GOLAmbientVector.clear();

	for(std::vector<sGameLight>::iterator it = _GOLFarAmbientVector.begin(); it!= _GOLFarAmbientVector.end(); it++)
		delete it->GOLight;	

	_GOLFarAmbientVector.clear();

	for(std::vector<sGameLight>::iterator it = _GOLTrainVector.begin(); it!= _GOLTrainVector.end(); it++)
		delete it->GOLight;	
	
	_GOLTrainVector.clear();
}

bool GameObjectLightManager::frameStartedGOL(const Ogre::Real aElapsedTime)
{
	return true;
}

bool GameObjectLightManager::frameEndedGOL(const Ogre::Real aElapsedTime)
{
	return true;
}

bool GameObjectLightManager::updateGOL(const Ogre::Real aElapsedTime)
{
	return true;
}
			
bool GameObjectLightManager::updateLogicGOL(const Ogre::Real aElapsedTime)
{
	return true;
}


bool GameObjectLightManager::createGOLight(Ogre::int32 aGameObjectId, ShareData::GameConfigurations::LoadersConfigurations::GameObjectLightType aGameObjectLightType, 
										   Ogre::SceneNode* aGOLSceneNode, Ogre::Light* aGOLLight)
{
	try
	{	
		GameObjectLight* gameObjectLight = new GameObjectLight(aGameObjectId,
															   aGameObjectLightType,
															   aGOLSceneNode,
															   aGOLLight);

		sGameLight gameLight;
		gameLight.LightId = aGameObjectId;
		gameLight.GOLight = gameObjectLight;

		switch(aGameObjectLightType)
		{
			case ShareData::GameConfigurations::LoadersConfigurations::GOL_STREETLIGHT:
				_GOLStreetLightVector.push_back(gameLight);
			break;
			case ShareData::GameConfigurations::LoadersConfigurations::GOL_AMBIENT:
				_GOLAmbientVector.push_back(gameLight);
			break;
			case ShareData::GameConfigurations::LoadersConfigurations::GOL_FARAMBIENT:
				_GOLFarAmbientVector.push_back(gameLight);
			break;
			case ShareData::GameConfigurations::LoadersConfigurations::GOL_TRAIN:
				_GOLTrainVector.push_back(gameLight);
			break;
		};

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("GameObjectLightManager::createGOLight || Desc: " + e.getDescription());
		return false;
	}
}

GameObjectLight* GameObjectLightManager::GetGOLStreetLight(Ogre::String aGOLStreetLightName)
{
	GameObjectLight* gOLStreetLight = 0;	
	for(std::vector<sGameLight>::iterator it = _GOLStreetLightVector.begin(); it!= _GOLStreetLightVector.end(); it++)
	{		
		if(Ogre::StringUtil::match(it->GOLight->mGOLLight->getName(),aGOLStreetLightName))
		{
			gOLStreetLight = it->GOLight;	
			break;
		}		
	}
	
	return gOLStreetLight;
}

GameObjectLight* GameObjectLightManager::GetGOLStreetLightById(Ogre::uint32 aId)
{
	GameObjectLight* gOLStreetLight = 0;	
	for(std::vector<sGameLight>::iterator it = _GOLStreetLightVector.begin(); it!= _GOLStreetLightVector.end(); it++)
	{		
		if(it->LightId == aId)
		{
			gOLStreetLight = it->GOLight;	
			break;
		}		
	}
	
	return gOLStreetLight;
}

GameObjectLight* GameObjectLightManager::GetGOLAmbient(Ogre::String aGOLAmbientLightName)
{
	GameObjectLight* gOLAmbient = 0;	
	for(std::vector<sGameLight>::iterator it = _GOLAmbientVector.begin(); it!= _GOLAmbientVector.end(); it++)
	{		
		if(Ogre::StringUtil::match(it->GOLight->mGOLLight->getName(),aGOLAmbientLightName))
		{
			gOLAmbient = it->GOLight;	
			break;
		}		
	}
	
	return gOLAmbient;
}

GameObjectLight* GameObjectLightManager::GetGOLAmbientById(Ogre::uint32 aId)
{
	GameObjectLight* gOLAmbient = 0;	
	for(std::vector<sGameLight>::iterator it = _GOLAmbientVector.begin(); it!= _GOLAmbientVector.end(); it++)
	{		
		if(it->LightId == aId)
		{
			gOLAmbient = it->GOLight;	
			break;
		}		
	}
	
	return gOLAmbient;
}

GameObjectLight* GameObjectLightManager::GetGOLFarAmbient(Ogre::String aGOLFarAmbientLightName)
{
	GameObjectLight* gOLFarAmbient = 0;	
	for(std::vector<sGameLight>::iterator it = _GOLFarAmbientVector.begin(); it!= _GOLFarAmbientVector.end(); it++)
	{		
		if(Ogre::StringUtil::match(it->GOLight->mGOLLight->getName(),aGOLFarAmbientLightName))
		{
			gOLFarAmbient = it->GOLight;	
			break;
		}	
	}
	
	return gOLFarAmbient;
}

GameObjectLight* GameObjectLightManager::GetGOLFarAmbientById(Ogre::uint32 aId)
{
	GameObjectLight* gOLFarAmbient = 0;	
	for(std::vector<sGameLight>::iterator it = _GOLFarAmbientVector.begin(); it!= _GOLFarAmbientVector.end(); it++)
	{		
		if(it->LightId == aId)
		{
			gOLFarAmbient = it->GOLight;	
			break;
		}		
	}
	
	return gOLFarAmbient;
}

GameObjectLight* GameObjectLightManager::GetGOLTrain(Ogre::String aGOLTrainName)
{
	GameObjectLight* gOLTrain = 0;	
	for(std::vector<sGameLight>::iterator it = _GOLTrainVector.begin(); it!= _GOLTrainVector.end(); it++)
	{		
		if(Ogre::StringUtil::match(it->GOLight->mGOLLight->getName(),aGOLTrainName))
		{
			gOLTrain = it->GOLight;	
			break;
		}	
	}
	
	return gOLTrain;
}

GameObjectLight* GameObjectLightManager::GetGOLTrainById(Ogre::uint32 aId)
{
	GameObjectLight* gOLTrain = 0;	
	for(std::vector<sGameLight>::iterator it = _GOLTrainVector.begin(); it!= _GOLTrainVector.end(); it++)
	{		
		if(it->LightId == aId)
		{
			gOLTrain = it->GOLight;	
			break;
		}		
	}
	
	return gOLTrain;
}

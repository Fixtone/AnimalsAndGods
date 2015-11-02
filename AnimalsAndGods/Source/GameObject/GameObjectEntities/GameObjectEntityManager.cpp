#include "stdafx.h"
#include "../../Header/GameObject/GameObjectEntities/GameObjectEntityManager.h"

using namespace GOE;

template<> GameObjectEntityManager* Ogre::Singleton<GameObjectEntityManager>::msSingleton = 0;
GameObjectEntityManager* GameObjectEntityManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
GameObjectEntityManager& GameObjectEntityManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

GameObjectEntityManager::GameObjectEntityManager()
{
}

GameObjectEntityManager::~GameObjectEntityManager()
{
}

void GameObjectEntityManager::initialiseManager(Ogre::SceneManager* aSceneManager)
{
	_SceneManager = aSceneManager;	
}

void GameObjectEntityManager::clearManager()
{	
}

void GameObjectEntityManager::configureGOE()
{	
}

void GameObjectEntityManager::releaseGOE()
{	
	BOOST_FOREACH(MapGameObjectEntityWorldStatic::value_type& gameObjectEntityWorldStatic, _MapGameObjectEntityWorldStatic)
		delete gameObjectEntityWorldStatic.second;
	
	_MapGameObjectEntityWorldStatic.clear();

	BOOST_FOREACH(MapGameObjectEntityWorldMovable::value_type& gameObjectEntityWorldMovable, _MapGameObjectEntityWorldMovable)
		delete gameObjectEntityWorldMovable.second;
	
	_MapGameObjectEntityWorldMovable.clear();

	BOOST_FOREACH(MapGameObjectEntityWorld::value_type& gameObjectEntityWorld, _MapGameObjectEntityWorld)
		delete gameObjectEntityWorld.second;
	
	_MapGameObjectEntityWorld.clear();	
}

bool GameObjectEntityManager::frameStartedGOE(const Ogre::Real aElapsedTime)
{
	return true;
}

bool GameObjectEntityManager::frameEndedGOE(const Ogre::Real aElapsedTime)
{
	return true;
}

bool GameObjectEntityManager::updateGOE(const Ogre::Real aElapsedTime)
{
	return true;
}
			
bool GameObjectEntityManager::updateLogicGOE(const Ogre::Real aElapsedTime)
{
	return true;
}

bool GameObjectEntityManager::createGOE(Ogre::int32 aGameObjectId, ShareData::GameConfigurations::PhysicsConfigurations::GameObjectEntityPhysicsType aGameObjectEntityPhysicsType,
										ShareData::GameConfigurations::LoadersConfigurations::GameObjectEntityType aGameObjectEntityType, 
						                Ogre::SceneNode* aGOESceneNode, Ogre::String aGOEEntityMeshFileName, Ogre::String aGOEEntityMaterialName, bool aGOEEntityCastShadows, bool aHasLODs, 
						                int aNumberLODs, std::vector<Ogre::String> aLODsDistances, Ogre::Real aBodyMass)
{
	try
	{
		switch(aGameObjectEntityType)
		{
			case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC:
			{
				Ogre::String name;
				name = Ogre::StringConverter::toString(aGameObjectId) + "#E";
				Ogre::Entity* gOEEntity = Tools::CreateEntity(_SceneManager, aGOESceneNode, name, "Play", aGOEEntityMeshFileName, aGOEEntityMaterialName, 
															   aGOEEntityCastShadows, aHasLODs, aNumberLODs, aLODsDistances);

				GameObjectEntity* gameObjectEntity = new GameObjectEntity(aGameObjectId,
																		  aGameObjectEntityPhysicsType,
																		  aGameObjectEntityType,
																		  aGOESceneNode,
																		  gOEEntity,
																		  aHasLODs,
																		  aNumberLODs,
																		  aLODsDistances);																		

				boost::unordered_map<Ogre::int32, GameObjectEntity*>::value_type gameObjectEntityValue_Type(aGameObjectId,
																											gameObjectEntity);
				_MapGameObjectEntityWorldStatic.insert(gameObjectEntityValue_Type);		

				break;
			}

			case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDMOVABLE:
			{
				Ogre::String name;
				name = Ogre::StringConverter::toString(aGameObjectId) + "#E";
				Ogre::Entity* gOEEntity = Tools::CreateEntity(_SceneManager, aGOESceneNode, name, "Play", aGOEEntityMeshFileName, aGOEEntityMaterialName, 
															   aGOEEntityCastShadows, aHasLODs, aNumberLODs, aLODsDistances);

				GameObjectEntity* gameObjectEntity = new GameObjectEntity(aGameObjectId,
																		  aGameObjectEntityPhysicsType,
																		  aGameObjectEntityType,
																		  aGOESceneNode,
																		  gOEEntity,
																		  aHasLODs,
																		  aNumberLODs,
																		  aLODsDistances,
																		  aBodyMass);																		

				boost::unordered_map<Ogre::int32, GameObjectEntity*>::value_type gameObjectEntityValue_Type(aGameObjectId,
																											gameObjectEntity);
				_MapGameObjectEntityWorldMovable.insert(gameObjectEntityValue_Type);		

				break;
			}
			case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLD:
			{
				Ogre::String name;
				name = Ogre::StringConverter::toString(aGameObjectId) + "#E";
				Ogre::Entity* gOEEntity = Tools::CreateEntity(_SceneManager, aGOESceneNode, name, "Play", aGOEEntityMeshFileName, aGOEEntityMaterialName, 
															   aGOEEntityCastShadows, aHasLODs, aNumberLODs, aLODsDistances);

				GameObjectEntity* gameObjectEntity = new GameObjectEntity(aGameObjectId,
																		  aGameObjectEntityPhysicsType,
																		  aGameObjectEntityType,
																		  aGOESceneNode,
																		  gOEEntity,
																		  aHasLODs,
																		  aNumberLODs,
																		  aLODsDistances);																		

				boost::unordered_map<Ogre::int32, GameObjectEntity*>::value_type gameObjectEntityValue_Type(aGameObjectId,
																											gameObjectEntity);
				_MapGameObjectEntityWorld.insert(gameObjectEntityValue_Type);		

				break;
			}
		};

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("GameObjectEntityManager::createGOE || Desc: " + e.getDescription());
		return false;
	}
}

GameObjectEntity* GameObjectEntityManager::GetGOE(Ogre::String aGOEName, ShareData::GameConfigurations::LoadersConfigurations::GameObjectEntityType aGOEType)
{
	GameObjectEntity* gOE = 0;	

	switch(aGOEType)
	{
		case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC:
		{
			BOOST_FOREACH(MapGameObjectEntityWorldStatic::value_type& gameObjectEntityWorldStatic, _MapGameObjectEntityWorldStatic)
			{
				if(Ogre::StringUtil::match(gameObjectEntityWorldStatic.second->mGOESceneNode->getName(),aGOEName))
				{
					gOE = gameObjectEntityWorldStatic.second;	
					break;
				}
			}
			
		}
		break;
		case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDMOVABLE:
		{
			BOOST_FOREACH(MapGameObjectEntityWorldMovable::value_type& gameObjectEntityWorldMovable, _MapGameObjectEntityWorldMovable)
			{
				if(Ogre::StringUtil::match(gameObjectEntityWorldMovable.second->mGOESceneNode->getName(),aGOEName))
				{
					gOE = gameObjectEntityWorldMovable.second;	
					break;
				}
			}			
		}
		break;
		case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLD:
		{
			BOOST_FOREACH(MapGameObjectEntityWorld::value_type& gameObjectEntityWorld, _MapGameObjectEntityWorld)		
			{
				if(Ogre::StringUtil::match(gameObjectEntityWorld.second->mGOESceneNode->getName(),aGOEName))
				{
					gOE = gameObjectEntityWorld.second;
					break;
				}
			}			
		}
		break;
		
	};	
	
	return gOE;
}

void GameObjectEntityManager::explodeAllBodies(float aForce)
{
	BOOST_FOREACH(MapGameObjectEntityWorldMovable::value_type& gameObjectEntityWorldMovable, _MapGameObjectEntityWorldMovable)
	{		
		gameObjectEntityWorldMovable.second->GOEData.mBody->addForce(NxOgre::Vec3(0,aForce,0), NxOgre::Enums::ForceMode_Impulse);		
	}
}
#ifndef GameObjectEntity_H	
#define GameObjectEntity_H

#include "../../stdafx.h"

class GameObjectEntity : public GameObject
{
	public:				

		GameObjectEntity(Ogre::int32 aGameObjectId, ShareData::GameConfigurations::PhysicsConfigurations::GameObjectEntityPhysicsType aGameObjectEntityPhysicsType,
						 ShareData::GameConfigurations::LoadersConfigurations::GameObjectEntityType aGameObjectEntityType, 
						 Ogre::SceneNode* aGOESceneNode, Ogre::Entity* aGOEEntity, bool aHasLODs, int aNumberLODs, std::vector<Ogre::String> aLODsDistances, Ogre::Real aBodyMass = 0)
		: GameObject(aGameObjectId)	
		, mGameObjectEntityType(aGameObjectEntityType)
		, mGOESceneNode(aGOESceneNode)		
		, mGOEEntity(aGOEEntity)
		, mHasLODs(aHasLODs)
		, mNumberLODs(aNumberLODs)
		{
			/*bool a = false;
			if(Ogre::StringUtil::startsWith(aGOESceneNode->getName(),"SFKiller"))
				a = true;*/

			Ogre::String name("");
			switch(aGameObjectEntityType)
			{
				case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLD:
				{
					GOEData.mGameObjectEntityPhysicsType = aGameObjectEntityPhysicsType;
					GOEData.mSceneGeometry = 0;
					GOEData.mBody = 0;					
					break;
				}
				case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC:
				{
					name = Ogre::StringConverter::toString(mGameObjectId) + "#SG";
					NxOgre::SceneGeometry* sceneGeometry = PhysicsManager::getSingletonPtr()->buildSceneGeometryEntity(name, mGOEEntity, mGOEEntity->getMesh()->getName(),
																													   aGOESceneNode->_getDerivedPosition(),
																													   aGOESceneNode->_getDerivedOrientation());

					GOEData.mGameObjectEntityPhysicsType = aGameObjectEntityPhysicsType;
					GOEData.mSceneGeometry = sceneGeometry;
					GOEData.mBody = 0;					
					break;
				}
				case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDMOVABLE:
				{
					name = Ogre::StringConverter::toString(mGameObjectId) + "#SB";
					Critter::Body* body = PhysicsManager::getSingletonPtr()->buildBodyGameObject(name,
																							     mGOEEntity,
																								 aGOESceneNode->_getDerivedPosition(),
																								 aGOESceneNode->_getDerivedOrientation(),
																								 aBodyMass);

					GOEData.mGameObjectEntityPhysicsType = aGameObjectEntityPhysicsType;
					GOEData.mSceneGeometry = 0;
					GOEData.mBody = body;					
					break;
				}
			};
		}	
		
		virtual ~GameObjectEntity()
		{
			switch(mGameObjectEntityType)
			{
				case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLD:
				{								
					break;
				}
				case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC:
				{					
					PhysicsManager::getSingletonPtr()->destroySceneGeometry(GOEData.mSceneGeometry);					
					break;
				}
				case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDMOVABLE:
				{
					PhysicsManager::getSingletonPtr()->destroyBody(GOEData.mBody);
					break;
				}
			};
			
		}	
 
	public:
		
		struct sGOEData
		{			
			ShareData::GameConfigurations::PhysicsConfigurations::GameObjectEntityPhysicsType	mGameObjectEntityPhysicsType;
			NxOgre::SceneGeometry*																mSceneGeometry;			
			Critter::Body*																		mBody;
		}GOEData;

		ShareData::GameConfigurations::LoadersConfigurations::GameObjectEntityType	mGameObjectEntityType;
		Ogre::SceneNode*															mGOESceneNode;
		Ogre::Entity*																mGOEEntity;
		bool																		mHasLODs;
		int																			mNumberLODs;
		std::vector<Ogre::String>													mLODsDistances;

 };
#endif
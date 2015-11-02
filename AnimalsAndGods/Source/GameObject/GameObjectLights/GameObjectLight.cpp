#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectLights/GameObjectLight.h"


GameObjectLight::GameObjectLight(Ogre::int32 aGameObjectId, ShareData::GameConfigurations::LoadersConfigurations::GameObjectLightType aGameObjectLightType, 
							     Ogre::SceneNode* aGOLSceneNode, Ogre::Light* aGOLLight)
: GameObject(aGameObjectId)	
, mGameObjectLightType(aGameObjectLightType)
, mGOLSceneNode(aGOLSceneNode)		
, mGOLLight(aGOLLight)		
{
	mGOLLight->setVisible(false);
	mGOLSceneNode->attachObject(mGOLLight);
}	
		
GameObjectLight::~GameObjectLight()
{			
	Tools::DestroyLight(GameManager::getSingletonPtr()->getSceneManager(), mGOLLight);
	Tools::Destroy(GameManager::getSingletonPtr()->getSceneManager(), mGOLSceneNode->getName());
}				

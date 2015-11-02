#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectNodes/GameObjectNodeHydrant.h"

GameObjectNodeHydrant::GONHydrantStates GameObjectNodeHydrant::StringToGONHydrantState(Ogre::String aString)
{
	const char* str = aString.c_str();

	if(strcmp ( "On", str ) == 0)       return GameObjectNodeHydrant::Open;
	else								return GameObjectNodeHydrant::Close;	
}

GameObjectNodeHydrant::GameObjectNodeHydrant(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aHydrantEntityName, Ogre::String aHydrantLeftPUName,
									 Ogre::String aHydrantRightPUName, GONHydrantStates aGONHydrantState)
: GameObjectNode(aGameObjectId, aGONSceneNode)			
, _HydrantEntityName(aHydrantEntityName)		
, _HydrantLeftPUName(aHydrantLeftPUName)
, _HydrantRightPUName(aHydrantRightPUName)
, _GONHydrantState(aGONHydrantState)	
{			
}	

GameObjectNodeHydrant::~GameObjectNodeHydrant()
{
}
 
void GameObjectNodeHydrant::configure()
{		
	_HydrantEntity = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(_HydrantEntityName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC);
	_HydrantLeftPU = GOPS::GameObjectParticleSystemsManager::getSingletonPtr()->GetGOPSParticleUnivers(_HydrantLeftPUName);
	_HydrantRightPU = GOPS::GameObjectParticleSystemsManager::getSingletonPtr()->GetGOPSParticleUnivers(_HydrantRightPUName);

	_GONHydrantParameters.timeLife = 10;
	_HydrantLeftPU->getParticleSystem()->stop();
	_HydrantRightPU->getParticleSystem()->stop();
}

void GameObjectNodeHydrant::release()
{	
}

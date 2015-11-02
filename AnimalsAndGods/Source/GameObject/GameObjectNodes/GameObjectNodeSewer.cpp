#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectNodes/GameObjectNodeSewer.h"

GameObjectNodeSewer::GONSewerStates GameObjectNodeSewer::StringToGONSewerState(Ogre::String aString)
{
	const char* str = aString.c_str();

	if(strcmp ( "On", str ) == 0)       return GameObjectNodeSewer::On;	
	else								return GameObjectNodeSewer::Off;	
}

GameObjectNodeSewer::GameObjectNodeSewer(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aSewerEntityName, Ogre::String aSewerPUName,
										 GONSewerStates aGONSewerState)
: GameObjectNode(aGameObjectId, aGONSceneNode)		
, mSewerEntityName(aSewerEntityName)
, mSewerPUName(aSewerPUName)
, mSewerEntity(0)		
, mGOPUSewer(0)
, mGONSewerState(aGONSewerState)
{			
}	

GameObjectNodeSewer::~GameObjectNodeSewer()
{
}
 
void GameObjectNodeSewer::configure()
{		
	mSewerEntity = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(mSewerEntityName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC);
	mGOPUSewer = GOPS::GameObjectParticleSystemsManager::getSingletonPtr()->GetGOPSParticleUnivers(mSewerPUName);
	mGOPUSewer->getParticleSystem()->setRenderingDistance(5);
};

void GameObjectNodeSewer::release()
{	
};

bool GameObjectNodeSewer::update(const Ogre::Real aElapsedTime)
{
	return true;
}

void GameObjectNodeSewer::updateLogic(lua_State *L, const float elapsedSeconds)
{		
}
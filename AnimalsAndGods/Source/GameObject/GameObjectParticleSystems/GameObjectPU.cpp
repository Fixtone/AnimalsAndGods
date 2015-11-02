#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectParticleSystems/GameObjectPU.h"


GameObjectPU::GameObjectPU(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aPUScriptName)
: GameObject(aGameObjectId)		
, mGOPUSceneNode(aGONSceneNode)
, mPUParticleSystem(0)
, mPUParticleSystemName(Ogre::StringConverter::toString(aGameObjectId) + "#PU")
, mPUParticleSystemScriptName(aPUScriptName)
{	
	mPUParticleSystem = Particles::ParticleUniverseManager::getSingletonPtr()->createParticleSystemByName(mPUParticleSystemName, mPUParticleSystemScriptName);	
	mPUParticleSystem->setRenderingDistance(50);		
	mPUParticleSystem->start();
	mGOPUSceneNode->attachObject(mPUParticleSystem);	
}	
 
GameObjectPU::~GameObjectPU()
{
	if(mPUParticleSystem)
	{
		mPUParticleSystem->stop();
		Particles::ParticleUniverseManager::getSingletonPtr()->removeParticleSystemByName(mPUParticleSystemName, mPUParticleSystemScriptName);
	}

	Tools::Destroy(GameManager::getSingletonPtr()->getSceneManager(), mGOPUSceneNode->getName());
}

Ogre::SceneNode* GameObjectPU::getGOPUSceneNode()
{
	return mGOPUSceneNode;
}

ParticleUniverse::ParticleSystem* GameObjectPU::getParticleSystem()
{
	return mPUParticleSystem;
}

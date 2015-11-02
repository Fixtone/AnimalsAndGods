#include "stdafx.h"
#include "../../../Header/Particles/ParticleUniverse/ParticleUniverseManager.h"

using namespace Particles;

template<> ParticleUniverseManager* Ogre::Singleton<ParticleUniverseManager>::msSingleton = 0;
ParticleUniverseManager* ParticleUniverseManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
ParticleUniverseManager& ParticleUniverseManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

ParticleUniverseManager::ParticleUniverseManager()
{
	_SceneManager = 0;
}

ParticleUniverseManager::~ParticleUniverseManager()
{
}

bool ParticleUniverseManager::initializeParticleUniverseManager(Ogre::SceneManager* aSceneManager)
{
	try
	{		
		_SceneManager = aSceneManager;			
		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}

ParticleUniverse::ParticleSystem* ParticleUniverseManager::createParticleSystemByName(Ogre::String aPsName, Ogre::String aPsTemplateName)
{
	try
	{		
		ParticleUniverse::ParticleSystem* pSys = ParticleUniverse::ParticleSystemManager::getSingletonPtr()->createParticleSystem(aPsName, aPsTemplateName, _SceneManager);		
		pSys->setRenderQueueGroup(Ogre::RENDER_QUEUE_WORLD_GEOMETRY_2);
		return pSys;
	}	
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return 0;
	}

}

void ParticleUniverseManager::removeParticleSystemByName(Ogre::String aPsName, Ogre::String aPsTemplateName)
{
	try
	{		
		ParticleUniverse::ParticleSystemManager::getSingletonPtr()->destroyParticleSystem(aPsName,_SceneManager);
	}	
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());		
	}

}

bool ParticleUniverseManager::clearParticleUniverseManager()
{		
	//ParticleUniverse::ParticleSystemManager::getSingletonPtr()->destroyAllParticleSystems(_SceneManager);	
	/*
	//Free EntityWorld Nodes
	for(std::vector<EntityWorld*>::iterator it = _VectorEntityWorld.begin(); it != _VectorEntityWorld.end(); it++)
		Tools::Destroy(_SceneManager,(*it)->GetSceneNode()->getName());

	for(std::vector<EntityWorldLOD*>::iterator it = _VectorEntityWorldLOD.begin(); it != _VectorEntityWorldLOD.end(); it++)
		Tools::Destroy(_SceneManager,(*it)->GetSceneNode()->getName());

	for(std::vector<EntitySceneGeometry*>::iterator it = _VectorEntitySceneGeometry.begin(); it != _VectorEntitySceneGeometry.end(); it++)
		Tools::Destroy(_SceneManager,(*it)->GetSceneNode()->getName());

	BOOST_FOREACH(MapEntityLightReactive::value_type& entityLightReactive, _MapEntityLightReactive)
		Tools::Destroy(_SceneManager, entityLightReactive.second->GetSceneNode()->getName());
		
	_VectorEntityWorld.clear();
	_VectorEntityWorldLOD.clear();
	_VectorEntitySceneGeometry.clear();
	
	_MapEntityLightReactive.clear();*/
	return true;
}
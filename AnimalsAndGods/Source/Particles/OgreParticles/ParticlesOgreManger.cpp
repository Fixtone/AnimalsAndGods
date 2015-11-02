#include "stdafx.h"
#include "../../../Header/Particles/OgreParticles/ParticleOgreManager.h"

using namespace Particles;

template<> ParticleOgreManager* Ogre::Singleton<ParticleOgreManager>::msSingleton = 0;
ParticleOgreManager* ParticleOgreManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
ParticleOgreManager& ParticleOgreManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

ParticleOgreManager::ParticleOgreManager()
{
}

ParticleOgreManager::~ParticleOgreManager()
{
}

void ParticleOgreManager::initializeParticleOgreManagerManager(Ogre::SceneManager* aSceneManager)
{
	_SceneManager = aSceneManager;
	//GeomUtils::createCone("ParticlesOgre", 0.25f,0.25f, 4);
}

void ParticleOgreManager::clearParticleOgreManagerManager()
{	
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
}

Ogre::ParticleSystem* ParticleOgreManager::createOgreParticleSystem(Ogre::SceneNode* aNodeAttachPUParticleSystem, Ogre::String aPSName, Ogre::String aPSTemplate)
{
	try
	{
		// create a particle system named explosions using the explosionTemplate
		Ogre::ParticleSystem* pS = _SceneManager->createParticleSystem(aPSName, aPSTemplate);	 		
		// fast forward 1 second  to the point where the particle has been emitted
		pS->fastForward(1.0);

		//Ogre::SceneNode* childDebug = aNodeAttachPUParticleSystem->createChildSceneNode(pS->getName() + "Debug");	
		//Ogre::Entity* entityDebug = _SceneManager->createEntity(pS->getName() + "_PSGeomEntity", "ParticlesOgre");

		// Create coloured material
		//Ogre::String materialName = pS->getName() + "_MaterialPSGeomEntity";
		//Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MaterialPSGeomEntity", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
		//Ogre::Pass* pass = material->getTechnique(0)->getPass(0);
		//pass->setDiffuse(Ogre::ColourValue::Red);
		//pass->setAmbient(Ogre::ColourValue::Red);
		//pass->setSelfIllumination(Ogre::ColourValue::Red);			
		//entityDebug->setMaterial(material);		
		//entityDebug->setRenderQueueGroup(Shaders::DeferredShadingManager::POST_GBUFFER_RENDER_QUEUE);

		//childDebug->attachObject(entityDebug);		
		//childDebug->setVisible(false);	

		return pS;
	}
	catch(Ogre::Exception e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[ParticleOgreManager]: " + e.getDescription());
		return 0;
	}
}

void ParticleOgreManager::destroyAllParticleSystem()
{	
	_SceneManager->destroyAllParticleSystems();
}

void ParticleOgreManager::destroyParticleSystem(Ogre::ParticleSystem* aOgreParticleSystem)
{
	_SceneManager->destroyParticleSystem(aOgreParticleSystem);
}
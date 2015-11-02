#ifndef ParticlesUniverseManager_H
#define ParticlesUniverseManager_H

//Particle Universe
#include "ParticleUniverseSystemManager.h"
#include "ParticleUniverseException.h"

namespace Particles
{
	class ParticleUniverseManager : public Ogre::Singleton<ParticleUniverseManager>
							      , public Ogre::FrameListener
	{
		public:	

			ParticleUniverseManager();
			~ParticleUniverseManager();		

			static ParticleUniverseManager& getSingleton(void);
			static ParticleUniverseManager* getSingletonPtr(void);

			bool initializeParticleUniverseManager(Ogre::SceneManager* aSceneManager);
			bool clearParticleUniverseManager();			

			ParticleUniverse::ParticleSystem* createParticleSystemByName(Ogre::String aPsName, Ogre::String aPsTemplateName);
			void removeParticleSystemByName(Ogre::String aPsName, Ogre::String aPsTemplateName);

		private:

			Ogre::SceneManager*							_SceneManager;	
	};
}
#endif
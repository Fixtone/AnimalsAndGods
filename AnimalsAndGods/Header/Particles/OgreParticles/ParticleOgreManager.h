#ifndef ParticleOgreManager_H
#define ParticleOgreManager_H

#include "../../../Header/Tools/ShareData.h"

namespace Particles
{
	class ParticleOgreManager : public Ogre::Singleton<ParticleOgreManager>
	{
		public:	

			ParticleOgreManager();
			~ParticleOgreManager();		

			static ParticleOgreManager& getSingleton(void);
			static ParticleOgreManager* getSingletonPtr(void);

			void initializeParticleOgreManagerManager(Ogre::SceneManager* aSceneManager);
			void clearParticleOgreManagerManager();		

			Ogre::ParticleSystem* createOgreParticleSystem(Ogre::SceneNode* aNodeAttachPUParticleSystem, Ogre::String aPSName, Ogre::String aPSTemplate);
			void destroyAllParticleSystem();
			void destroyParticleSystem(Ogre::ParticleSystem* aOgreParticleSystem);

		private:

			Ogre::SceneManager* _SceneManager;			

	};
}
#endif
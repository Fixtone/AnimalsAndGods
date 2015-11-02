#ifndef GameObjectPU_H
#define GameObjectPU_H

class GameObjectPU : public GameObject
{						
	public:			

		GameObjectPU(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aPUScriptName);
		virtual ~GameObjectPU();	

		Ogre::SceneNode*					getGOPUSceneNode();
		ParticleUniverse::ParticleSystem*	getParticleSystem();

	private:		

		Ogre::String						mPUParticleSystemName;
		Ogre::String						mPUParticleSystemScriptName;
		Ogre::SceneNode*					mGOPUSceneNode;
		ParticleUniverse::ParticleSystem*	mPUParticleSystem;		
		
 };
#endif

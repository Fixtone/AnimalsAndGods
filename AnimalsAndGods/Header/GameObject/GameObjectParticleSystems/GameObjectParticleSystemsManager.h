#ifndef GameObjectParticleSystemsManager_H
#define GameObjectParticleSystemsManager_H
	 
namespace GOPS
{
	class GameObjectParticleSystemsManager : public Ogre::Singleton<GameObjectParticleSystemsManager>
	{
		public:	

			GameObjectParticleSystemsManager();
			~GameObjectParticleSystemsManager();		

			static GameObjectParticleSystemsManager& getSingleton(void);
			static GameObjectParticleSystemsManager* getSingletonPtr(void);

			void initialiseManager(Ogre::SceneManager* aSceneManager);
			void clearManager();				
			void configureGOPS();
			void releaseGOPS();			

			bool frameStartedGOPS(const Ogre::Real aElapsedTime);			
			bool frameEndedGOPS(const Ogre::Real aElapsedTime);

			bool updateGOPS(const Ogre::Real aElapsedTime);			
			bool updateLogicGOPS(const Ogre::Real aElapsedTime);

			bool createGOPSParticleUnivers(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aPUScriptName);				
			
			GameObjectPU* GetGOPSParticleUnivers(Ogre::String aGameObjectPUName);

		private:
		
			Ogre::SceneManager*						_SceneManager;
						
			typedef boost::unordered_map<Ogre::int32, GameObjectPU*> MapGameObjectPU;
			MapGameObjectPU _MapGameObjectPU;			
			
			//typedef boost::unordered_map<Ogre::int32, GameObjectNodeStreetLight*> MapGameObjectNodeStreetLight;
			//MapGameObjectNodeStreetLight _MapGameObjectNodeStreetLight;					

	};
}
#endif
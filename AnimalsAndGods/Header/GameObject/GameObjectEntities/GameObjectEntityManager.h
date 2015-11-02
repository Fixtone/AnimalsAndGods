#ifndef GameObjectEntityManager_H
#define GameObjectEntityManager_H
	 
namespace GOE
{
	class GameObjectEntityManager : public Ogre::Singleton<GameObjectEntityManager>
	{
		public:	

			GameObjectEntityManager();
			~GameObjectEntityManager();		

			static GameObjectEntityManager& getSingleton(void);
			static GameObjectEntityManager* getSingletonPtr(void);

			void initialiseManager(Ogre::SceneManager* aSceneManager);
			void clearManager();				
			void configureGOE();
			void releaseGOE();			

			bool frameStartedGOE(const Ogre::Real aElapsedTime);			
			bool frameEndedGOE(const Ogre::Real aElapsedTime);

			bool updateGOE(const Ogre::Real aElapsedTime);
			bool updateLogicGOE(const Ogre::Real aElapsedTime);

			bool createGOE(Ogre::int32 aGameObjectId, ShareData::GameConfigurations::PhysicsConfigurations::GameObjectEntityPhysicsType aGameObjectEntityPhysicsType,
						   ShareData::GameConfigurations::LoadersConfigurations::GameObjectEntityType aGameObjectEntityType, 
						   Ogre::SceneNode* aGOESceneNode, Ogre::String aGOEEntityMeshFileName, Ogre::String aGOEEntityMaterialName, bool aGOEEntityCastShadows, bool aHasLODs, 
						   int aNumberLODs, std::vector<Ogre::String> aLODsDistances, Ogre::Real aBodyMass = 0);

			GameObjectEntity* GetGOE(Ogre::String aGOEName, ShareData::GameConfigurations::LoadersConfigurations::GameObjectEntityType aGOEType);
			
			void explodeAllBodies(float aForce);
			
		private:
		
			Ogre::SceneManager*						_SceneManager;
						
			typedef boost::unordered_map<Ogre::int32, GameObjectEntity*> MapGameObjectEntityWorldStatic;
			MapGameObjectEntityWorldStatic _MapGameObjectEntityWorldStatic;		

			typedef boost::unordered_map<Ogre::int32, GameObjectEntity*> MapGameObjectEntityWorldMovable;
			MapGameObjectEntityWorldMovable _MapGameObjectEntityWorldMovable;	

			typedef boost::unordered_map<Ogre::int32, GameObjectEntity*> MapGameObjectEntityWorld;
			MapGameObjectEntityWorld _MapGameObjectEntityWorld;		
	};
}
#endif
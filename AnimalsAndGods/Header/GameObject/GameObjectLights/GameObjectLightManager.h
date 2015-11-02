#ifndef GameObjectLightManager_H
#define GameObjectLightManager_H
	 
namespace GOL
{
	class GameObjectLightManager : public Ogre::Singleton<GameObjectLightManager>		
	{
		public:	

			struct sGameLight
			{
				Ogre::int32			LightId;
				GameObjectLight*	GOLight;
			};

			GameObjectLightManager();
			~GameObjectLightManager();		

			static GameObjectLightManager& getSingleton(void);
			static GameObjectLightManager* getSingletonPtr(void);

			void initialiseManager(Ogre::SceneManager* aSceneManager);
			void clearManager();
		
			void configureGOL();
			void releaseGOL();			
			bool frameStartedGOL(const Ogre::Real aElapsedTime);			
			bool frameEndedGOL(const Ogre::Real aElapsedTime);
			bool updateGOL(const Ogre::Real aElapsedTime);
			bool updateLogicGOL(const Ogre::Real aElapsedTime);

			bool createGOLight(Ogre::int32 aGameObjectId, ShareData::GameConfigurations::LoadersConfigurations::GameObjectLightType aGameObjectLightType, 
							   Ogre::SceneNode* aGOLSceneNode, Ogre::Light* aGOLLight);

			GameObjectLight* GetGOLStreetLight(Ogre::String aGOLStreetLightName);
			GameObjectLight* GetGOLStreetLightById(Ogre::uint32 aId);	

			GameObjectLight* GetGOLAmbient(Ogre::String aGOLAmbientLightName);
			GameObjectLight* GetGOLAmbientById(Ogre::uint32 aId);	

			GameObjectLight* GetGOLFarAmbient(Ogre::String aGOLFarAmbientLightName);
			GameObjectLight* GetGOLFarAmbientById(Ogre::uint32 aId);	

			GameObjectLight* GetGOLTrain(Ogre::String aGOLStreetLightName);
			GameObjectLight* GetGOLTrainById(Ogre::uint32 aId);	
			
		private:
		
			Ogre::SceneManager*						_SceneManager;
			
			std::vector<sGameLight>					_GOLStreetLightVector;
			std::vector<sGameLight>					_GOLAmbientVector;
			std::vector<sGameLight>					_GOLFarAmbientVector;
			std::vector<sGameLight>					_GOLTrainVector;

	};
}
#endif
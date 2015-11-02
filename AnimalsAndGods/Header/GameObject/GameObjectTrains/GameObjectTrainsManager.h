#ifndef GameObjectTrainsManager_H
#define GameObjectTrainsManager_H
	 
namespace GOT
{
	class GameObjectTrainsManager : public Ogre::Singleton<GameObjectTrainsManager>
								  , public LuaInterface
	{
		public:							

			struct sGOTrainData
			{
				Ogre::String		TrainName;
				GameObjectTrain*	GOTrain;
			};

			GameObjectTrainsManager();
			~GameObjectTrainsManager();		

			static GameObjectTrainsManager& getSingleton(void);
			static GameObjectTrainsManager* getSingletonPtr(void);

			void initialiseManager(Ogre::SceneManager* aSceneManager);
			void clearManager();		
			
			void configureGON();
			void releaseGON();			

			bool frameStartedGON(const Ogre::Real aElapsedTime);			
			bool frameEndedGON(const Ogre::Real aElapsedTime);

			bool updateGON(const Ogre::Real aElapsedTime);
			bool updateLogicGON(const Ogre::Real aElapsedTime);

			bool createGONTrain(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, const Ogre::String &aTrainLightName, 
							    const Ogre::String &aWayPointsRouteName, GameObjectTrain::GONTrainStates aGONTrainState,
							    Ogre::Real aSpeed, Ogre::Real aMinStopTime, Ogre::Real aMaxStopTime);
	
			LUA_INTERFACE();

			// Entity Lib (exported to Lua)
			LUA_LIBRARY("GameObjectTrainsManager", gameObjectTrainsManagerLib);

		private:
		
			Ogre::SceneManager*						_SceneManager;		

			std::vector<sGOTrainData>				_GOTrainVector;
	};
}
#endif
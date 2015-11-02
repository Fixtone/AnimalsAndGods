#ifndef GameObjectSpaceShipsManager_H
#define GameObjectSpaceShipsManager_H
	 
namespace GOSS
{
	class GameObjectSpaceShipsManager : public Ogre::Singleton<GameObjectSpaceShipsManager>
									  , public LuaInterface
	{
		public:							

			GameObjectSpaceShipsManager();
			~GameObjectSpaceShipsManager();		

			static GameObjectSpaceShipsManager& getSingleton(void);
			static GameObjectSpaceShipsManager* getSingletonPtr(void);

			void initialiseManager(Ogre::SceneManager* aSceneManager);
			void clearManager();		
			
			void configureGON();
			void releaseGON();			

			bool frameStartedGON(const Ogre::Real aElapsedTime);			
			bool frameEndedGON(const Ogre::Real aElapsedTime);

			bool updateGON(const Ogre::Real aElapsedTime);
			bool updateLogicGON(const Ogre::Real aElapsedTime);

			bool createGONSpaceShip(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, const Ogre::String &aGOESpaceShipName, const Ogre::String &aSpaceShipNodeTrackAnimationName,
									const Ogre::String &aSpaceShipWayPointsRouteName, Ogre::Real aSpaceShipSpeed, Ogre::Real aSpaceShipLandMinStopTime,
									Ogre::Real aSpaceShipLandMaxStopTime, GameObjectSpaceShip::GONSpaceShipStates aGONSpaceShipState);
	
			LUA_INTERFACE();

			// Entity Lib (exported to Lua)
			LUA_LIBRARY("GameObjectSpaceShipsManager", gameObjectSpaceShipsManagerLib);

		private:
		
			Ogre::SceneManager*						_SceneManager;		

			typedef boost::unordered_map<Ogre::String, GameObjectSpaceShip*> MapGameObjectSpaceShip;
			MapGameObjectSpaceShip _MapGameObjectSpaceShip;

	};
}
#endif
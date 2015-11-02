#ifndef GameObjectCharactersManager_H
#define GameObjectCharactersManager_H
	 
namespace GOCH
{
	class GameObjectCharactersManager : public Ogre::Singleton<GameObjectCharactersManager>
									  , public LuaInterface
	{
		public:										

			GameObjectCharactersManager();
			~GameObjectCharactersManager();		

			static GameObjectCharactersManager& getSingleton(void);
			static GameObjectCharactersManager* getSingletonPtr(void);

			void initialiseManager(Ogre::SceneManager* aSceneManager);
			void clearManager();		
			
			void configureGOCH();
			void releaseGOCH();			

			bool frameStartedGOCH(const Ogre::Real aElapsedTime);			
			bool frameEndedGOCH(const Ogre::Real aElapsedTime);

			bool updateGOCH(const Ogre::Real aElapsedTime);
			bool updateLogicGOCH(const Ogre::Real aElapsedTime);

			bool createGOCHPlayer(Ogre::SceneNode* aGONSceneNode, Ogre::String aPlayerCameraNodeName);
			bool createGOCHPolice(Ogre::uint32 aPoliceId, Ogre::SceneNode* aGONSceneNode, Ogre::String aPoliceEntityMeshName, Ogre::String aPoliceTalkCameraNodeName,
								   GameObjectPolice::GOCHPoliceStates aGOCHPoliceState);

			GameObjectPlayer* getGOCHPlayer();
	
			LUA_INTERFACE();

			// Entity Lib (exported to Lua)
			LUA_LIBRARY("GameObjectCharactersManager", gameObjectCharactersManagerLib);
			LUA_FUNCTION(getCameraDistanceToGameObjectPolice);		

		private:

			GameObjectPolice* _GetGOPoliceById(Ogre::uint32 aId);
		
			Ogre::SceneManager*						_SceneManager;		

			typedef boost::unordered_map<Ogre::String, GameObjectPlayer*> MapGameObjectPlayer;
			MapGameObjectPlayer _MapGameObjectPlayer;

			typedef boost::unordered_map<Ogre::uint32, GameObjectPolice*> MapGameObjectPolice;
			MapGameObjectPolice _MapGameObjectPolice;

	};
}
#endif
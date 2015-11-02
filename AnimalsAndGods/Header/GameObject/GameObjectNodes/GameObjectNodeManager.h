#ifndef GameObjectNodeManager_H
#define GameObjectNodeManager_H
	 
namespace GON
{
	class GameObjectNodeManager : public Ogre::Singleton<GameObjectNodeManager>		
								, public LuaInterface
	{
		public:	

			GameObjectNodeManager();
			~GameObjectNodeManager();		

			static GameObjectNodeManager& getSingleton(void);
			static GameObjectNodeManager* getSingletonPtr(void);

			void initialiseManager(Ogre::SceneManager* aSceneManager);
			void clearManager();				
			void configureGON();
			void releaseGON();			

			bool frameStartedGON(const Ogre::Real aElapsedTime);			
			bool frameEndedGON(const Ogre::Real aElapsedTime);

			bool updateGON(const Ogre::Real aElapsedTime);
			bool updateLogicGON(const Ogre::Real aElapsedTime);

			bool createGONLighter(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
								  Ogre::String aLPanelInfoName, Ogre::String aLCarLighterName, Ogre::String aLPedrastianLighterName, 
								  GameObjectNodeLighter::GONLighterStates aGONLighterState);

			bool createGONStreetLight(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
									  Ogre::String aGONLightName, Ogre::String aGONStreetLightName, GameObjectNodeStreetLight::GONStreetLightStates aGONStreetLightState);
			
			bool createGONSewer(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aSewerEntityName, Ogre::String aSewerPUName, 
				 			    GameObjectNodeSewer::GONSewerStates aGONSewerState);

			bool createGONHydrant(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aHydrantEntityName, Ogre::String aHydrantLeftPUName,
								  Ogre::String aHydrantRightPUName, GameObjectNodeHydrant::GONHydrantStates aGONHydrantState);

			bool createGONFloorSign(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
									Ogre::String aFloorSignEntityName, Ogre::String aFloorSignBackEntityName, Ogre::String aFloorSignFrontEntityName, 
									GameObjectNodeFloorSign::GONFloorSignStates aGONFloorSignState);

			bool createGONStreetAddonOne(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
										 Ogre::String aStreetAddonOneEntityName, 
										 GameObjectNodeStreetAddonOne::GONStreetAddonOneStates aGONStreetAddonOneState);

			bool createGONStreetAddonTwo(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
										 Ogre::String aStreetAddonTwoEntityName,
										 GameObjectNodeStreetAddonTwo::GONStreetAddonTwoStates aGONStreetAddonTwoState);

			bool createGONStreetAddonThree(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
										   Ogre::String aStreetAddonThreeEntityName,
										   GameObjectNodeStreetAddonThree::GONStreetAddonThreeStates aGONStreetAddonThreeState);

			GameObjectNodeLighter* GetGONLighter(Ogre::String aGONLighterName);
			GameObjectNodeLighter* GetGONLighterById(Ogre::uint32 aId);

			GameObjectNodeFloorSign* GetGONFloorSign(Ogre::String aGONFloorSignName);
			GameObjectNodeFloorSign* GetGONFloorSignById(Ogre::uint32 aId);

			GameObjectNodeStreetLight* GetGONStreetLight(Ogre::String aGONStreetLightName);
			GameObjectNodeStreetLight* GetGONStreetLightById(Ogre::uint32 aId);

			GameObjectNodeStreetAddonOne* GetGONStreetAddonOne(Ogre::String aGONStreetAddonOneName);
			GameObjectNodeStreetAddonOne* GetGONStreetAddonOneById(Ogre::uint32 aId);

			GameObjectNodeStreetAddonTwo* GetGONStreetAddonTwo(Ogre::String aGONStreetAddonTwoName);
			GameObjectNodeStreetAddonTwo* GetGONStreetAddonTwoById(Ogre::uint32 aId);

			GameObjectNodeStreetAddonThree* GetGONStreetAddonThree(Ogre::String aGONStreetAddonThreeName);
			GameObjectNodeStreetAddonThree* GetGONStreetAddonThreeById(Ogre::uint32 aId);

			LUA_INTERFACE();

			// Entity Lib (exported to Lua)
			LUA_LIBRARY("GameObjectNodeManager", gameObjectNodeManagerLib);
			LUA_FUNCTION(getCameraDistanceToGameObjectNodeLighter);		
			LUA_FUNCTION(getCameraDistanceToGameObjectNodeFloorSign);
			LUA_FUNCTION(getCameraDistanceToGameObjectNodeStreetLight);
			LUA_FUNCTION(getCameraDistanceToGameObjectNodeStreetAddonOne);
			LUA_FUNCTION(getCameraDistanceToGameObjectNodeStreetAddonTwo);
			LUA_FUNCTION(getCameraDistanceToGameObjectNodeStreetAddonThree);
			
		private:
		
			Ogre::SceneManager*						_SceneManager;
						
			typedef boost::unordered_map<Ogre::int32, GameObjectNodeLighter*> MapGameObjectNodeLighter;
			MapGameObjectNodeLighter _MapGameObjectNodeLighter;			
			
			typedef boost::unordered_map<Ogre::int32, GameObjectNodeStreetLight*> MapGameObjectNodeStreetLight;
			MapGameObjectNodeStreetLight _MapGameObjectNodeStreetLight;		

			typedef boost::unordered_map<Ogre::int32, GameObjectNodeSewer*> MapGameObjectNodeSewer;
			MapGameObjectNodeSewer _MapGameObjectNodeSewer;	

			typedef boost::unordered_map<Ogre::int32, GameObjectNodeHydrant*> MapGameObjectNodeHydrant;
			MapGameObjectNodeHydrant _MapGameObjectNodeHydrant;	

			typedef boost::unordered_map<Ogre::int32, GameObjectNodeFloorSign*> MapGameObjectNodeFloorSign;
			MapGameObjectNodeFloorSign _MapGameObjectNodeFloorSign;		

			typedef boost::unordered_map<Ogre::int32, GameObjectNodeStreetAddonOne*> MapGameObjectNodeStreetAddonOne;
			MapGameObjectNodeStreetAddonOne _MapGameObjectNodeStreetAddonOne;	

			typedef boost::unordered_map<Ogre::int32, GameObjectNodeStreetAddonTwo*> MapGameObjectNodeStreetAddonTwo;
			MapGameObjectNodeStreetAddonTwo _MapGameObjectNodeStreetAddonTwo;		

			typedef boost::unordered_map<Ogre::int32, GameObjectNodeStreetAddonThree*> MapGameObjectNodeStreetAddonThree;
			MapGameObjectNodeStreetAddonThree _MapGameObjectNodeStreetAddonThree;		

	};
}
#endif
#ifndef GameObjectWayPointsManager_H
#define GameObjectWayPointsManager_H
	 
namespace GOWP
{
	class GameObjectWayPointsManager : public Ogre::Singleton<GameObjectWayPointsManager>
	{
		public:							

			GameObjectWayPointsManager();
			~GameObjectWayPointsManager();		

			static GameObjectWayPointsManager& getSingleton(void);
			static GameObjectWayPointsManager* getSingletonPtr(void);

			void initialiseGameObjectWayPointsManager(Ogre::SceneManager* aSceneManager);
			void clearGameObjectWayPointsManager();		
			void configureGameObjectWayPointsManager();
			void releaseGameObjectWayPointsManager();	

			bool createGameObjectWayPoints(Ogre::int32 &aGameObjectWorldSGId, Ogre::SceneNode* aGameObjectSceneNodeParent,
										   std::vector<Ogre::SceneNode*> amWayPointsVector, 
										   ShareData::GameConfigurations::LoadersConfigurations::WayPointType aWayPointType,
										   Ogre::String aWayPointsName);
	
			bool update(const float elapsedSeconds);		

			void showDebug();
			void hideDebug();

			ShareData::GameConfigurations::GOConfigurations::sWayPointsRoute GetWayPointsRouteByName(Ogre::String aName);
			
		private:
		
			void	_buildDebug();

			Ogre::SceneManager*						_SceneManager;		

			std::vector<ShareData::GameConfigurations::GOConfigurations::sWayPointsRoute> _VectorWayPoints;			

	};
}
#endif
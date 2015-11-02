#ifndef LevelManager_H
#define LevelManager_H

namespace Levels
{
	/** List of Street Light Types */
	enum GameLevelScene
	{
		None		= 0,
		Intro       = 1,
		MainMenu    = 2,
		Loading     = 3,
		Play		= 4,
		Pause		= 5,
		Finish		= 6
	};

	class LevelManager : public Ogre::Singleton<LevelManager>
					   , public Ogre::ResourceGroupListener
					   , public Ogre::ResourceLoadingListener
	{
		public:	

			LevelManager();
			~LevelManager();		

			static LevelManager& getSingleton(void);
			static LevelManager* getSingletonPtr(void);

			void initializeLevelManager(Ogre::Root* aRoot, Ogre::SceneManager* aSceneManager, Ogre::RenderWindow* aRenderWindow);
			void clearLevelManager();

			void createResourceGroupListener();
			void removeResourceGroupListener();

			void loadResourcesGameLevelScene(GameLevelScene aGameLevelSceneToLoad);
			void unloadResourcesGameLevelScene(GameLevelScene aGameLevelSceneToLoad);

			GameLevelScene getGameLevelSceneToLoad(){return _GameLevelSceneToLoad;}
			Ogre::String getGameLevelSceneToLoadString()
			{
				Ogre::String str("");
				switch(_GameLevelSceneToLoad)
				{
					case Intro:
					{
						str = "Intro";
						break;
					}
					case MainMenu:
					{
						str = "MainMenu";
						break;
					}
					case Loading:
					{
						str = "Loading";
						break;
					}
					case Play:
					{
						str = "Play";
						break;
					}
					case Pause:
					{
						str = "Pause";
						break;
					}
					case Finish:
					{
						str = "Finish";
						break;
					}
					default:
						str = "Play";
						break;
				};
				return str;
			}
			void setGameLevelSceneToLoad(GameLevelScene aGameLevelSceneToLoad){_GameLevelSceneToLoad = aGameLevelSceneToLoad;}
	
			// ResourceGroupListener callbacks
			virtual void resourceGroupScriptingStarted(const Ogre::String& groupName, size_t scriptCount);
			virtual void scriptParseStarted(const Ogre::String& scriptName, bool& skipThisScript);
			virtual void scriptParseEnded(const Ogre::String& scriptName, bool skipped);
			virtual void resourceGroupScriptingEnded(const Ogre::String& groupName);
			virtual void resourceGroupLoadStarted(const Ogre::String& groupName, size_t resourceCount);
			virtual void resourceLoadStarted(const Ogre::ResourcePtr& resource);
			virtual void resourceLoadEnded(void);
			virtual void worldGeometryStageStarted(const Ogre::String& description);
			virtual void worldGeometryStageEnded(void);
			virtual void resourceGroupLoadEnded(const Ogre::String& groupName);

			// ResourceLoadingListener callbacks
			virtual bool resourceCollision(Ogre::Resource *resource, Ogre::ResourceManager *resourceManager); 
			virtual Ogre::DataStreamPtr resourceLoading(const Ogre::String &name, const Ogre::String &group, Ogre::Resource *resource);
			virtual void resourceStreamOpened(const Ogre::String &name, const Ogre::String &group, Ogre::Resource *resource, Ogre::DataStreamPtr &dataStream); 

		private:
			
			Ogre::Root*				_Root;
			Ogre::SceneManager*		_SceneManager;		
			Ogre::RenderWindow*		_RenderWindow;

			GameLevelScene			_GameLevelSceneToLoad;

	};
}
#endif
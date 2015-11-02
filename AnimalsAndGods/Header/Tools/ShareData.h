#ifndef __SHAREDDATA_H
#define __SHAREDDATA_H

#include "../Mind/Thought.h"
#include "../Shaders/DeferredShadingManager.h"

namespace ShareData
{
	namespace DefferedShading
	{
		class DefferedShadingSharedData : public Ogre::Singleton<DefferedShadingSharedData> 
		{

			public:

				DefferedShadingSharedData();
				~DefferedShadingSharedData();				
				
				static DefferedShadingSharedData& getSingleton(void);
				static DefferedShadingSharedData* getSingletonPtr(void);

				// Shared data Deffered Shading across the application
				Ogre::Real iLastFrameTime;
				Ogre::Root *iRoot;
				Ogre::Camera *iCamera;
				Ogre::RenderWindow *iWindow;

				Shaders::DeferredShadingManager* iDeferredShadingManager;
				
				bool iActivate;
				bool iGlobalActivate;
			
				Ogre::Light*	iMainLight;

				//Ogre::vector<Ogre::Node*>::type mLightNodes;

		};
	}
	
	namespace GameConfigurations
	{
		namespace Verions
		{
			static const Ogre::String GAME_VERION = "0.0.1";
		};

		namespace LoadersConfigurations
		{
			enum GameObjectNodeType
			{
				GON_WORLD = 0,				
				GON_LIGHTER = 1,
				GON_STREETLIGHT = 2,
				GON_PU = 3,
				GON_SEWER = 4,
				GON_FLOORSIGN = 5,
				GON_ADDON_ONE = 6,
				GON_ADDON_TWO = 7,
				GON_ADDON_THREE = 8,
				GON_HYDRANT = 9,
				GON_WAYPOINT = 10,
				GON_TRAIN = 11,
				GON_SPACESHIP = 12
			};	

			enum GameObjectCharacterType
			{
				GOCH_PLAYER = 100,
				GOCH_POLICE = 101
			};

			enum GameObjectLightType
			{
				GOL_AMBIENT = 0,
				GOL_STREETLIGHT = 1,
				GOL_FARAMBIENT = 2,
				GOL_TRAIN = 3
			};

			enum GameObjectEntityType
			{
				GOE_WORLD = 0,
				GOE_WORLDSTATIC = 1,
				GOE_WORLDMOVABLE = 2
			};

			enum WayPointType
			{
				WP_TRAIN = 0,
				WP_CAMERA = 1,
				WP_DROID = 2
			};

			struct sPageData
			{
				Ogre::uint					mPageNumber;
				std::vector<Ogre::String>	mLines;
			};

			struct sMenuData
			{
				boost::unordered_map<Ogre::String, std::vector<sPageData>> mStory;
			};			
		}

		namespace PhysicsConfigurations
		{
			enum PhysicsShapeGroups
			{
				NonCollidable = 0,      // Things that the character controller can go through such as Ghosts or tiny			
				Walls = 1,              // Walls, Floors and other static geometry that can't be moved.
				Objects = 2,            // Boxes, Barrels and other dynamic parts of the scene that can be moved by pushing.
			};

			enum GameObjectEntityPhysicsType
			{
				GOEPT_NONE = 0,
				GOEPT_SCENEGEOMETRY = 1,
				GOEPT_BODY = 2,
				GOEPT_CHARACTER = 3
			};
		}

		namespace PlayerConfigurations
		{
			class GameConfigurationsSharedData : public Ogre::Singleton<GameConfigurationsSharedData> 
			{
				public:

					GameConfigurationsSharedData();
					~GameConfigurationsSharedData();				
				
					static GameConfigurationsSharedData& getSingleton(void);
					static GameConfigurationsSharedData* getSingletonPtr(void);

					void loadPlayerConfiguration();

					// Shared data Deffered Shading across the application
					Ogre::Real iEntityPlayerWalkSpeed;
					Ogre::Real iEntityPlayerGlobalInitPositionX;
					Ogre::Real iEntityPlayerGlobalInitPositionY;
					Ogre::Real iEntityPlayerGlobalInitPositionZ;
					Ogre::String iEntityPlayerArmsMesh;
					Ogre::String iEntityPlayerMachineGunMesh;
			};
		}

		namespace CameraConfigurations
		{
			enum CustomCameraType
			{
				STATIC	 = 0,
				FREE	 = 1,				
				FPS		 = 2
			};
		}

		namespace UIConfigurations
		{
			static const Ogre::Real NativeWResolition = 1920;
			static const Ogre::Real NativeHResolition = 1080;
			static const Ogre::Real DefaultTimeBetweenThougts = 20;

			//##MousePointer
			static const Ogre::Vector2 Mouse_Size(36,36);

			//##ButtonExit
			static const Ogre::Vector2 Btn_ExitPositon(914,675);
			static const Ogre::Vector2 Btn_ExitSize(219,79);

			//##ButtonPlay
			static const Ogre::Vector2 Btn_PlayPositon(893,262);
			static const Ogre::Vector2 Btn_PlaySize(250,84);

			//##ButtonStory
			static const Ogre::Vector2 Btn_StoryPositon(881,432);
			static const Ogre::Vector2 Btn_StorySize(289,79);

			//##ButtonCredits
			static const Ogre::Vector2 Btn_CreditsPositon(876,589);
			static const Ogre::Vector2 Btn_CreditsSize(289,84);

			//##ButtonOptions
			static const Ogre::Vector2 Btn_OptionsPositon(862,337);
			static const Ogre::Vector2 Btn_OptionsSize(344,84);

			//##ButtonHelp
			static const Ogre::Vector2 Btn_HelpPositon(900,508);
			static const Ogre::Vector2 Btn_HelpsSize(254,79);
			
			//##ButtonBack			
			static const Ogre::Vector2 Btn_BackSize(254,89);

			//##ButtonLeft
			static const Ogre::Vector2 Btn_LeftSize(69,69);

			//##ButtonRight
			static const Ogre::Vector2 Btn_RightSize(69,69);

			//##ButtonPauseStateResume
			static const Ogre::Vector2 Btn_PauseStateResumePosition(734,313);
			static const Ogre::Vector2 Btn_PauseStateResumeSize(399,89);

			//##ButtonPauseStateRestart
			static const Ogre::Vector2 Btn_PauseStateRestartPosition(769,416);
			static const Ogre::Vector2 Btn_PauseStateRestartSize(329,89);

			//##ButtonPauseStateMainMenu
			static const Ogre::Vector2 Btn_PauseStateMainMenuPosition(682,519);
			static const Ogre::Vector2 Btn_PauseStateMainMenuSize(559,78);
		}

		namespace GOConfigurations
		{
			struct sWayPointsRoute
			{
				ShareData::GameConfigurations::LoadersConfigurations::WayPointType mWayPointType;
				Ogre::String													   mWayPointsName;
				Ogre::SceneNode*												   mWayPointsSceneNodeParent;
				std::vector<Ogre::SceneNode*>									   mWayPointsVector;
				std::vector<Ogre::SceneNode*>									   mWayPointsVectorDebug;
				std::vector<Ogre::SceneNode*>									   mWayPointsVectorLinesDebug;
			};

			struct sAnimationsData
			{
				boost::unordered_map<Ogre::String, Ogre::AnimationState*> mAnimationStates;
			};

			struct sMindData
			{
				boost::unordered_map<Ogre::String, std::vector<Thought*>> mMind;
			};
		}
	}	

}
#endif

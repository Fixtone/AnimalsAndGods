#ifndef GameObjectNodeLighter_H	
#define GameObjectNodeLighter_H

class GameObjectNodeLighter : public GameObjectNode
							, public IClever
{
	public:		
				
		enum GONLighterStates
		{
			On   = 0,			
			Off  = 1
		};

		GameObjectNodeLighter(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
							  Ogre::String aLPanelInfoName, Ogre::String aLCarLighterName, Ogre::String aLPedrastianLighterName, 
							  GONLighterStates aGONLighterState);

		virtual ~GameObjectNodeLighter();
 
		void configure();
		void release();
		bool frameStarted(const Ogre::Real aElapsedTime){return true;}
		bool frameEnded(const Ogre::Real aElapsedTime){return true;}		
		bool update(const Ogre::Real aElapsedTime);
		void updateLogic(lua_State *L, const float elapsedSeconds);

		static GameObjectNodeLighter::GONLighterStates StringToGONLighterStates(Ogre::String aString);		

	private:

		static const char*		GON_LIGHTER_CULLINGFUNCTION;
		static const Ogre::Real MIN_TIME_PEDRASTIANS;
		static const Ogre::Real MAX_TIME_PEDRASTIANS;
		static const Ogre::Real MIN_TIME_REDLIGHTER;
		static const Ogre::Real MAX_TIME_REDLIGHTER;
		static const Ogre::Real MIN_TIME_GREENLIGHTER;
		static const Ogre::Real MAX_TIME_GREENLIGHTER;
		static const Ogre::Real TIME_YELLOWLIGHTER;

		enum GONLighterPedrastianStates
		{
			PedrastianWalk  = 0,			
			PedrastianStop  = 1
		};

		enum GONLighterCarStates
		{
			CarRun  = 0,			
			CarWarning = 1,
			CarStop  = 2
		};

		GONLighterStates				mGONLighterState;		
						
		GameObjectEntity*				mLPedrastianLighterGOE;		
		Ogre::MaterialPtr				mGONLighterPedrastiansMaterialPtr;
		Ogre::MaterialPtr				mGONNewPedrastiansMaterialPtr;
		Ogre::String					mLPedrastianLighterName;		
		Ogre::Real						mAcumTimePedrastians;	
		Ogre::Real						mSwitchTimePedrastians;
		GONLighterPedrastianStates		mCurrentPedrastiansState;

		Ogre::String					mLPanelInfoName;
		GameObjectEntity*				mLPanelInfoGOE;		
		Ogre::MaterialPtr				mGONLighterInfoMaterialPtr;
		Ogre::MaterialPtr				mGONNewInfoMaterialPtr;

		Ogre::String					mLCarLighterName;
		GameObjectEntity*				mLCarLighterGOE;		
		Ogre::MaterialPtr				mGONRedLighterCarMaterialPtr;
		Ogre::MaterialPtr				mGONYellowLighterCarMaterialPtr;
		Ogre::MaterialPtr				mGONGreenLighterCarMaterialPtr;
		Ogre::MaterialPtr				mGONNewRedMaterialPtr;
		Ogre::MaterialPtr				mGONNewYellowMaterialPtr;
		Ogre::MaterialPtr				mGONNewGreenbMaterialPtr;
		Ogre::Real						mAcumTimeCars;
		Ogre::Real						mSwitchTimeCars;
		GONLighterCarStates				mCurrentCarsState;		


		void _CreateMaterial(Ogre::String aNewMaterialnName, Ogre::MaterialPtr aCopyMaterial, Ogre::MaterialPtr aNewMaterial, Ogre::Entity* aEntity);
		void _SetGlowOff(Ogre::MaterialPtr aMaterialPtr, Ogre::String aTechniqueName);
		void _SetGlowOn(Ogre::MaterialPtr aMaterialPtr, Ogre::String aTechniqueName);
		
 };
#endif

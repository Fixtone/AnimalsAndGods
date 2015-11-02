#ifndef GameObjectNodeFloorSign_H
#define GameObjectNodeFloorSign_H

class GameObjectNodeFloorSign : public GameObjectNode
							  , public IClever
{
	public:		
				
		enum GONFloorSignStates
		{
			On   = 0,			
			Off  = 1
		};

		GameObjectNodeFloorSign(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
							    Ogre::String aFloorSignEntityName, Ogre::String aFloorSignBackEntityName, Ogre::String aFloorSignFrontEntityName, 
							    GONFloorSignStates aGONFloorSignState);

		virtual ~GameObjectNodeFloorSign();
 
		void configure();
		void release();
		bool frameStarted(const Ogre::Real aElapsedTime){return true;}
		bool frameEnded(const Ogre::Real aElapsedTime){return true;}		
		bool update(const Ogre::Real aElapsedTime);
		void updateLogic(lua_State *L, const float elapsedSeconds);

		static GameObjectNodeFloorSign::GONFloorSignStates StringToGONFloorSignState(Ogre::String aString);		

	private:

		static const char* GON_FLOORSIGN_CULLINGFUNCTION;
		static const Ogre::Real MIN_TIME_FLOORSIGNFRONT;
		static const Ogre::Real MAX_TIME_FLOORSIGNFRONT;
		static const Ogre::Real MIN_TIME_FLOORSIGNBACK;
		static const Ogre::Real MAX_TIME_FLOORSIGNBACK;				

		GONFloorSignStates				mGONFloorSignState;						
		Ogre::String					mFloorSignEntityName;		
		Ogre::String					mFloorSignBackEntityName;		
		Ogre::String					mFloorSignFrontEntityName;		
		GameObjectEntity*				mFloorSignEntity;	
		GameObjectEntity*				mFloorSignBackEntity;		
		GameObjectEntity*				mFloorSignFrontEntity;
		Ogre::MaterialPtr				mFloorSignMaterialPtr;
		Ogre::MaterialPtr				mFloorSignBackMaterialPtr;
		Ogre::MaterialPtr				mFloorSignFrontMaterialPtr;	
		Ogre::MaterialPtr				mNewFloorSignMaterialPtr;
		Ogre::MaterialPtr				mNewFloorSignBackMaterialPtr;
		Ogre::MaterialPtr				mNewFloorSignFrontMaterialPtr;	
		Ogre::Real						mAcumTimeFloorSignBack;	
		Ogre::Real						mSwitchTimeFloorSignBack;	
		Ogre::Real						mAcumTimeFloorSignFront;	
		Ogre::Real						mSwitchTimeFloorSignFront;	

		std::vector<Ogre::TexturePtr>	mPosters;
		
		void _SetGlowOff(Ogre::MaterialPtr aMaterialPtr, Ogre::String aTechniqueName);
		void _SetGlowOn(Ogre::MaterialPtr aMaterialPtr, Ogre::String aTechniqueName);
		
 };
#endif

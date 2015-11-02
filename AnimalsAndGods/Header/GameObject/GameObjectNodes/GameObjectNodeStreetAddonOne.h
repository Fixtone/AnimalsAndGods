#ifndef GameObjectNodeStreetAddonOne_H
#define GameObjectNodeStreetAddonOne_H

class GameObjectNodeStreetAddonOne : public GameObjectNode
								   , public IClever
{
	public:				
		
		enum GONStreetAddonOneStates
		{
			On   = 0,			
			Off  = 1
		};

		GameObjectNodeStreetAddonOne(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aStreetAddonOneEntityName, 
									 GONStreetAddonOneStates aGONStreetAddonOneState);

		virtual ~GameObjectNodeStreetAddonOne();
 
		void configure();
		void release();
		bool frameStarted(const Ogre::Real aElapsedTime){return true;}
		bool frameEnded(const Ogre::Real aElapsedTime){return true;}		
		bool update(const Ogre::Real aElapsedTime){return true;}
		void updateLogic(lua_State *L, const float elapsedSeconds);

		static GameObjectNodeStreetAddonOne::GONStreetAddonOneStates StringToGONStreetAddonOneState(Ogre::String aString);

	private:		

		static const char*				GON_STREETADDONOne_CULLINGFUNCTION;

		GONStreetAddonOneStates			mGONStreetAddonOneState;			
		Ogre::String					mStreetAddonOneEntityName;				
		GameObjectEntity*				mStreetAddonOneEntity;				
 };
#endif

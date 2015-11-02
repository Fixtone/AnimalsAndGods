#ifndef GameObjectNodeStreetAddonTwo_H
#define GameObjectNodeStreetAddonTwo_H

class GameObjectNodeStreetAddonTwo : public GameObjectNode
								   , public IClever
{
	public:				
		
		enum GONStreetAddonTwoStates
		{
			On   = 0,			
			Off  = 1,
			FlipFlap = 2
		};

		GameObjectNodeStreetAddonTwo(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aStreetAddonTwoEntityName, 
									 GONStreetAddonTwoStates aGONStreetAddonTwoState);

		virtual ~GameObjectNodeStreetAddonTwo();
 
		void configure();
		void release();
		bool frameStarted(const Ogre::Real aElapsedTime){return true;}
		bool frameEnded(const Ogre::Real aElapsedTime){return true;}		
		bool update(const Ogre::Real aElapsedTime){return true;}
		void updateLogic(lua_State *L, const float elapsedSeconds);

		static GameObjectNodeStreetAddonTwo::GONStreetAddonTwoStates StringToGONStreetAddonTwoState(Ogre::String aString);

	private:		

		static const char*				GON_STREETADDONTWO_CULLINGFUNCTION;

		GONStreetAddonTwoStates			mGONStreetAddonTwoState;			
		Ogre::String					mStreetAddonTwoEntityName;				
		GameObjectEntity*				mStreetAddonTwoEntity;		

 };
#endif

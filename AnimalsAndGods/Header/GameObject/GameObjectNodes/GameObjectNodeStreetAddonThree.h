#ifndef GameObjectNodeStreetAddonThree_H
#define GameObjectNodeStreetAddonThree_H

class GameObjectNodeStreetAddonThree : public GameObjectNode
									 , public IClever
{
	public:				
		
		enum GONStreetAddonThreeStates
		{
			On   = 0,			
			Off  = 1
		};

		GameObjectNodeStreetAddonThree(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aStreetAddonThreeEntityName, 
									   GONStreetAddonThreeStates aGONStreetAddonThreeState);

		virtual ~GameObjectNodeStreetAddonThree();
 
		void configure();
		void release();
		bool frameStarted(const Ogre::Real aElapsedTime){return true;}
		bool frameEnded(const Ogre::Real aElapsedTime){return true;}		
		bool update(const Ogre::Real aElapsedTime){return true;}
		void updateLogic(lua_State *L, const float elapsedSeconds);

		static GameObjectNodeStreetAddonThree::GONStreetAddonThreeStates StringToGONStreetAddonThreeState(Ogre::String aString);

	private:		

		static const char*				GON_STREETADDONTHREE_CULLINGFUNCTION;

		GONStreetAddonThreeStates		mGONStreetAddonThreeState;			
		Ogre::String					mStreetAddonThreeEntityName;				
		GameObjectEntity*				mStreetAddonThreeEntity;				
 };
#endif

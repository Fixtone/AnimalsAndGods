#ifndef GameObjectNodeStreetLight_H	
#define GameObjectNodeStreetLight_H

class GameObjectNodeStreetLight : public GameObjectNode
								, public IClever
{
	public:		
				
		enum GONStreetLightStates
		{
			On   = 0,			
			Off  = 1,
			FlipFlap = 2
		};

		GameObjectNodeStreetLight(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
								  Ogre::String aStreetLightEntityName, Ogre::String aLightStreetLightName, 
								  GONStreetLightStates aGONStreetLightState);
 
		void configure();
		void release();
		bool frameStarted(const Ogre::Real aElapsedTime){return true;}
		bool frameEnded(const Ogre::Real aElapsedTime){return true;}
		bool update(const Ogre::Real aElapsedTime);
		void updateLogic(lua_State *L, const float elapsedSeconds);

		static GameObjectNodeStreetLight::GONStreetLightStates StringToGONStreetLightState(Ogre::String aString);		

	private:		

		static const char* GON_STREETLIGHT_CULLINGFUNCTION;

		Ogre::String					mStreetLightEntityName;		
		Ogre::String					mLightStreetLightName;
		GONStreetLightStates			mGONStreetLightState;						
		GameObjectEntity*				mStreetLightEntity;		
		GameObjectLight*				mLightStreetLight;
		Ogre::SceneNode*				mBillboardNode;
		Ogre::BillboardSet*				mBillboardSet;
		
 };
#endif

#ifndef GameObjectSpaceShip_H
#define GameObjectSpaceShip_H

class GameObjectSpaceShip : public GameObjectNode
						  , public IClever 
{
	public:
		
		enum GONSpaceShipStates
		{
			Stop			= 0,
			Rotation		= 1,
			Fly				= 2
		};
				
		struct GameObjectSpaceShipParameters
		{			
			Ogre::Real speed;
			Ogre::Real rotationSpeed;
			Ogre::Real minStopLand;
			Ogre::Real maxStopLand;			
		};			

		GameObjectSpaceShip(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, const Ogre::String &aGOESpaceShipName, const Ogre::String &aSpaceShipNodeTrackAnimationName,
							const Ogre::String &aSpaceShipWayPointsRouteName, Ogre::Real aSpaceShipSpeed, Ogre::Real aSpaceShipLandMinStopTime,
							Ogre::Real aSpaceShipLandMaxStopTime, GONSpaceShipStates aGONSpaceShipState);

		~GameObjectSpaceShip();		
			
		void configure();
		void release();
		bool frameStarted(const Ogre::Real aElapsedTime){return true;}
		bool frameEnded(const Ogre::Real aElapsedTime){return true;}		
		bool update(const Ogre::Real aElapsedTime);
		void updateLogic(lua_State *L, const float elapsedSeconds){};
		
		static GONSpaceShipStates StringToState (Ogre::String string);

	private:					
				
		typedef boost::unordered_map<GONSpaceShipStates, boost::function<void(Ogre::Real)>> SpaceShipStateCallbackFunc;
		SpaceShipStateCallbackFunc _SpaceShipStateCallbackFunc;

		void _NextLocation();

		void stateStop(Ogre::Real aElapsedTime);
		void stateRotation(Ogre::Real aElapsedTime);
		void stateFly(Ogre::Real aElapsedTime);

		GONSpaceShipStates													_GONSpaceShipState;	
		Ogre::Quaternion													_CurrentQuaternion;
		Ogre::Quaternion													_NextQuaternion;
		Ogre::Real															_RotationSlerpProgress;
		Ogre::Vector3														_NextDistinationPosition;
		Ogre::Vector3														_Direction;
		Ogre::Real															_Distance;

		Ogre::String														_SpaceShipNodeTrackAnimationName;
		Ogre::String														_GOESpaceShipName;
		Ogre::String														_WayPointsRouteName;	
		ShareData::GameConfigurations::GOConfigurations::sWayPointsRoute	_SpaceShipRoute;
		GameObjectSpaceShipParameters										_GONSpaceShipParameters;
		ShareData::GameConfigurations::GOConfigurations::sAnimationsData	_Animations;
				
		unsigned int														_CurrentWaypoint;
		unsigned int														_NextWaypoint;
};

#endif
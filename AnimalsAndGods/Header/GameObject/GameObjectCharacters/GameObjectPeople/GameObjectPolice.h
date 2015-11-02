#ifndef GameObjectPolice_H
#define GameObjectPolice_H

class GameObjectPolice : public GameObjectCharacter
					   , public IClever
{
	public:		

		enum GOCHPoliceStates
		{
			Crawl = 0,
			Crouch = 1,
			CrouchRifleShoot = 2,
			Death = 3,
			Down = 4,
			LookingAround = 5,
			ShootRifle = 6,
			Sleep = 7,
			Talk = 8,
			WalkAnim = 9,
			WalkRifle = 10,
			WalkRifleShoot = 11,
			Idle = 12,
			IdleRifle = 13			
		};
	
		GameObjectPolice(Ogre::uint32 aGOCHId, Critter::Node* aPlayerNode, Ogre::String aPoliceEntityMeshName,
						 Ogre::String aPoliceTalkCameraNodeName, Critter::RenderSystem* aRendersystem, 
						 const Critter::AnimatedCharacterDescription& desc, const NxOgre::Vec3 &position,
						 Ogre::Radian yaw, GOCHPoliceStates aGOCHPoliceState);
		
		~GameObjectPolice();		

		static GameObjectPolice::GOCHPoliceStates StringToGOCHPoliceState(Ogre::String aString);		
		
		void configure();
		void release();
		bool frameStarted(const Ogre::Real aElapsedTime);
		bool frameEnded(const Ogre::Real aElapsedTime);
		bool update(const Ogre::Real aElapsedTime);
		void updateLogic(lua_State *L, const float elapsedSeconds);

		void advancePhysics(float aElapsedTime, const NxOgre::Enums::Priority&);		
		void advanceAnimation(float aElapsedTime, const NxOgre::Enums::Priority&);

	private:		
		
		static const char* GO_POLICE_CULLINGFUNCTION;

		bool		   _Active;
		bool           mUsesGravity;
		Ogre::Real     mMaxGroundSpeed;
		bool           mHasMovement;		
		NxOgre::Ray    mRay;			
		
		//Move Police
		bool							_GoingForward;
		bool							_GoingBack;
		bool							_GoingLeft;
		bool							_GoingRLeft;
		bool							_GoingRight;
		bool							_GoingRRight;
		bool							_FastMove;
		bool							_GoingUp;		

		Ogre::Camera*					_PoliceTalkCamera;

		//Animations
		typedef boost::unordered_map<GOCHPoliceStates, Ogre::AnimationState*> MapPoliceStateAnimationState;
		MapPoliceStateAnimationState _MapPoliceStateAnimationState;

		typedef boost::unordered_map<GOCHPoliceStates, boost::function<void(Ogre::Real)>> PoliceStateCallbackFunc;
		PoliceStateCallbackFunc _PoliceStateCallbackFunc;

		void stateCrawl(Ogre::Real aElapsedTime);
		void stateCrouch(Ogre::Real aElapsedTime);
		void stateCrouchRifleShoot(Ogre::Real aElapsedTime);
		void stateDeath(Ogre::Real aElapsedTime);
		void stateDown(Ogre::Real aElapsedTime);
		void stateLookingAround(Ogre::Real aElapsedTime);
		void stateShootRifle(Ogre::Real aElapsedTime);
		void stateSleep(Ogre::Real aElapsedTime);
		void stateTalk(Ogre::Real aElapsedTime);
		void stateWalkAnim(Ogre::Real aElapsedTime);
		void stateWalkRifle(Ogre::Real aElapsedTime);
		void stateWalkRifleShoot(Ogre::Real aElapsedTime);
		void stateIdle(Ogre::Real aElapsedTime);
		void stateIdleRifle(Ogre::Real aElapsedTime);		

		Ogre::AnimationState*			_CurrentAnimation;
		GOCHPoliceStates				_CurrentPoliceState;	

		Ogre::Entity*					_GOCHPoliceEntity;

};

#endif GameObjectPolice_H
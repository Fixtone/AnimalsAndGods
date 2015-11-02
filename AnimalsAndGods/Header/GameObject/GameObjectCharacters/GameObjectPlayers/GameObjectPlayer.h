#ifndef GameObjectPlayer_H
#define GameObjectPlayer_H

class GameObjectPlayer : public GameObjectCharacter
					   , public IClever

{
	public:		

		enum PlayerStates
		{
			IDLEBLAST = 0,
			BLASTSHOOT = 1,
			BLASTTOMG = 2,
			CROCHEDBLAST = 3 ,
			CROCHEDMG = 4 ,
			IDLEMG = 5,
			MGTOBLAST = 6,
			RELOADEDBLAST = 7,
			RELOADEDMG = 8,
			RUNBLAST = 9,
			RUNMG = 10,
			SHOOTPRIMARYMG = 11,
			SHOOTSUPPORTMG = 12
		};		

		GameObjectPlayer(Critter::Node* aPlayerNode, Ogre::String aPlayerCameraNodeName, Critter::RenderSystem* aRendersystem, 
						 const Critter::AnimatedCharacterDescription& desc, const NxOgre::Vec3 &position,
						 Ogre::Radian yaw);
			
		~GameObjectPlayer();

		void configure();
		void release();
		bool frameStarted(const Ogre::Real aElapsedTime);
		bool frameEnded(const Ogre::Real aElapsedTime);
		bool update(const Ogre::Real aElapsedTime);
		void updateLogic(lua_State *L, const float elapsedSeconds){};

		void advancePhysics(float aElapsedTime, const NxOgre::Enums::Priority&);	

		bool keyPressed( const OIS::KeyEvent &e );
		bool keyReleased( const OIS::KeyEvent &e );
		bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
		bool mouseMoved( const OIS::MouseEvent &e );

		bool isActive(){return _Active;}
		void setActive(bool aActive){_Active = aActive;}

	private:

		Ogre::Real     mMaxJumpVelocity, mJumpTime, mFallTime;
		NxOgre::Vec3   mAirUserDirection, mJumpVelocity0;
		size_t         mJumpDirectionIndex;
		bool           mIsJumping, mIsFalling;
		size_t         mFallDirectionIndex;
		bool           mUsesGravity;
		Ogre::Real     mMaxGroundSpeed;
		bool           mHasMovement;
		//size_t         mAnimWaitNextAnims[2];
		NxOgre::Ray    mRay;		
	
		//Ogre::Vector3 getPlayerPosition();
	
	private:				
		
		//Move Player
		bool							_GoingForward;
		bool							_GoingBack;
		bool							_GoingLeft;
		bool							_GoingRLeft;
		bool							_GoingRight;
		bool							_GoingRRight;
		bool							_FastMove;
		bool							_GoingUp;
		bool							_HasJumpMovement;
		bool							_Active;
		
		FPSCamera*						_PlayerCamera;

		////Animations
		//typedef boost::unordered_map<PlayerStates, Ogre::AnimationState*> MapPlayerStateAnimationState;
		//MapPlayerStateAnimationState _MapPlayerStateAnimationState;

	 //   void stateIdleMG(Ogre::Real aElapsedTime);
		//void stateIdleBlast(Ogre::Real aElapsedTime);
		//void stateMGToBlast(Ogre::Real aElapsedTime);
		//void stateBlastToMG(Ogre::Real aElapsedTime);
		//void stateRunBlast(Ogre::Real aElapsedTime);
		//void stateRunMG(Ogre::Real aElapsedTime);

		//Ogre::AnimationState*			_CurrentAnimation;
		//PlayerStates					_CurrentPlayerState;	

		////Lantern
		//Ogre::Node*						_LanternNode;
		//Ogre::Light*					_LanternLight;		

};

#endif GameObjectPlayer_H
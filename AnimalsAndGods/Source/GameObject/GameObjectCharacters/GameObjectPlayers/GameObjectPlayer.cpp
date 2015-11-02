#include "stdafx.h"
#include "../../Header/GameObject/GameObjectCharacters/GameObjectPlayers/GameObjectPlayer.h"

GameObjectPlayer::GameObjectPlayer(Critter::Node* aPlayerNode, Ogre::String aPlayerCameraNodeName, Critter::RenderSystem* aRendersystem, 
								   const Critter::AnimatedCharacterDescription& desc, const NxOgre::Vec3 &position,
								   Ogre::Radian yaw)
: GameObjectCharacter(aPlayerNode, aRendersystem)
{	
	mYaw = yaw;
	mShape = desc.mShape;
	mAlternateShape = desc.mAlternateShape;
	mIsUsingAlternateShape = desc.mIsUsingAlternateShape;
 
	NxOgre::CharacterControllerDescription c_desc;
	c_desc.mCallback = this;
	c_desc.mCapsuleEasyClimbing = false;
	c_desc.mStepOffset = desc.mStepOffset;
	c_desc.mSlopeLimit = desc.mSlopeLimit;
	c_desc.mUpDirection = desc.mUpDirection;	
 
	mActiveGroups = desc.mCollisionMask;
	mIsJumping = false;
	mJumpTime = 0;
	mMaxJumpVelocity = desc.mJumpVelocity;
	mJumpVelocity0.zero();
	mJumpDirectionIndex = 0;
	mUsesGravity = true;
	mMaxGroundSpeed = desc.mMaxGroundSpeed;
	mIsFalling = false;
	mFallDirectionIndex = 0;
	mHasMovement = false;
	
	createCharacterController(position, mShape, c_desc);	
	mRay.mDirection.y = -1;	

	Ogre::String nameDebugMesh = "Player_DM#0";
	Procedural::BoxGenerator().setSizeY(3).realizeMesh(nameDebugMesh);
	Ogre::Entity* entity = GameManager::getSingletonPtr()->getSceneManager()->createEntity(nameDebugMesh);
	Ogre::SceneNode* sn = mNode->getSceneNode()->createChildSceneNode();
	sn->attachObject(entity);
	sn->setPosition(Ogre::Vector3::ZERO);
	entity->setMaterialName("WaypointSphereDebug");
	entity->setCastShadows(false);			
	sn->setVisible(true);

	Cameras::CameraManager::getSingletonPtr()->createCamera(ShareData::GameConfigurations::CameraConfigurations::FPS, "PlayerCameraFPS",
															GameManager::getSingletonPtr()->getSceneManager()->getSceneNode("PlayerCameraNode#0"), Ogre::Vector3::ZERO, 
															Ogre::Quaternion::IDENTITY*Ogre::Vector3::UNIT_Z);

	Cameras::CameraManager::getSingletonPtr()->setActiveCamera("PlayerCameraFPS");
	_PlayerCamera = static_cast<FPSCamera*>(Cameras::CameraManager::getSingletonPtr()->getCameraByName("PlayerCameraFPS"));
	_Active = false;

}

GameObjectPlayer::~GameObjectPlayer()
{		
}

void GameObjectPlayer::configure()
{
	_GoingForward = _GoingBack = _GoingLeft = _GoingRLeft = _GoingRight = _GoingRRight = _FastMove = _GoingUp = false;
	_HasJumpMovement = false;	

	//	///############LANTERN		
	//	_LanternLight = mSceneManager->createLight("spotLight");
	//	_LanternLight->setType(Ogre::Light::LT_SPOTLIGHT);
	//	_LanternLight->setDiffuseColour(1.0f, 1.0f, 1.0f);
	//	_LanternLight->setSpecularColour(1.0f, 1.0f, 1.0f); 
	//	_LanternLight->setDirection(1, 0, 0);
	//	_LanternLight->setPosition(Ogre::Vector3(0, 0, 0)); 
	//	_LanternLight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
	//	_LanternLight->setAttenuation(65, 1.0f, 0.07f, 0.017f);
	//	_LanternLight->setCastShadows(false);
	//	_LanternLight->setVisible(false);	//Off by default	
	//	mSceneManager->getSceneNode("PlayerCameraFPSSceneNode#0")->attachObject(_LanternLight);
	//	///############LANTERN
		
}

void GameObjectPlayer::release()
{	
}

bool GameObjectPlayer::frameStarted(const Ogre::Real aElapsedTime)
{
	return true;
}

bool GameObjectPlayer::frameEnded(const Ogre::Real aElapsedTime)
{
	return true;
}		

void GameObjectPlayer::advancePhysics(float aElapsedTime, const NxOgre::Enums::Priority&)
{
	if(isActive())
	{
		GameObjectCharacter::advancePhysics(aElapsedTime, NxOgre::Enums::Priority_Medium);

		NxOgre::Vec3 displacement;
	
		if (mUsesGravity)
			displacement += mScene->getGravity();	

		if (mHasMovement == false)
		{
		}
		else
		{
			static  Ogre::Vector3 userDirection;
			userDirection = Ogre::Vector3::ZERO;		
		
			if(_GoingForward)
				userDirection.z = -float(Ogre::Math::Clamp<float>(0.1f, 0, 0.1f)) * mMaxGroundSpeed;    
			if(_GoingBack)
				userDirection.z = float(Ogre::Math::Clamp<float>(0.1f, 0, 0.1f)) * mMaxGroundSpeed; 
			if(_GoingRight)
				userDirection.x = -float(Ogre::Math::Clamp<float>(0.1f, 0, 0.1f)) * mMaxGroundSpeed;    
			if(_GoingLeft)
				userDirection.x = float(Ogre::Math::Clamp<float>(0.1f, 0, 0.1f)) * mMaxGroundSpeed;  
			if(_GoingRLeft)
			{
				// y += v * 0.013 * dt
				mYaw += Ogre::Radian(float(Ogre::Math::Clamp<float>(0.1f, 0, 0.1f)) * 10 * aElapsedTime); // temp.
				userDirection.x = 0;
			}
			if(_GoingRRight)
			{
				// y += v * 0.013 * dt
				mYaw += Ogre::Radian(-float(Ogre::Math::Clamp<float>(0.1f, 0, 0.1f)) * 10 * aElapsedTime); // temp.
				userDirection.x = 0;
			}		
		
			userDirection = Ogre::Quaternion(mYaw, Ogre::Vector3::UNIT_Y) * userDirection;  		

			displacement.x += userDirection.x;
			displacement.z += userDirection.z;
		}

		move(displacement * aElapsedTime);	
	}
}

bool GameObjectPlayer::update(const Ogre::Real aElapsedTime)
{		
	return true;
}	

bool GameObjectPlayer::keyPressed( const OIS::KeyEvent &e )
{	
	if(isActive())
	{
		mHasMovement = true;

		if(e.key == OIS::KC_A)	
			_GoingLeft = true;
	
		if(e.key == OIS::KC_D)	
			_GoingRight = true;

		if(e.key == OIS::KC_S)	
			_GoingForward = true;

		if(e.key == OIS::KC_W)	
			_GoingBack = true;

		if(e.key == OIS::KC_Q)	
			_GoingRLeft = true;

		if(e.key == OIS::KC_E)	
			_GoingRRight = true;

		if(e.key == OIS::KC_LSHIFT)
			mMaxGroundSpeed *=2;
	}

	return true;
}

bool GameObjectPlayer::keyReleased( const OIS::KeyEvent &e )
{	
	if(isActive())
	{
		if(e.key == OIS::KC_A)	
			_GoingLeft = false;
	
		if(e.key == OIS::KC_D)	
			_GoingRight = false;

		if(e.key == OIS::KC_S)	
			_GoingForward = false;

		if(e.key == OIS::KC_W)	
			_GoingBack = false;

		if(e.key == OIS::KC_Q)	
			_GoingRLeft = false;

		if(e.key == OIS::KC_E)	
			_GoingRRight = false;

		if(e.key == OIS::KC_LSHIFT)
			mMaxGroundSpeed /=2;

		if(!_GoingBack && !_GoingForward && !_GoingLeft && !_GoingRight && !_GoingRLeft && !_GoingRRight)
			mHasMovement = false;
		else
			mHasMovement = true;
	}

	return true;
}

bool GameObjectPlayer::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{	
	return true;
}

bool GameObjectPlayer::mouseMoved( const OIS::MouseEvent &e )
{
	if(isActive())	
		mYaw += Ogre::Degree(-e.state.X.rel * 0.16f);	
	
	return true;
}
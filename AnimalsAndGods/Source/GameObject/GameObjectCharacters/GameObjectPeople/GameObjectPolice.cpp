#include "stdafx.h"
#include "../../Header/GameObject/GameObjectCharacters/GameObjectPeople/GameObjectPolice.h"

const char*	GameObjectPolice::GO_POLICE_CULLINGFUNCTION = "GO_PoliceCulling";
GameObjectPolice::GOCHPoliceStates GameObjectPolice::StringToGOCHPoliceState(Ogre::String aString)
{
	const char* str = aString.c_str();

	if(strcmp ( "Crawl", str ) == 0)					return GameObjectPolice::Crawl;	
	if(strcmp ( "Crouch", str ) == 0)					return GameObjectPolice::Crouch;	
	if(strcmp ( "CrouchRifleShoot", str ) == 0)			return GameObjectPolice::CrouchRifleShoot;	
	if(strcmp ( "Death", str ) == 0)					return GameObjectPolice::Death;	
	if(strcmp ( "Down", str ) == 0)						return GameObjectPolice::Down;	
	if(strcmp ( "LookingAround", str ) == 0)			return GameObjectPolice::LookingAround;	
	if(strcmp ( "ShootRifle", str ) == 0)				return GameObjectPolice::ShootRifle;	
	if(strcmp ( "Sleep", str ) == 0)					return GameObjectPolice::Sleep;	
	if(strcmp ( "Talk", str ) == 0)						return GameObjectPolice::Talk;	
	if(strcmp ( "WalkAnim", str ) == 0)					return GameObjectPolice::WalkAnim;	
	if(strcmp ( "WalkRifle", str ) == 0)				return GameObjectPolice::WalkRifle;	
	if(strcmp ( "WalkRifleShoot", str ) == 0)			return GameObjectPolice::WalkRifleShoot;	
	if(strcmp ( "Idle", str ) == 0)						return GameObjectPolice::Idle;	
	else												return GameObjectPolice::IdleRifle;	
}


GameObjectPolice::GameObjectPolice(Ogre::uint32 aGOCHId, Critter::Node* aPlayerNode, Ogre::String aPoliceEntityMeshName,
								   Ogre::String aPoliceTalkCameraNodeName, Critter::RenderSystem* aRendersystem, 
								   const Critter::AnimatedCharacterDescription& desc, const NxOgre::Vec3 &position,
						           Ogre::Radian yaw, GOCHPoliceStates aGOCHPoliceState)
: GameObjectCharacter(aGOCHId, aPlayerNode, aRendersystem)
, _CurrentPoliceState(aGOCHPoliceState)
, _Active(true)
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
	mUsesGravity = true;
	mMaxGroundSpeed = desc.mMaxGroundSpeed;
	mHasMovement = false;

	createCharacterController(position, mShape, c_desc);	
	mRay.mDirection.y = -1;	
			
	/*
	Ogre::String nameDebugMesh = "Player_DM#0";
	Procedural::BoxGenerator().setSizeY(3).realizeMesh(nameDebugMesh);
	Ogre::Entity* entity = GameManager::getSingletonPtr()->getSceneManager()->createEntity(nameDebugMesh);
	Ogre::SceneNode* sn = mNode->getSceneNode()->createChildSceneNode();
	sn->attachObject(entity);
	sn->setPosition(Ogre::Vector3::ZERO);
	entity->setMaterialName("WaypointSphereDebug");
	entity->setCastShadows(false);			
	sn->setVisible(true);
	*/
	
	/*
	Cameras::CameraManager::getSingletonPtr()->createCamera(ShareData::GameConfigurations::CameraConfigurations::FPS, "PlayerCameraFPS",
															GameManager::getSingletonPtr()->getSceneManager()->getSceneNode("PlayerCameraNode#0"), Ogre::Vector3::ZERO, 
															Ogre::Quaternion::IDENTITY*Ogre::Vector3::UNIT_Z);
	*/

	//_PlayerCamera = static_cast<FPSCamera*>(Cameras::CameraManager::getSingletonPtr()->getCameraByName("PlayerCameraFPS"));
	//_Active = false;	
	GameObjectEntity* gOE = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(aPoliceEntityMeshName,ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLD);
	_GOCHPoliceEntity = gOE->mGOEEntity;
	Ogre::Real entityYSize = _GOCHPoliceEntity->getBoundingBox().getSize().y;
	Ogre::Vector3 currentPos = mNode->getSceneNode()->getChild(aPoliceEntityMeshName)->getPosition();	
	mNode->getSceneNode()->getChild(aPoliceEntityMeshName)->setPosition(currentPos.x,currentPos.y-((entityYSize*gOE->mGOESceneNode->getScale().y)/2),currentPos.z);

	_MapPoliceStateAnimationState[Crawl] = _GOCHPoliceEntity->getAnimationState("Crawl");
	_MapPoliceStateAnimationState[Crouch] = _GOCHPoliceEntity->getAnimationState("Crouch");
	_MapPoliceStateAnimationState[CrouchRifleShoot] = _GOCHPoliceEntity->getAnimationState("CrouchRifleShoot");
	_MapPoliceStateAnimationState[Death] = _GOCHPoliceEntity->getAnimationState("Death");	
	_MapPoliceStateAnimationState[Down] = _GOCHPoliceEntity->getAnimationState("Down");
	_MapPoliceStateAnimationState[LookingAround] = _GOCHPoliceEntity->getAnimationState("LookingAround");
	_MapPoliceStateAnimationState[ShootRifle] = _GOCHPoliceEntity->getAnimationState("ShootRifle");
	_MapPoliceStateAnimationState[Sleep] = _GOCHPoliceEntity->getAnimationState("Sleep");	
	_MapPoliceStateAnimationState[Talk] = _GOCHPoliceEntity->getAnimationState("Talk");
	_MapPoliceStateAnimationState[WalkAnim] = _GOCHPoliceEntity->getAnimationState("WalkAnim");
	_MapPoliceStateAnimationState[WalkRifle] = _GOCHPoliceEntity->getAnimationState("WalkRifle");
	_MapPoliceStateAnimationState[WalkRifleShoot] = _GOCHPoliceEntity->getAnimationState("WalkRifleShoot");	
	_MapPoliceStateAnimationState[Idle] = _GOCHPoliceEntity->getAnimationState("Idle");
	_MapPoliceStateAnimationState[IdleRifle] = _GOCHPoliceEntity->getAnimationState("IdleRifle");

	_CurrentAnimation = _MapPoliceStateAnimationState[_CurrentPoliceState];
	_CurrentAnimation->setEnabled(true);
	_CurrentAnimation->setLoop(true);
		
	_PoliceStateCallbackFunc[Crawl] = boost::bind(&GameObjectPolice::stateCrawl, this, _1);
	_PoliceStateCallbackFunc[Crouch] = boost::bind(&GameObjectPolice::stateCrouch, this, _1);
	_PoliceStateCallbackFunc[CrouchRifleShoot] = boost::bind(&GameObjectPolice::stateCrouchRifleShoot, this, _1);
	_PoliceStateCallbackFunc[Death] = boost::bind(&GameObjectPolice::stateDeath, this, _1);
	_PoliceStateCallbackFunc[Down] = boost::bind(&GameObjectPolice::stateDown, this, _1);
	_PoliceStateCallbackFunc[LookingAround] = boost::bind(&GameObjectPolice::stateLookingAround, this, _1);
	_PoliceStateCallbackFunc[ShootRifle] = boost::bind(&GameObjectPolice::stateShootRifle, this, _1);
	_PoliceStateCallbackFunc[Sleep] = boost::bind(&GameObjectPolice::stateSleep, this, _1);
	_PoliceStateCallbackFunc[Talk] = boost::bind(&GameObjectPolice::stateTalk, this, _1);
	_PoliceStateCallbackFunc[WalkAnim] = boost::bind(&GameObjectPolice::stateWalkAnim, this, _1);
	_PoliceStateCallbackFunc[WalkRifle] = boost::bind(&GameObjectPolice::stateWalkRifle, this, _1);
	_PoliceStateCallbackFunc[WalkRifleShoot] = boost::bind(&GameObjectPolice::stateWalkRifleShoot, this, _1);	
	_PoliceStateCallbackFunc[Idle] = boost::bind(&GameObjectPolice::stateIdle, this, _1);
	_PoliceStateCallbackFunc[IdleRifle] = boost::bind(&GameObjectPolice::stateIdleRifle, this, _1);

}

GameObjectPolice::~GameObjectPolice()
{		
}

void GameObjectPolice::configure()
{
	_GoingForward = _GoingBack = _GoingLeft = _GoingRLeft = _GoingRight = _GoingRRight = _FastMove = _GoingUp = false;	

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

void GameObjectPolice::release()
{	
}

bool GameObjectPolice::frameStarted(const Ogre::Real aElapsedTime)
{
	return true;
}

bool GameObjectPolice::frameEnded(const Ogre::Real aElapsedTime)
{
	return true;
}		

void GameObjectPolice::advancePhysics(float aElapsedTime, const NxOgre::Enums::Priority&)
{	
	if(_Active)
		GameObjectCharacter::advancePhysics(aElapsedTime, NxOgre::Enums::Priority_Medium);	
}

void GameObjectPolice::advanceAnimation(float aElapsedTime, const NxOgre::Enums::Priority&)
{
	if(_Active)
	{
		GameObjectCharacter::advanceAnimation(aElapsedTime, NxOgre::Enums::Priority_Medium);
		_CurrentAnimation->addTime(aElapsedTime);
	}
}

bool GameObjectPolice::update(const Ogre::Real aElapsedTime)
{		
	return true;
}

void GameObjectPolice::updateLogic(lua_State *L, const float elapsedSeconds)
{
	// the function name
	lua_getglobal(L, GO_POLICE_CULLINGFUNCTION);
	
	// push arguments
	lua_pushnumber(L, mGOCHId);	

	// call the function with 1 argument, return 1 result
	lua_call(L, 1, 1);

	// get the result 
	bool newActive = (bool)luaL_checkint(L, -1);
	lua_pop(L, 1);

	// state is the new state for the player
	// Do something if and only if the state has changed!
	if(newActive != _Active)
	{
		_Active = newActive;		
		mNode->getSceneNode()->setVisible(_Active);		
	}

}

void GameObjectPolice::stateCrawl(Ogre::Real aElapsedTime)
{
}

void GameObjectPolice::stateCrouch(Ogre::Real aElapsedTime)
{
}

void GameObjectPolice::stateCrouchRifleShoot(Ogre::Real aElapsedTime)
{
}

void GameObjectPolice::stateDeath(Ogre::Real aElapsedTime)
{
}

void GameObjectPolice::stateDown(Ogre::Real aElapsedTime)
{
}

void GameObjectPolice::stateLookingAround(Ogre::Real aElapsedTime)
{
}

void GameObjectPolice::stateShootRifle(Ogre::Real aElapsedTime)
{
}

void GameObjectPolice::stateSleep(Ogre::Real aElapsedTime)
{
}

void GameObjectPolice::stateTalk(Ogre::Real aElapsedTime)
{
}

void GameObjectPolice::stateWalkAnim(Ogre::Real aElapsedTime)
{
}

void GameObjectPolice::stateWalkRifle(Ogre::Real aElapsedTime)
{
}

void GameObjectPolice::stateWalkRifleShoot(Ogre::Real aElapsedTime)
{
}

void GameObjectPolice::stateIdle(Ogre::Real aElapsedTime)
{
}
	
void GameObjectPolice::stateIdleRifle(Ogre::Real aElapsedTime)
{
}


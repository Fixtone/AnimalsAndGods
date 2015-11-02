#include "stdafx.h"
//#include "../../Header/GameObject/GameObjectTypes/GameObjectEnemy.h"
//
//GameObjectEnemy::GameObjectEnemy(const NxOgre::SimpleCapsule &aShape, const unsigned int &aCollisionMask, const Ogre::Real &aMaxGroundSpeed, Ogre::SceneManager* &aSceneManager, 
//								 Ogre::SceneNode* &aCharacterNode, const Ogre::String &aEnemyMeshName)								   
//: GameObjectSCharacter(aSceneManager, aCharacterNode)
//{	
//	_GoingBack = _GoingForward = _GoingRight = _GoingLeft = _GoingUp = _GoingRRight = _GoingRLeft = false;
//
//	/*mRenderSystem = PhysicsManager::getSingletonPtr()->getPhysicsRenderSystem();
//			
//	Critter::AnimatedCharacterDescription desc;
//	desc.mShape = aShape;
//	desc.mCollisionMask = aCollisionMask;
//	desc.mMaxGroundSpeed = aMaxGroundSpeed;*/
//
//	mCharacterEntity = mSceneManager->getEntity(aEnemyMeshName);		
//	mCharacterEntity->setCastShadows(true);
//
//	/*Ogre::Vector3 enemyGlobalPosition(aCharacterNode->getPosition());
//	aCharacterNode->setPosition(0,-1.5f,0);
//	aCharacterNode->setOrientation(Ogre::Quaternion::IDENTITY);
//		
//	mCharacterCritterNode = new Critter::Node(mSceneManager, aCharacterNode, mRenderSystem);
//	mCharacterCritterNode->addEntity(mCharacterEntity);
//	mCharacterCritterNode->setScale(0.3f);	*/
//	//mCharacterCritterNode->setPose(NxOgre::Vec3(0,-(mCharacterEntity->getBoundingBox().getSize().y/2),0),NxOgre::Quat::IDENTITY);
//
//	/*desc.setJumpVelocityFromMaxHeight(PhysicsManager::getSingletonPtr()->getScene()->getGravity().y, 0.75f);
//	mCharacter = mRenderSystem->createAnimatedCharacter(Ogre::Vector3::ZERO, Ogre::Radian(0), mCharacterCritterNode, desc);
//	mCharacter->setPosition(NxOgre::Vec3(enemyGlobalPosition.x,enemyGlobalPosition.y+4,enemyGlobalPosition.z));*/
//}
//
//GameObjectEnemy::~GameObjectEnemy()
//{
//	//mRenderSystem->destroyAnimatedCharacter(mCharacter);
//}
//
//void GameObjectEnemy::initialiseGameObject()
//{	
//	_MapEnemyStateAnimationState[IDLE] = mCharacterEntity->getAnimationState("Idle");
//	//_MapEnemyStateAnimationState[FIND] = mCharacterEntity->getAnimationState("Find");
//	//_MapEnemyStateAnimationState[WALK] = mCharacterEntity->getAnimationState("Walk");	
//
//	_CurrentAnimation = _MapEnemyStateAnimationState[IDLE];
//	_CurrentAnimation->setEnabled(true);
//	_CurrentAnimation->setLoop(true);
//	_CurrentEnemyState = IDLE;
//		
//	_EnemyStateCallbackFunc[IDLE] = boost::bind(&GameObjectEnemy::stateIdle, this, _1);
//	//_EnemyStateCallbackFunc[FIND] = boost::bind(&GameObjectEnemy::stateFind, this, _1);
//	//_EnemyStateCallbackFunc[WALK] = boost::bind(&GameObjectEnemy::stateWalk, this, _1);
//	
//}
//
//void GameObjectEnemy::clearGameObject()
//{	
//	_MapEnemyStateAnimationState.clear();
//	_EnemyStateCallbackFunc.clear();
//}
//
//void GameObjectEnemy::updateGameObject(const float elapsedSeconds)
//{
//	EnemyStateCallbackFunc::iterator i = _EnemyStateCallbackFunc.find(_CurrentEnemyState);
//   
//	if (i != _EnemyStateCallbackFunc.end())
//		i->second(elapsedSeconds);
//
//	////_RainNode->setPosition(Ogre::Vector3(mNode->getPosition().x,6,mNode->getPosition().z));
//	//mCharacterInputHelper.reset();
//
//	//if(_GoingLeft)
//	//{
//	//	mCharacterInputHelper.input.is_turning = false;
//	//	mCharacterInputHelper.left(127);
//	//}
//	//if(_GoingRight)
//	//{
//	//	mCharacterInputHelper.input.is_turning = false;
//	//	mCharacterInputHelper.right(127);
//	//}
//	//if(_GoingForward)
//	//{
//	//	mCharacterInputHelper.forward(127);
//	//}
//	//if(_GoingBack)
//	//{
//	//	mCharacterInputHelper.backward(127);
//	//}
//	//if(_GoingRRight)
//	//{
//	//	mCharacterInputHelper.input.is_turning = true;
//	//	mCharacterInputHelper.right();
//	//}
//	//if(_GoingRLeft)
//	//{
//	//	mCharacterInputHelper.input.is_turning = true;
//	//	mCharacterInputHelper.left();
//	//}
//	//if(_GoingUp)
//	//{
//	//	mCharacterInputHelper.up(true);
//	//}  
//
//	//mCharacter->setInput(mCharacterInputHelper);
//}
//
//bool GameObjectEnemy::keyPressed( const OIS::KeyEvent &e )
//{		
//	/*
//	if(e.key == OIS::KC_L)
//	{
//		if(_LanternLight->getVisible() == false) { _LanternLight->setVisible(true); }
//		else { _LanternLight->setVisible(false); }		
//	}
//	
//	if(e.key == OIS::KC_A)
//	{ 			
//		_GoingLeft = true; 		
//		_CurrentAnimation->setTimePosition(0);
//		_CurrentAnimation->setEnabled(false);
//		
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentAnimation = _MapPlayerStateAnimationState[RUNMG];
//		else
//			_CurrentAnimation = _MapPlayerStateAnimationState[RUNBLAST];
//		
//		_CurrentAnimation->setEnabled(true);
//		_CurrentAnimation->setLoop(true);
//		
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentPlayerState = RUNMG;
//		else
//			_CurrentPlayerState = RUNBLAST;
//	}
//
//	if(e.key == OIS::KC_D)
//	{ 
//		_GoingRight = true; 
//		_CurrentAnimation->setTimePosition(0);
//		_CurrentAnimation->setEnabled(false);
//
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentAnimation = _MapPlayerStateAnimationState[RUNMG];
//		else
//			_CurrentAnimation = _MapPlayerStateAnimationState[RUNBLAST];
//
//		_CurrentAnimation->setEnabled(true);
//		_CurrentAnimation->setLoop(true);
//		
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentPlayerState = RUNMG;
//		else
//			_CurrentPlayerState = RUNBLAST;
//	}
//	
//	if(e.key == OIS::KC_W)
//	{ 
//		_GoingForward = true; 
//		_CurrentAnimation->setTimePosition(0);
//		_CurrentAnimation->setEnabled(false);
//
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentAnimation = _MapPlayerStateAnimationState[RUNMG];
//		else
//			_CurrentAnimation = _MapPlayerStateAnimationState[RUNBLAST];
//
//		_CurrentAnimation->setEnabled(true);
//		_CurrentAnimation->setLoop(true);
//		
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentPlayerState = RUNMG;
//		else
//			_CurrentPlayerState = RUNBLAST;
//	}
//	
//	if(e.key == OIS::KC_S)
//	{ 
//		_GoingBack = true; 
//		_CurrentAnimation->setTimePosition(0);
//		_CurrentAnimation->setEnabled(false);
//
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentAnimation = _MapPlayerStateAnimationState[RUNMG];
//		else
//			_CurrentAnimation = _MapPlayerStateAnimationState[RUNBLAST];
//
//		_CurrentAnimation->setEnabled(true);
//		_CurrentAnimation->setLoop(true);
//		
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentPlayerState = RUNMG;
//		else
//			_CurrentPlayerState = RUNBLAST;
//	}	
//
//	if(e.key == OIS::KC_Q)
//	{ 		
//		_GoingRLeft = true; 
//	}		
//
//	if(e.key == OIS::KC_E)
//	{ 		
//		_GoingRRight = true; 
//	}		
//
//
//	if(e.key == OIS::KC_LSHIFT){ _FastMove = true; }
//
//	if(e.key == OIS::KC_0)
//	{
//		Weapons::WeaponsManager::getSingletonPtr()->setCurrentWeaponType(Weapons::WeaponsManager::BLAST);
//		_CurrentAnimation->setTimePosition(0);
//		_CurrentAnimation->setEnabled(false);
//		_CurrentAnimation = _MapPlayerStateAnimationState[MGTOBLAST];
//		_CurrentAnimation->setEnabled(true);
//		_CurrentAnimation->setLoop(false);
//		_CurrentPlayerState = MGTOBLAST;
//	}
//
//	if(e.key == OIS::KC_9)
//	{
//		Weapons::WeaponsManager::getSingletonPtr()->setCurrentWeaponType(Weapons::WeaponsManager::MG);
//		_CurrentAnimation->setTimePosition(0);
//		_CurrentAnimation->setEnabled(false);
//		_CurrentAnimation = _MapPlayerStateAnimationState[BLASTTOMG];
//		_CurrentAnimation->setEnabled(true);
//		_CurrentAnimation->setLoop(false);
//		_CurrentPlayerState = BLASTTOMG;
//	}
//	*/
//
//	return true;
//}
//
//bool GameObjectEnemy::keyReleased( const OIS::KeyEvent &e )
//{	
//	/*
//	if(e.key == OIS::KC_A)
//	{ 
//		_GoingLeft = false; 
//		_CurrentAnimation->setTimePosition(0);
//		_CurrentAnimation->setEnabled(false);
//
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentAnimation = _MapPlayerStateAnimationState[IDLEMG];
//		else
//			_CurrentAnimation = _MapPlayerStateAnimationState[IDLEBLAST];
//
//		_CurrentAnimation->setEnabled(true);
//		_CurrentAnimation->setLoop(false);
//		
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentPlayerState = IDLEMG;
//		else
//			_CurrentPlayerState = IDLEBLAST;
//	}
//
//	if(e.key == OIS::KC_D)
//	{ 		
//		_GoingRight = false; 
//		_GoingLeft = false; 
//		_CurrentAnimation->setTimePosition(0);
//		_CurrentAnimation->setEnabled(false);
//
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentAnimation = _MapPlayerStateAnimationState[IDLEMG];
//		else
//			_CurrentAnimation = _MapPlayerStateAnimationState[IDLEBLAST];
//
//		_CurrentAnimation->setEnabled(true);
//		_CurrentAnimation->setLoop(false);
//		
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentPlayerState = IDLEMG;
//		else
//			_CurrentPlayerState = IDLEBLAST;
//	}
//
//	if(e.key == OIS::KC_W)
//	{ 		
//		_GoingForward = false;
//		_GoingLeft = false; 
//		_CurrentAnimation->setTimePosition(0);
//		_CurrentAnimation->setEnabled(false);
//		
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentAnimation = _MapPlayerStateAnimationState[IDLEMG];
//		else
//			_CurrentAnimation = _MapPlayerStateAnimationState[IDLEBLAST];
//
//		_CurrentAnimation->setEnabled(true);
//		_CurrentAnimation->setLoop(false);
//		
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentPlayerState = IDLEMG;
//		else
//			_CurrentPlayerState = IDLEBLAST;
//	}
//
//	if(e.key == OIS::KC_S)
//	{ 		
//		_GoingBack = false; 
//		_GoingLeft = false; 
//		_CurrentAnimation->setTimePosition(0);
//		_CurrentAnimation->setEnabled(false);
//		
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentAnimation = _MapPlayerStateAnimationState[IDLEMG];
//		else
//			_CurrentAnimation = _MapPlayerStateAnimationState[IDLEBLAST];
//
//		_CurrentAnimation->setEnabled(true);
//		_CurrentAnimation->setLoop(false);
//
//		if(Weapons::WeaponsManager::getSingletonPtr()->getCurrentWeaponType() == Weapons::WeaponsManager::MG)
//			_CurrentPlayerState = IDLEMG;
//		else
//			_CurrentPlayerState = IDLEBLAST;
//		
//	}	
//
//	if(e.key == OIS::KC_Q)
//	{ 		
//		_GoingRLeft = false; 
//		//_PlayerAnimatedHelper.input.is_turning = false;
//	}		
//
//	if(e.key == OIS::KC_E)
//	{ 		
//		_GoingRRight = false; 
//		//_PlayerAnimatedHelper.input.is_turning = false;
//	}		
//
//	if(e.key == OIS::KC_LSHIFT){ _FastMove = false; }
//	*/
//
//	return true;
//}
//
//bool GameObjectEnemy::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
//{
//	/*_GunAnimStateArms = _PlayerEntityArms->getAnimationState("Shoot");
//	_GunAnimStateArms->setTimePosition(0);
//	_GunAnimStateArms->setLoop(false);
//	_GunAnimStateArms->setEnabled(true);	*/
//
//	/*
//	_GunAnimStateMG = _PlayerEntityMG->getAnimationState("CrochedBlast");
//	_GunAnimStateMG->setTimePosition(0);
//	_GunAnimStateMG->setLoop(false);
//	_GunAnimStateMG->setEnabled(true);	
//	*/
//	return true;
//}
//
//bool GameObjectEnemy::mouseMoved( const OIS::MouseEvent &e )
//{		
//	/*
//	mYaw += Ogre::Radian(Ogre::Degree(e.state.X.rel * -0.16f));		
//	mGameObjectSceneNode->pitch(Ogre::Degree(e.state.Y.rel * 0.16f));
//	*/
//
//	return true;
//}
//
//void GameObjectEnemy::stateIdle(Ogre::Real aElapsedTime)
//{
//	_CurrentAnimation->addTime(aElapsedTime);
//}
//
//void GameObjectEnemy::stateWalk(Ogre::Real aElapsedTime)
//{
//	_CurrentAnimation->addTime(aElapsedTime);
//}
//
//void GameObjectEnemy::stateFind(Ogre::Real aElapsedTime)
//{
//	_CurrentAnimation->addTime(aElapsedTime);
//}

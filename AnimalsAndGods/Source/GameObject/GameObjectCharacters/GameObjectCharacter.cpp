#include "stdafx.h"
#include "../../Header/GameObject/GameObjectCharacters/GameObjectCharacter.h"

GameObjectCharacter::GameObjectCharacter(Critter::Node* aNode, Critter::RenderSystem* aRenderSystem)
: CharacterController(aRenderSystem->getScene())
, mNode(aNode)
, mRenderSystem(aRenderSystem)
, mYaw(0)
, mUpDirection(NxOgre::Enums::Y)
{
	mScene->addSimulateListener(this, mPriority);
	mScene->addRenderListener(this, mPriority);
}

GameObjectCharacter::GameObjectCharacter(Ogre::uint32 aGOCHId, Critter::Node* aNode, Critter::RenderSystem* aRenderSystem)
: CharacterController(aRenderSystem->getScene())
, mNode(aNode)
, mRenderSystem(aRenderSystem)
, mYaw(0)
, mUpDirection(NxOgre::Enums::Y)
, mGOCHId(aGOCHId)
{
	mScene->addSimulateListener(this, mPriority);
	mScene->addRenderListener(this, mPriority);
}

GameObjectCharacter::~GameObjectCharacter()
{
	mScene->removeRenderListener(this, mPriority);
	mScene->removeSimulateListener(this, mPriority);
	delete mNode;
}

Critter::Enums::CharacterType GameObjectCharacter::getType() const
{
	return Critter::Enums::CharacterType_Base;
}

bool GameObjectCharacter::advance(float deltaTime, const NxOgre::Enums::Priority& priority, const NxOgre::Enums::SceneFunction& func)
{
	if (func == NxOgre::Enums::SceneFunction_Simulate)
		advancePhysics(deltaTime, priority);
	else
		advanceAnimation(deltaTime, priority);

	return true;
}

void GameObjectCharacter::advancePhysics(float deltaTime, const NxOgre::Enums::Priority&)
{
	if (hasCollidedDown() == false)
		move(mScene->getGravity());
}

void GameObjectCharacter::advanceAnimation(float deltaTime, const NxOgre::Enums::Priority&)
{
	mNode->setPosition(getPosition());
	mNode->setOrientation(mYaw, mUpDirection);
	//mNode->updateAnimations(deltaTime);
}
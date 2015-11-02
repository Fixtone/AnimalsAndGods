#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectNodes/GameObjectNode.h"


GameObjectNode::GameObjectNode(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode)
: GameObject(aGameObjectId)	
, mGONSceneNode(aGONSceneNode)				
{}	
		
GameObjectNode::~GameObjectNode()
{
	Tools::Destroy(GameManager::getSingletonPtr()->getSceneManager(), mGONSceneNode->getName());
}					
 
Ogre::SceneNode* GameObjectNode::getSceneNode()
{
	return mGONSceneNode;
}

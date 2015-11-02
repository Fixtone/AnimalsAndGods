#ifndef GameObjectNode_H	
#define GameObjectNode_H

class GameObjectNode : public GameObject
{
	public:				

		GameObjectNode(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode);		
		virtual ~GameObjectNode();

		Ogre::SceneNode* getSceneNode();

	protected:

		Ogre::SceneNode*															mGONSceneNode;
 };
#endif
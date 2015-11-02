#ifndef GameObjectLight_H	
#define GameObjectLight_H

class GameObjectLight : public GameObject
{
	public:		

		GameObjectLight(Ogre::int32 aGameObjectId, ShareData::GameConfigurations::LoadersConfigurations::GameObjectLightType aGameObjectLightType, 
						Ogre::SceneNode* aGOLSceneNode, Ogre::Light* aGOLLight);
		
		virtual ~GameObjectLight();

	public:	

		ShareData::GameConfigurations::LoadersConfigurations::GameObjectLightType	mGameObjectLightType;
		Ogre::SceneNode*															mGOLSceneNode;
		Ogre::Light*																mGOLLight;		

 };
#endif
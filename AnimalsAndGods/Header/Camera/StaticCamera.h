#ifndef StandardCamera_H
#define StandardCamera_H

#include "CustomCamera.h"

class StaticCamera : public CustomCamera
{
	public:

		StaticCamera(Ogre::SceneManager* aSceneManager);
		~StaticCamera();

		bool initialiseCamera(Ogre::String aCameraName, ShareData::GameConfigurations::CameraConfigurations::CustomCameraType aCustomCameraType, 
							  Ogre::Vector3 aPostion, Ogre::Vector3 aDirection);

		bool clearCamera(); 

};
#endif
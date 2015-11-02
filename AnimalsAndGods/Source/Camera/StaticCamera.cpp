#include "stdafx.h"
#include "../../Header/Camera/StaticCamera.h"

StaticCamera::StaticCamera(Ogre::SceneManager* aSceneManager)
: CustomCamera(aSceneManager)
{
}

StaticCamera::~StaticCamera()
{	
}

bool StaticCamera::initialiseCamera(Ogre::String aCameraName, ShareData::GameConfigurations::CameraConfigurations::CustomCameraType aCustomCameraType, 
								    Ogre::Vector3 aPostion, Ogre::Vector3 aDirection)
{
	try
	{
		mCustomCameraType = aCustomCameraType;
		mCamera = mSceneManager->createCamera(aCameraName);
		mCamera->setNearClipDistance(0.1f);
		mCamera->setFarClipDistance(1000.0f);		
		mCamera->setPosition(aPostion);
		mCamera->setDirection(aDirection);

		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}

bool StaticCamera::clearCamera()
{
	try
	{		
		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}

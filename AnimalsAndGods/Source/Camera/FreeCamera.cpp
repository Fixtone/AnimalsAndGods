#include "stdafx.h"
#include "../../Header/Camera/FreeCamera.h"

FreeCamera::FreeCamera(Ogre::SceneManager* aSceneManager)
: CustomCamera(aSceneManager)
{
}

FreeCamera::~FreeCamera()
{	
}

bool FreeCamera::initialiseCamera(Ogre::String aCameraName, ShareData::GameConfigurations::CameraConfigurations::CustomCameraType aCustomCameraType, 
								  Ogre::Vector3 aPostion, Ogre::Vector3 aDirection)
{
	try
	{		

		_CameraName	= aCameraName;	
		mCustomCameraType = aCustomCameraType;
		mCamera = mSceneManager->createCamera(_CameraName);
		mCamera->setNearClipDistance(0.1f);
		mCamera->setFarClipDistance(10000.0f);		
		mCamera->setPosition(aPostion);
		mCamera->setDirection(aDirection);
			
		_CameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
		_CameraMan->setTopSpeed(5);			

		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}

bool FreeCamera::clearCamera()
{
	try
	{		
		mSceneManager->destroyCamera(_CameraName);
		if(_CameraMan) delete _CameraMan;
		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}
	
void FreeCamera::update(const Ogre::FrameEvent& evt)
{
	_CameraMan->frameRenderingQueued(evt);
}

bool FreeCamera::keyPressed( const OIS::KeyEvent &arg )
{
	_CameraMan->injectKeyDown(arg);
	return true;
}

bool FreeCamera::keyReleased( const OIS::KeyEvent &e )
{
	_CameraMan->injectKeyUp(e);
	return true;
}
 
bool FreeCamera::mouseMoved( const OIS::MouseEvent &e )
{
	_CameraMan->injectMouseMove(e);
	return true;
}

bool FreeCamera::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	_CameraMan->injectMouseDown(e,id);
	return true;
}

bool FreeCamera::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	_CameraMan->injectMouseUp(e,id);
	return true;
}
 
bool FreeCamera::povMoved( const OIS::JoyStickEvent &e, int pov )
{	
	return true;
}

bool FreeCamera::axisMoved( const OIS::JoyStickEvent &e, int axis )
{
	return true;
}

bool FreeCamera::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )
{
	return true;
}

bool FreeCamera::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool FreeCamera::buttonReleased( const OIS::JoyStickEvent &e, int button )
{
	return true;
}
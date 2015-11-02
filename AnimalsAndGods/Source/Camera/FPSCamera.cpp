#include "stdafx.h"
#include "../../Header/Camera/FPSCamera.h"

FPSCamera::FPSCamera(Ogre::SceneManager* aSceneManager)
: CustomCamera(aSceneManager)
{
}

FPSCamera::~FPSCamera()
{	
}

bool FPSCamera::initialiseCamera(Ogre::String aCameraName, ShareData::GameConfigurations::CameraConfigurations::CustomCameraType aCustomCameraType, 
								 Ogre::SceneNode* aParentCameraNode, Ogre::Vector3 aPostion, Ogre::Vector3 aDirection)
{
	try
	{
		_CameraName		  = aCameraName;	
		m_RotateSpeed	  = 0.16f;
		m_TopSpeed		  = 20.0f;
		mCustomCameraType = aCustomCameraType;
		
		mCamera = mSceneManager->createCamera(_CameraName);		

		mCamera->setNearClipDistance(0.1f);
		mCamera->setFarClipDistance(1000.0f);				
				
		mCamera->setAutoTracking(false);
		mCamera->setFixedYawAxis(true);
		mCamera->setDebugDisplayEnabled(true);

		mCamera->setDirection(aDirection);
		mCamera->setPosition(aPostion);

		//FPS camera
		_ParentFPSCameraNode = aParentCameraNode;		
		_ParentFPSCameraNode->setAutoTracking(false);
		_ParentFPSCameraNode->setFixedYawAxis(true);
		_ParentFPSCameraNode->showBoundingBox(true);

		_FPSCameraNode = _ParentFPSCameraNode->createChildSceneNode("FPSCameraNode");		
		_FPSCameraYawNode = _FPSCameraNode->createChildSceneNode("FPSCameraYawNode");
		_FPSCameraPitchNode = _FPSCameraYawNode->createChildSceneNode("FPSCameraPitchNode");		
		_FPSCameraRollNode = _FPSCameraPitchNode->createChildSceneNode("FPSCameraRollNode");
		_FPSCameraRollNode->attachObject(mCamera);	

		Ogre::String nameDebugMesh = "CameraPlayer_DM#0";
		Procedural::SphereGenerator().setRadius(1).realizeMesh(nameDebugMesh);
		Ogre::Entity* entity = GameManager::getSingletonPtr()->getSceneManager()->createEntity(nameDebugMesh);
		Ogre::SceneNode* sn = _ParentFPSCameraNode->createChildSceneNode();
		sn->attachObject(entity);
		sn->setPosition(Ogre::Vector3::ZERO);
		entity->setMaterialName("WaypointLineDebug");
		entity->setCastShadows(false);			
		sn->setVisible(true);

		_ParentFPSCameraNode->translate(0,0.5f,0);

		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}

bool FPSCamera::clearCamera()
{
	try
	{		
		mSceneManager->destroyCamera(_CameraName);
		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}
	
void FPSCamera::updateCamera(Ogre::Real aElapsedTime)
{
	moveCamera(aElapsedTime);
}

void FPSCamera::moveCamera(Ogre::Real aElapsedTime)
{
	/*
	Ogre::Real deltaTime = aElapsedTime;// / 1000.0f;	
	Ogre::Real tooSmall	= std::numeric_limits<Ogre::Real>::epsilon();	

	pitchAngle = (2 * Ogre::Degree(Ogre::Math::ACos(_FPSCameraPitchNode->getOrientation().w)).valueDegrees());
	pitchAngleSign = _FPSCameraPitchNode->getOrientation().x;

	if(pitchAngle > 90.0f)
	{
		if(pitchAngleSign > 0) { _FPSCameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f), Ogre::Math::Sqrt(0.5f), 0, 0)); }
		else if(pitchAngleSign < 0) { _FPSCameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f), -Ogre::Math::Sqrt(0.5f), 0, 0)); }
	}
	*/
}

bool FPSCamera::keyPressed( const OIS::KeyEvent &arg )
{	
	return true;
}

bool FPSCamera::keyReleased( const OIS::KeyEvent &arg )
{
	return true;
}
 
bool FPSCamera::mouseMoved( const OIS::MouseEvent &e )
{
	//Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_NORMAL, "CameraYaw[" + Ogre::StringConverter::toString((2 * Ogre::Degree(Ogre::Math::ACos(_FPSCameraYawNode->getOrientation().w)).valueDegrees())) + "]");
	//Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_NORMAL, "CameraYaw[" + Ogre::StringConverter::toString(_FPSCameraYawNode->getOrientation().getYaw()) + "]");
	//Calculate the camera Yaw Angle   
	//_FPSCameraYawNode->yaw(Ogre::Degree(-e.state.X.rel * m_RotateSpeed));

	//Calculate the camera Pitch Angle   
	_FPSCameraPitchNode->pitch(Ogre::Degree(e.state.Y.rel * m_RotateSpeed));

   pitchAngleSign = _FPSCameraPitchNode->getOrientation().x;
   pitchAngle = (2 * Ogre::Degree(Ogre::Math::ACos(_FPSCameraPitchNode->getOrientation().w)).valueDegrees());  

   if(pitchAngle > 90.0f)
	{
		if(pitchAngleSign > 0)
		{
			_FPSCameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f), Ogre::Math::Sqrt(0.5f), 0, 0));
		}
		else if (pitchAngleSign < 0)
		{
		   _FPSCameraPitchNode->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f), -Ogre::Math::Sqrt(0.5f), 0, 0));
		}
	}

	return true;
}

bool FPSCamera::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	/*if(id == OIS::MB_Left) { m_bLMouseDown = true; }
	else if(id == OIS::MB_Right) { m_bRMouseDown = true; }*/
	
	return true;
}

bool FPSCamera::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{	
	/* if(id == OIS::MB_Left) { m_bLMouseDown = false; }
	else if(id == OIS::MB_Right) { m_bRMouseDown = false; }*/

	return true;
}
 
bool FPSCamera::povMoved( const OIS::JoyStickEvent &e, int pov )
{	
	return true;
}

bool FPSCamera::axisMoved( const OIS::JoyStickEvent &e, int axis )
{
	return true;
}

bool FPSCamera::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )
{
	return true;
}

bool FPSCamera::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool FPSCamera::buttonReleased( const OIS::JoyStickEvent &e, int button )
{
	return true;
}
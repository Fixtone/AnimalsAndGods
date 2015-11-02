#ifndef FPSCamera_H
#define FPSCamera_H

#include "CustomCamera.h"

class FPSCamera : public CustomCamera
{
	public:

		FPSCamera(Ogre::SceneManager* aSceneManager);
		~FPSCamera();
				
		bool initialiseCamera(Ogre::String aCameraName, ShareData::GameConfigurations::CameraConfigurations::CustomCameraType aCustomCameraType, Ogre::SceneNode* aParentCameraNode, Ogre::Vector3 aPostion, Ogre::Vector3 aDirection);

		bool clearCamera();
		void updateCamera(Ogre::Real aElapsedTime);

		bool makeCameraPhysics();

		bool keyPressed( const OIS::KeyEvent &arg );
		bool keyReleased( const OIS::KeyEvent &e );
 
		bool mouseMoved( const OIS::MouseEvent &e );
		bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
		bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );
 
		bool povMoved( const OIS::JoyStickEvent &e, int pov );
		bool axisMoved( const OIS::JoyStickEvent &e, int axis );
		bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID );
		bool buttonPressed( const OIS::JoyStickEvent &e, int button );
		bool buttonReleased( const OIS::JoyStickEvent &e, int button );	

		Ogre::SceneNode* getParentFPSCameraNode(){return _ParentFPSCameraNode;}
		Ogre::SceneNode* getFPSCameraNode(){return _FPSCameraNode;}
		Ogre::SceneNode* getFPSCameraYawNode(){return _FPSCameraYawNode;}
		Ogre::SceneNode* getFPSCameraPitchNode(){return _FPSCameraPitchNode;}
		Ogre::SceneNode* getFPSCameraRollNode(){return _FPSCameraRollNode;}

	private:

		Ogre::String				_CameraName;

		Ogre::SceneNode*			_ParentFPSCameraNode;
		Ogre::SceneNode*			_FPSCameraNode;
		Ogre::SceneNode*			_FPSCameraYawNode;
		Ogre::SceneNode*			_FPSCameraPitchNode;
		Ogre::SceneNode*			_FPSCameraRollNode;		

		Ogre::Degree				m_RotateSpeed;
		Ogre::Vector3				m_Velocity;
	
		Ogre::Real					pitchAngle;
		Ogre::Real					pitchAngleSign;
		Ogre::Real					m_TopSpeed;		

		bool						m_bLMouseDown, m_bRMouseDown;		

		void moveCamera(Ogre::Real aElapsedTime);

};
#endif
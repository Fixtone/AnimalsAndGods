#ifndef FreeCamera_H
#define FreeCamera_H

#include "CustomCamera.h"

class FreeCamera : public CustomCamera
{
	public:

		FreeCamera(Ogre::SceneManager* aSceneManager);
		~FreeCamera();

		bool initialiseCamera(Ogre::String aCameraName, ShareData::GameConfigurations::CameraConfigurations::CustomCameraType aCustomCameraType, 
							  Ogre::Vector3 aPostion, Ogre::Vector3 aDirection);
		bool clearCamera();
		void update(const Ogre::FrameEvent& evt);

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

	private:
	
		Ogre::String				_CameraName;
		OgreBites::SdkCameraMan*	_CameraMan;

};
#endif
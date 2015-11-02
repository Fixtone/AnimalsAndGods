#ifndef CustomCamera_H
#define CustomCamera_H

#include "../Physics/PhysicsManager.h"

class CustomCamera
{
	 public:
		
		CustomCamera(Ogre::SceneManager* aSceneManager)
		: mSceneManager(aSceneManager)
		{}
 
		virtual ~CustomCamera()
		{}

		virtual bool initialiseCamera(){return true;}
		virtual bool initialiseCamera(Ogre::String aCameraName, ShareData::GameConfigurations::CameraConfigurations::CustomCameraType aCustomCameraType, Ogre::Vector3 aPostion, Ogre::Vector3 aDirection){return true;}
		virtual bool initialiseCamera(Ogre::String aCameraName, ShareData::GameConfigurations::CameraConfigurations::CustomCameraType aCustomCameraType, Ogre::SceneNode* aParentCameraNode, Ogre::Vector3 aPostion, Ogre::Vector3 aDirection){return true;}

		virtual bool clearCamera(){return true;}
		virtual void update(const Ogre::FrameEvent& evt){};

		virtual bool keyPressed( const OIS::KeyEvent &arg ){return true;}
		virtual bool keyReleased( const OIS::KeyEvent &e ){return true;}
 
		virtual bool mouseMoved( const OIS::MouseEvent &e ){return true;}
		virtual bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id ){return true;}
		virtual bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id ){return true;}
 
		virtual bool povMoved( const OIS::JoyStickEvent &e, int pov ){return true;}
		virtual bool axisMoved( const OIS::JoyStickEvent &e, int axis ){return true;}
		virtual bool sliderMoved( const OIS::JoyStickEvent &e, int sliderID ){return true;}
		virtual bool buttonPressed( const OIS::JoyStickEvent &e, int button ){return true;}
		virtual bool buttonReleased( const OIS::JoyStickEvent &e, int button ){return true;}

		Ogre::Camera* getCamera(){return mCamera;}		
		ShareData::GameConfigurations::CameraConfigurations::CustomCameraType getCustomCameraType(){return mCustomCameraType;}

	protected:

		Ogre::SceneManager*														mSceneManager;		
		Ogre::Camera*															mCamera;
		ShareData::GameConfigurations::CameraConfigurations::CustomCameraType	mCustomCameraType;
 };
#endif
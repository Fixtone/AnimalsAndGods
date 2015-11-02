#ifndef CameraManager_H_
#define CameraManager_H_

#include "StaticCamera.h"
#include "FreeCamera.h"
#include "FPSCamera.h"

namespace Cameras
{
	class CameraManager : public Ogre::Singleton<CameraManager>
	{
		public:			

			CameraManager();
			~CameraManager();

			static CameraManager& getSingleton(void);
			static CameraManager* getSingletonPtr(void);

			bool initializeCameraManager(Ogre::Root* aRoot, Ogre::SceneManager* &aSceneManager, Ogre::RenderWindow* aRenderWindow);
			bool clearCameraManager();					

			CustomCamera* getActiveCamera();
			CustomCamera* getCameraByName(Ogre::String aCameraName);
			bool removeCustomCameraByName(Ogre::String aCameraName);

			void setActiveCamera(Ogre::String aCustomCameraName);			
			
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

			bool createCamera(ShareData::GameConfigurations::CameraConfigurations::CustomCameraType aCustomCameraType, Ogre::String aCameraName, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion);
			bool createCamera(ShareData::GameConfigurations::CameraConfigurations::CustomCameraType aCustomCameraType, Ogre::String aCameraName, Ogre::SceneNode* aParentSceneNode, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion);		
		
	private:

			CustomCamera* _createStaticCamera(Ogre::String aCameraName, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion);
			CustomCamera* _createFreeCamera(Ogre::String aCameraName, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion);
			CustomCamera* _createFPSCamera(Ogre::String aCameraName, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion);	
			CustomCamera* _createStaticCamera(Ogre::String aCameraName, Ogre::SceneNode* aParentSceneNode, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion);
			CustomCamera* _createFreeCamera(Ogre::String aCameraName, Ogre::SceneNode* aParentSceneNode, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion);
			CustomCamera* _createFPSCamera(Ogre::String aCameraName, Ogre::SceneNode* aParentSceneNode, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion);		

			bool _configureViewPort(Ogre::Camera* aCamera);			

			typedef boost::unordered_map<Ogre::String, CustomCamera*> MapCustomCameras;
			MapCustomCameras _MapCustomCameras;

			CustomCamera*			_ActiveCamera;

			Ogre::Root*				_Root;
			Ogre::SceneManager*		_SceneManager;
			Ogre::RenderWindow*		_RenderWindow;
			Ogre::Viewport*			_ViewPort;
			
	};
}
#endif
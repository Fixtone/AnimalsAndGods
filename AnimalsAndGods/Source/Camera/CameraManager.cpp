#include "stdafx.h"
#include "../../Header/Camera/CameraManager.h"

using namespace Cameras;

template<> CameraManager* Ogre::Singleton<CameraManager>::msSingleton = 0;
CameraManager* CameraManager::getSingletonPtr(void)
{
	return msSingleton;
}
CameraManager& CameraManager::getSingleton(void)
{  
	assert( msSingleton );  return ( *msSingleton );  
}

CameraManager::CameraManager()
: _ActiveCamera(0)
, _ViewPort(0)
{
}

CameraManager::~CameraManager(){}

bool CameraManager::initializeCameraManager(Ogre::Root* aRoot, Ogre::SceneManager* &aSceneManager, Ogre::RenderWindow* aRenderWindow)
{
	try
	{
		_Root = aRoot;
		_SceneManager = aSceneManager;
		_RenderWindow = aRenderWindow;	

		createCamera(ShareData::GameConfigurations::CameraConfigurations::STATIC,"GodCam", Ogre::Vector3(0, 0, 0), Ogre::Vector3(0,0,0));
		setActiveCamera("GodCam");

		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}

bool CameraManager::clearCameraManager()
{
	try
	{
		BOOST_FOREACH(MapCustomCameras::value_type& customCamera, _MapCustomCameras)
		{
			customCamera.second->clearCamera();
			delete customCamera.second;
		}
		
		_MapCustomCameras.clear();

		_ViewPort = 0;
		_ActiveCamera = 0;

		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}

bool CameraManager::createCamera(ShareData::GameConfigurations::CameraConfigurations::CustomCameraType aCustomCameraType, Ogre::String aCameraName, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion)
{
	try
	{	
		switch(aCustomCameraType)
		{
			case ShareData::GameConfigurations::CameraConfigurations::STATIC:
			{
				CustomCamera* customCamera = _createStaticCamera(aCameraName,aCameraPosition,aCameraDirecion);
				_configureViewPort(customCamera->getCamera());

				break;
			}
			case ShareData::GameConfigurations::CameraConfigurations::FREE:
			{
				CustomCamera* customCamera = _createFreeCamera(aCameraName,aCameraPosition,aCameraDirecion);
				_configureViewPort(customCamera->getCamera());
				break;
			}
			case ShareData::GameConfigurations::CameraConfigurations::FPS:
			{
				CustomCamera* customCamera = _createFPSCamera(aCameraName,aCameraPosition,aCameraDirecion);
				_configureViewPort(customCamera->getCamera());
				break;
			}
		};

		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}

bool CameraManager::createCamera(ShareData::GameConfigurations::CameraConfigurations::CustomCameraType aCustomCameraType, Ogre::String aCameraName, Ogre::SceneNode* aParentSceneNode, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion)
{
	try
	{	
		switch(aCustomCameraType)
		{
			case ShareData::GameConfigurations::CameraConfigurations::STATIC:
			{
				CustomCamera* customCamera = _createStaticCamera(aCameraName, aParentSceneNode, aCameraPosition,aCameraDirecion);
				_configureViewPort(customCamera->getCamera());

				break;
			}
			case ShareData::GameConfigurations::CameraConfigurations::FREE:
			{
				CustomCamera* customCamera = _createFreeCamera(aCameraName, aParentSceneNode, aCameraPosition,aCameraDirecion);
				_configureViewPort(customCamera->getCamera());
				break;
			}
			case ShareData::GameConfigurations::CameraConfigurations::FPS:
			{
				CustomCamera* customCamera = _createFPSCamera(aCameraName, aParentSceneNode, aCameraPosition,aCameraDirecion);
				_configureViewPort(customCamera->getCamera());
				break;
			}
		};

		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}

CustomCamera* CameraManager::getActiveCamera()
{
	return _ActiveCamera;
}

void CameraManager::setActiveCamera(Ogre::String aCustomCameraName)
{
	boost::unordered_map<Ogre::String, CustomCamera*>::const_iterator it = _MapCustomCameras.find(aCustomCameraName);
	if(it!=_MapCustomCameras.end())
	{
		_ActiveCamera = (*it).second;
		_ViewPort->setCamera(_ActiveCamera->getCamera());
		ShareData::DefferedShading::DefferedShadingSharedData::getSingletonPtr()->iCamera = _ActiveCamera->getCamera();
	}
}

CustomCamera* CameraManager::getCameraByName(Ogre::String aCameraName)
{
	return _MapCustomCameras[aCameraName];
}

bool CameraManager::removeCustomCameraByName(Ogre::String aCameraName)
{
	boost::unordered_map<Ogre::String, CustomCamera*>::const_iterator it = _MapCustomCameras.find(aCameraName);
	
	if(it!=_MapCustomCameras.end())
	{
		delete (*it).second;
		_MapCustomCameras.erase(it);
		_SceneManager->destroyCamera(aCameraName);		

		return true;
	}
	else
	{
		return false;
	}
}
	
void CameraManager::update(const Ogre::FrameEvent& evt)
{
	if(_ActiveCamera)
		_ActiveCamera->update(evt);
}

CustomCamera* CameraManager::_createStaticCamera(Ogre::String aCameraName, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion)
{
	_MapCustomCameras[aCameraName] = new StaticCamera(_SceneManager);	
	static_cast<StaticCamera*>(_MapCustomCameras[aCameraName])->initialiseCamera(aCameraName, ShareData::GameConfigurations::CameraConfigurations::STATIC, aCameraPosition, aCameraDirecion);		
	return _MapCustomCameras[aCameraName];
}

CustomCamera* CameraManager::_createFreeCamera(Ogre::String aCameraName, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion)
{	
	_MapCustomCameras[aCameraName] = new FreeCamera(_SceneManager);
	static_cast<FreeCamera*>(_MapCustomCameras[aCameraName])->initialiseCamera(aCameraName, ShareData::GameConfigurations::CameraConfigurations::FREE, aCameraPosition, aCameraDirecion);	
	return _MapCustomCameras[aCameraName];
}

CustomCamera* CameraManager::_createFPSCamera(Ogre::String aCameraName, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion)
{
	_MapCustomCameras[aCameraName] = new FPSCamera(_SceneManager);
	_MapCustomCameras[aCameraName]->initialiseCamera(aCameraName, ShareData::GameConfigurations::CameraConfigurations::FPS, aCameraPosition, aCameraDirecion);	
	return _MapCustomCameras[aCameraName];
}

CustomCamera* CameraManager::_createStaticCamera(Ogre::String aCameraName, Ogre::SceneNode* aParentNode, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion)
{
	/*
	_MapCustomCameras[aCameraName] = new StaticCamera(_SceneManager);	
	static_cast<StaticCamera*>(_MapCustomCameras[aCameraName])->initialiseCamera(aCameraName, ShareData::GameConfigurations::CameraConfigurations::STATIC, aParentNode, aCameraPosition, aCameraDirecion);		
	return _MapCustomCameras[aCameraName];
	*/
	return 0;
}

CustomCamera* CameraManager::_createFreeCamera(Ogre::String aCameraName, Ogre::SceneNode* aParentNode, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion)
{	
	/*
	_MapCustomCameras[aCameraName] = new FreeCamera(_SceneManager);
	_MapCustomCameras[aCameraName]->initialiseCamera(aCameraName, ShareData::GameConfigurations::CameraConfigurations::FREE, aParentNode, aCameraPosition, aCameraDirecion);	
	return _MapCustomCameras[aCameraName];
	*/
	return 0;
}

CustomCamera* CameraManager::_createFPSCamera(Ogre::String aCameraName, Ogre::SceneNode* aParentNode, Ogre::Vector3 aCameraPosition, Ogre::Vector3 aCameraDirecion)
{
	_MapCustomCameras[aCameraName] = new FPSCamera(_SceneManager);
	static_cast<FPSCamera*>(_MapCustomCameras[aCameraName])->initialiseCamera(aCameraName, ShareData::GameConfigurations::CameraConfigurations::FPS, aParentNode, aCameraPosition, aCameraDirecion);	
	return _MapCustomCameras[aCameraName];
}

bool CameraManager::_configureViewPort(Ogre::Camera* aCamera)
{
	try
	{	
		if(!_RenderWindow->hasViewportWithZOrder(0))
			_ViewPort = _RenderWindow->addViewport(aCamera);	
		else
			_ViewPort = _RenderWindow->getViewport(0);

		_ViewPort->setBackgroundColour(Ogre::ColourValue(0,0,0));
		_ViewPort->setCamera(aCamera);

		aCamera->setAspectRatio(Ogre::Real(_ViewPort->getActualWidth()) / Ogre::Real(_ViewPort->getActualHeight()));		

		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}


bool CameraManager::keyPressed( const OIS::KeyEvent &arg )
{
	if(_ActiveCamera)
		_ActiveCamera->keyPressed(arg);
	return true;
}

bool CameraManager::keyReleased( const OIS::KeyEvent &e )
{
	if(_ActiveCamera)
		_ActiveCamera->keyReleased(e);
	return true;
}
 
bool CameraManager::mouseMoved( const OIS::MouseEvent &e )
{
	if(_ActiveCamera)
		_ActiveCamera->mouseMoved(e);
	return true;
}

bool CameraManager::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	if(_ActiveCamera)
		_ActiveCamera->mousePressed(e,id);
	return true;
}

bool CameraManager::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	if(_ActiveCamera)
		_ActiveCamera->mouseReleased(e,id);
	return true;
}
 
bool CameraManager::povMoved( const OIS::JoyStickEvent &e, int pov )
{	
	if(_ActiveCamera)
		_ActiveCamera->povMoved(e,pov);
	return true;
}

bool CameraManager::axisMoved( const OIS::JoyStickEvent &e, int axis )
{
	if(_ActiveCamera)
		_ActiveCamera->axisMoved(e,axis);
	return true;
}

bool CameraManager::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )
{
	if(_ActiveCamera)
		_ActiveCamera->sliderMoved(e,sliderID);
	return true;
}

bool CameraManager::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	if(_ActiveCamera)
		_ActiveCamera->buttonPressed(e,button);
	return true;
}

bool CameraManager::buttonReleased( const OIS::JoyStickEvent &e, int button )
{
	if(_ActiveCamera)
		_ActiveCamera->buttonReleased(e,button);
	return true;
}

#include "stdafx.h"
#include "../../Header/GUI/GUI3D/GUI3DManager.h"


using namespace UI;

template<> GUI3DManager* Ogre::Singleton<GUI3DManager>::msSingleton = 0;
GUI3DManager* GUI3DManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
GUI3DManager& GUI3DManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

GUI3DManager::GUI3DManager()
: _ClassName("GUI3DManager")
, _Gui3D(0)
{
}

GUI3DManager::~GUI3DManager()
{
}

void GUI3DManager::initializeManager()
{	
	_Gui3D = new Gui3D::Gui3D(&_MyStandardPanelColors);

	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_NORMAL, _ClassName + ": GUI3D just came outta the mist :O");	
	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_NORMAL, _ClassName + ": Initialized :)");	
}

void GUI3DManager::clearManager()
{		
	if(_Gui3D)
		delete _Gui3D;

	Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_NORMAL, _ClassName + ": GUI3D went back into the mist...");
}
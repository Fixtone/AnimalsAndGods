#include "stdafx.h"
#include "../../Header/GameStates/ConsoleState.h"
  
ConsoleState ConsoleState::mConsoleState; 
void ConsoleState::enter()
{  
	mRoot = Ogre::Root::getSingletonPtr(); 
	mSceneMgr = mRoot->getSceneManager("AnimalsAndGodsSceneManager");		
	mRenderwindow = mRoot->getAutoCreatedWindow();

	mViewport = mRenderwindow->getViewport(0);
	mViewport->setBackgroundColour(Ogre::ColourValue(0.0, 1.0, 0.0));	

}
 
void ConsoleState::exit()
{	
}
 
void ConsoleState::pause()
{
}
 
void ConsoleState::resume()
{
}
 
bool ConsoleState::keyPressed( const OIS::KeyEvent &e )
{
	return true;
}

bool ConsoleState::keyReleased( const OIS::KeyEvent &e )
{
	return true;
}
 
bool ConsoleState::mouseMoved( const OIS::MouseEvent &e )
{
	return true;
}

bool ConsoleState::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{
	return true;
}

bool ConsoleState::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id )
{	
	return true;
}

bool ConsoleState::povMoved( const OIS::JoyStickEvent &e, int pov )
{
	return true;
}

bool ConsoleState::axisMoved( const OIS::JoyStickEvent &e, int axis )
{
	return true;
}

bool ConsoleState::sliderMoved( const OIS::JoyStickEvent &e, int sliderID )
{
	return true;
}

bool ConsoleState::buttonPressed( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool ConsoleState::buttonReleased( const OIS::JoyStickEvent &e, int button )
{
	return true;
}

bool ConsoleState::frameStarted(const Ogre::FrameEvent& evt)
{
	return true;
}

bool ConsoleState::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	return true;
}

bool ConsoleState::frameEnded(const Ogre::FrameEvent& evt)
{
	return true;
}
#include "StdAfx.h"
#include "Header\GameStates\GameManager.h"
#include "Header\GameStates\IntroState.h"

#ifdef __cplusplus
extern "C" {
#endif

#if _DEBUG 
	int main(int argc, char *argv[])
#else
	INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#endif
	{
		GameManager* game = new GameManager();		

		try 
		{
			// initialize the game and switch to the first state			
			game->start(IntroState::getInstance());						
			
		} 
		catch( Ogre::Exception& e )
		{

#if _DEBUG
   std::cerr << "An exception has occured: " <<	e.getFullDescription().c_str() << std::endl;
#else _RELEASE
	#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32	 
		MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
	#else
		std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
	#endif
#endif
		}

		delete game;

		return 0;
	}

#ifdef __cplusplus
}
#endif
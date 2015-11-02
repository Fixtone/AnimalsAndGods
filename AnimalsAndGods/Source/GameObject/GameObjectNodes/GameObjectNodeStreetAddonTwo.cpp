#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectNodes/GameObjectNodeStreetAddonTwo.h"

const char*		 GameObjectNodeStreetAddonTwo::GON_STREETADDONTWO_CULLINGFUNCTION = "GON_StreetAddonTwoCulling";

GameObjectNodeStreetAddonTwo::GONStreetAddonTwoStates GameObjectNodeStreetAddonTwo::StringToGONStreetAddonTwoState(Ogre::String aString)
{
	const char* str = aString.c_str();

	if(strcmp ( "On", str ) == 0)       return GameObjectNodeStreetAddonTwo::On;			
	if(strcmp ( "Off", str ) == 0)      return GameObjectNodeStreetAddonTwo::Off;			
	else								return GameObjectNodeStreetAddonTwo::FlipFlap;
}

GameObjectNodeStreetAddonTwo::GameObjectNodeStreetAddonTwo(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
														   Ogre::String aStreetAddonTwoEntityName,
														   GONStreetAddonTwoStates aGONStreetAddonTwoState)
: GameObjectNode(aGameObjectId, aGONSceneNode)	
, mStreetAddonTwoEntityName(aStreetAddonTwoEntityName)
, mGONStreetAddonTwoState(aGONStreetAddonTwoState)
{
}	
 
GameObjectNodeStreetAddonTwo::~GameObjectNodeStreetAddonTwo()
{	
}

void GameObjectNodeStreetAddonTwo::configure()
{		
	mStreetAddonTwoEntity = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(mStreetAddonTwoEntityName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC);		
}

void GameObjectNodeStreetAddonTwo::release()
{		
}

void GameObjectNodeStreetAddonTwo::updateLogic(lua_State *L, const float elapsedSeconds)
{			
	// the function name
	lua_getglobal(L, GON_STREETADDONTWO_CULLINGFUNCTION);
	
	// push arguments
	lua_pushnumber(L, mGameObjectId);	
	lua_pushnumber(L, mGONStreetAddonTwoState);

	// call the function with 2 argument, return 1 result
	lua_call(L, 2, 1);

	// get the result 
	GONStreetAddonTwoStates newGONStreetAddonTwoState = (GONStreetAddonTwoStates)luaL_checkint(L, -1);
	lua_pop(L, 1);

	// state is the new state for the player
	// Do something if and only if the state has changed!
	if(newGONStreetAddonTwoState != mGONStreetAddonTwoState)
	{		
		switch(newGONStreetAddonTwoState)
		{
			case On:
			{	
				mGONSceneNode->setVisible(true);												
			}
			break;
			case Off:
			{
				mGONSceneNode->setVisible(false);								
			}
			break;
		};
	
		mGONStreetAddonTwoState = newGONStreetAddonTwoState;
	}
}
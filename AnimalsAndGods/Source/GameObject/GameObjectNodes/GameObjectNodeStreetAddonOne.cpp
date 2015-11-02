#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectNodes/GameObjectNodeStreetAddonOne.h"

const char*		 GameObjectNodeStreetAddonOne::GON_STREETADDONOne_CULLINGFUNCTION = "GON_StreetAddonOneCulling";

GameObjectNodeStreetAddonOne::GONStreetAddonOneStates GameObjectNodeStreetAddonOne::StringToGONStreetAddonOneState(Ogre::String aString)
{
	const char* str = aString.c_str();

	if(strcmp ( "On", str ) == 0)       return GameObjectNodeStreetAddonOne::On;			
	else								return GameObjectNodeStreetAddonOne::Off;
}

GameObjectNodeStreetAddonOne::GameObjectNodeStreetAddonOne(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
															   Ogre::String aStreetAddonOneEntityName,
															   GONStreetAddonOneStates aGONStreetAddonOneState)
: GameObjectNode(aGameObjectId, aGONSceneNode)	
, mStreetAddonOneEntityName(aStreetAddonOneEntityName)
, mGONStreetAddonOneState(aGONStreetAddonOneState)
{
}	
 
GameObjectNodeStreetAddonOne::~GameObjectNodeStreetAddonOne()
{	
}

void GameObjectNodeStreetAddonOne::configure()
{		
	mStreetAddonOneEntity = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(mStreetAddonOneEntityName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDMOVABLE);		
}

void GameObjectNodeStreetAddonOne::release()
{		
}

void GameObjectNodeStreetAddonOne::updateLogic(lua_State *L, const float elapsedSeconds)
{			
	// the function name
	lua_getglobal(L, GON_STREETADDONOne_CULLINGFUNCTION);
	
	// push arguments
	lua_pushnumber(L, mGameObjectId);	
	lua_pushnumber(L, mGONStreetAddonOneState);

	// call the function with 2 argument, return 1 result
	lua_call(L, 2, 1);

	// get the result 
	GONStreetAddonOneStates newGONStreetAddonOneState = (GONStreetAddonOneStates)luaL_checkint(L, -1);
	lua_pop(L, 1);

	// state is the new state for the player
	// Do something if and only if the state has changed!
	if(newGONStreetAddonOneState != mGONStreetAddonOneState)
	{		
		switch(newGONStreetAddonOneState)
		{
			case On:
			{	
				//mGONSceneNode->setVisible(true);								
				mStreetAddonOneEntity->GOEData.mBody->getNode()->getSceneNode()->setVisible(true);
			}
			break;
			case Off:
			{
				//mGONSceneNode->setVisible(false);				
				mStreetAddonOneEntity->GOEData.mBody->getNode()->getSceneNode()->setVisible(false);
			}
			break;
		};
	
		mGONStreetAddonOneState = newGONStreetAddonOneState;
	}
}
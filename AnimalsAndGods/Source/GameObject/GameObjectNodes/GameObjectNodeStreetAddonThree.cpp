#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectNodes/GameObjectNodeStreetAddonThree.h"

const char*		 GameObjectNodeStreetAddonThree::GON_STREETADDONTHREE_CULLINGFUNCTION = "GON_StreetAddonThreeCulling";

GameObjectNodeStreetAddonThree::GONStreetAddonThreeStates GameObjectNodeStreetAddonThree::StringToGONStreetAddonThreeState(Ogre::String aString)
{
	const char* str = aString.c_str();

	if(strcmp ( "On", str ) == 0)       return GameObjectNodeStreetAddonThree::On;			
	else								return GameObjectNodeStreetAddonThree::Off;
}

GameObjectNodeStreetAddonThree::GameObjectNodeStreetAddonThree(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
															   Ogre::String aStreetAddonThreeEntityName,
															   GONStreetAddonThreeStates aGONStreetAddonThreeState)
: GameObjectNode(aGameObjectId, aGONSceneNode)	
, mStreetAddonThreeEntityName(aStreetAddonThreeEntityName)
, mGONStreetAddonThreeState(aGONStreetAddonThreeState)
{
}	
 
GameObjectNodeStreetAddonThree::~GameObjectNodeStreetAddonThree()
{	
}

void GameObjectNodeStreetAddonThree::configure()
{		
	mStreetAddonThreeEntity = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(mStreetAddonThreeEntityName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDMOVABLE);		
}

void GameObjectNodeStreetAddonThree::release()
{		
}

void GameObjectNodeStreetAddonThree::updateLogic(lua_State *L, const float elapsedSeconds)
{			
	// the function name
	lua_getglobal(L, GON_STREETADDONTHREE_CULLINGFUNCTION);
	
	// push arguments
	lua_pushnumber(L, mGameObjectId);	
	lua_pushnumber(L, mGONStreetAddonThreeState);

	// call the function with 2 argument, return 1 result
	lua_call(L, 2, 1);

	// get the result 
	GONStreetAddonThreeStates newGONStreetAddonThreeState = (GONStreetAddonThreeStates)luaL_checkint(L, -1);
	lua_pop(L, 1);

	// state is the new state for the player
	// Do something if and only if the state has changed!
	if(newGONStreetAddonThreeState != mGONStreetAddonThreeState)
	{		
		switch(newGONStreetAddonThreeState)
		{
			case On:
			{	
				//mGONSceneNode->setVisible(true);								
				mStreetAddonThreeEntity->GOEData.mBody->getNode()->getSceneNode()->setVisible(true);
			}
			break;
			case Off:
			{
				//mGONSceneNode->setVisible(false);				
				mStreetAddonThreeEntity->GOEData.mBody->getNode()->getSceneNode()->setVisible(false);
			}
			break;
		};
	
		mGONStreetAddonThreeState = newGONStreetAddonThreeState;
	}
}
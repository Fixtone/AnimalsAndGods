#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectNodes/GameObjectNodeStreetLight.h"

const char*	GameObjectNodeStreetLight::GON_STREETLIGHT_CULLINGFUNCTION = "GON_StreetLightCulling";
GameObjectNodeStreetLight::GONStreetLightStates GameObjectNodeStreetLight::StringToGONStreetLightState(Ogre::String aString)
{
	const char* str = aString.c_str();

	if(strcmp ( "On", str ) == 0)       return GameObjectNodeStreetLight::On;	
	else if(strcmp ( "Off", str ) == 0)	return GameObjectNodeStreetLight::Off;
	else								return GameObjectNodeStreetLight::FlipFlap;
}

GameObjectNodeStreetLight::GameObjectNodeStreetLight(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
													 Ogre::String aStreetLightEntityName, Ogre::String aLightStreetLightName, 
													 GONStreetLightStates aGONStreetLightState)
: GameObjectNode(aGameObjectId, aGONSceneNode)		
, mStreetLightEntityName(aStreetLightEntityName)
, mLightStreetLightName(aLightStreetLightName)
, mStreetLightEntity(0)
, mLightStreetLight(0)
, mGONStreetLightState(aGONStreetLightState)
{	
	mBillboardNode = aGONSceneNode->createChildSceneNode("StreetLightBillboard@" + Ogre::StringConverter::toString(mGameObjectId));
	mBillboardSet = GameManager::getSingletonPtr()->getSceneManager()->createBillboardSet("mySet@" + Ogre::StringConverter::toString(mGameObjectId));
	mBillboardSet->setMaterialName("LightShafts");
	mBillboardSet->setBillboardType(Ogre::BBT_ORIENTED_SELF);
	Billboard* myBillboard = mBillboardSet->createBillboard(Ogre::Vector3::ZERO);	
	myBillboard->mDirection = Ogre::Vector3::UNIT_Y;
	myBillboard->setDimensions(5,9.2f);
	myBillboard->setPosition(0,3.50f,1.8f); 
	mBillboardNode->attachObject(mBillboardSet);
}	
 
void GameObjectNodeStreetLight::configure()
{
	mStreetLightEntity = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(mStreetLightEntityName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC);	
	mLightStreetLight = GOL::GameObjectLightManager::getSingletonPtr()->GetGOLStreetLight(mLightStreetLightName);	
	mLightStreetLight->mGOLLight->setVisible(true);
};

void GameObjectNodeStreetLight::release()
{	
};

bool GameObjectNodeStreetLight::update(const Ogre::Real aElapsedTime)
{
	return true;
}

void GameObjectNodeStreetLight::updateLogic(lua_State *L, const float elapsedSeconds)
{		
	// the function name
	lua_getglobal(L, GON_STREETLIGHT_CULLINGFUNCTION);
	
	// push arguments
	lua_pushnumber(L, mGameObjectId);	
	lua_pushnumber(L, mGONStreetLightState);

	// call the function with 1 argument, return 1 result
	lua_call(L, 2, 1);

	// get the result 
	GONStreetLightStates newGONStreetLightState = (GONStreetLightStates)luaL_checkint(L, -1);
	lua_pop(L, 1);

	// state is the new state for the player
	// Do something if and only if the state has changed!
	if(newGONStreetLightState != mGONStreetLightState)
	{		
		switch(newGONStreetLightState)
		{
			case On:
			{				
				mLightStreetLight->mGOLLight->setVisible(true);				
				mGONSceneNode->setVisible(true);
			}
			break;
			case Off:
			{
				mLightStreetLight->mGOLLight->setVisible(false);
				mGONSceneNode->setVisible(false);
			}
			break;
		};
	
		mGONStreetLightState = newGONStreetLightState;
	}	
}
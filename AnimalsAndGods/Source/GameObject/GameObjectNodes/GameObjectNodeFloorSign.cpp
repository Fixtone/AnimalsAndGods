#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectNodes/GameObjectNodeFloorSign.h"

const char*		 GameObjectNodeFloorSign::GON_FLOORSIGN_CULLINGFUNCTION = "GON_FloorSignCulling";
const Ogre::Real GameObjectNodeFloorSign::MIN_TIME_FLOORSIGNFRONT = 4.0f;
const Ogre::Real GameObjectNodeFloorSign::MAX_TIME_FLOORSIGNFRONT = 10.0f;
const Ogre::Real GameObjectNodeFloorSign::MIN_TIME_FLOORSIGNBACK = 4.0f;
const Ogre::Real GameObjectNodeFloorSign::MAX_TIME_FLOORSIGNBACK = 10.0f;


GameObjectNodeFloorSign::GONFloorSignStates GameObjectNodeFloorSign::StringToGONFloorSignState(Ogre::String aString)
{
	const char* str = aString.c_str();

	if(strcmp ( "On", str ) == 0)       return GameObjectNodeFloorSign::On;			
	else								return GameObjectNodeFloorSign::Off;
}

GameObjectNodeFloorSign::GameObjectNodeFloorSign(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
												 Ogre::String aFloorSignEntityName, Ogre::String aFloorSignBackEntityName, Ogre::String aFloorSignFrontEntityName, 
												 GONFloorSignStates aGONFloorSignState)
: GameObjectNode(aGameObjectId, aGONSceneNode)	
, mFloorSignEntityName(aFloorSignEntityName)
, mFloorSignBackEntityName(aFloorSignBackEntityName)		
, mFloorSignFrontEntityName(aFloorSignFrontEntityName)	
, mFloorSignEntity(0)
, mFloorSignBackEntity(0)
, mFloorSignFrontEntity(0)
, mAcumTimeFloorSignBack(0)
, mSwitchTimeFloorSignBack(0)
, mAcumTimeFloorSignFront(0)
, mSwitchTimeFloorSignFront(0)
, mGONFloorSignState(aGONFloorSignState)
{			
}	
 
GameObjectNodeFloorSign::~GameObjectNodeFloorSign()
{	
}

void GameObjectNodeFloorSign::configure()
{	
	//Ogre::ResourcePtr a = Ogre::TextureManager::getSingletonPtr()->getResourceByName("Poster_0");
	//const Ogre::TexturePtr destinationTexture = Ogre::TextureManager::getSingletonPtr()->getResourceByName("Poster_0.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	//mPosters.push_back(Ogre::TextureManager::getSingletonPtr()->getByName("Poster_0", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME));

	mFloorSignEntity = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(mFloorSignEntityName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC);
	mFloorSignBackEntity = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(mFloorSignBackEntityName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC);
	mFloorSignFrontEntity = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(mFloorSignFrontEntityName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC);

	mFloorSignMaterialPtr = mFloorSignEntity->mGOEEntity->getSubEntity(0)->getMaterial();
	mFloorSignBackMaterialPtr = mFloorSignBackEntity->mGOEEntity->getSubEntity(0)->getMaterial();
	mFloorSignFrontMaterialPtr = mFloorSignFrontEntity->mGOEEntity->getSubEntity(0)->getMaterial();

	mSwitchTimeFloorSignBack = Ogre::Math::RangeRandom(MIN_TIME_FLOORSIGNBACK,MAX_TIME_FLOORSIGNBACK);
	mSwitchTimeFloorSignFront = Ogre::Math::RangeRandom(MIN_TIME_FLOORSIGNFRONT,MAX_TIME_FLOORSIGNFRONT);
	
	mNewFloorSignMaterialPtr = Ogre::MaterialManager::getSingleton().create(Ogre::StringConverter::toString(mGameObjectId) + "@FloorSignMaterial#M", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	mFloorSignMaterialPtr->copyDetailsTo(mNewFloorSignMaterialPtr);
	mFloorSignEntity->mGOEEntity->getSubEntity(0)->setMaterial(mNewFloorSignMaterialPtr);

	mNewFloorSignBackMaterialPtr = Ogre::MaterialManager::getSingleton().create(Ogre::StringConverter::toString(mGameObjectId) + "@FloorSignBackMaterial#M", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	mFloorSignBackMaterialPtr->copyDetailsTo(mNewFloorSignBackMaterialPtr);
	mFloorSignBackEntity->mGOEEntity->getSubEntity(0)->setMaterial(mNewFloorSignBackMaterialPtr);
	
	mNewFloorSignFrontMaterialPtr = Ogre::MaterialManager::getSingleton().create(Ogre::StringConverter::toString(mGameObjectId) + "@FloorSignFrontMaterial#M", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	mFloorSignFrontMaterialPtr->copyDetailsTo(mNewFloorSignFrontMaterialPtr);
	mFloorSignFrontEntity->mGOEEntity->getSubEntity(0)->setMaterial(mNewFloorSignFrontMaterialPtr);
		
	int posterSet = Ogre::Math::RangeRandom(0,7.9f);
	mNewFloorSignBackMaterialPtr->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName("Poster_" + Ogre::StringConverter::toString(posterSet) + ".png");
	mNewFloorSignBackMaterialPtr->getTechnique(1)->getPass(0)->getTextureUnitState(0)->setTextureName("PosterGlow_" + Ogre::StringConverter::toString(posterSet) + ".png");	

	posterSet = Ogre::Math::RangeRandom(0,7.9f);
	mNewFloorSignFrontMaterialPtr->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName("Poster_" + Ogre::StringConverter::toString(posterSet) + ".png");
	mNewFloorSignFrontMaterialPtr->getTechnique(1)->getPass(0)->getTextureUnitState(0)->setTextureName("PosterGlow_" + Ogre::StringConverter::toString(posterSet) + ".png");

};

void GameObjectNodeFloorSign::release()
{	
	Ogre::MaterialManager::getSingleton().remove(mNewFloorSignMaterialPtr->getHandle());
	Ogre::MaterialManager::getSingleton().remove(mNewFloorSignBackMaterialPtr->getHandle());
	Ogre::MaterialManager::getSingleton().remove(mNewFloorSignFrontMaterialPtr->getHandle());
};

bool GameObjectNodeFloorSign::update(const Ogre::Real aElapsedTime)
{			
	if(mAcumTimeFloorSignBack>mSwitchTimeFloorSignBack)
	{
		int posterSet = Ogre::Math::RangeRandom(0,7.9f);
		mNewFloorSignBackMaterialPtr->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName("Poster_" + Ogre::StringConverter::toString(posterSet) + ".png");
		mNewFloorSignBackMaterialPtr->getTechnique(1)->getPass(0)->getTextureUnitState(0)->setTextureName("PosterGlow_" + Ogre::StringConverter::toString(posterSet) + ".png");
		//mNewFloorSignBackMaterialPtr->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScroll(0.33f*imageSet,0);
		//mNewFloorSignBackMaterialPtr->getTechnique(1)->getPass(0)->getTextureUnitState(0)->setTextureScroll(0.33f*imageSet,0);
		mSwitchTimeFloorSignBack = Ogre::Math::RangeRandom(MIN_TIME_FLOORSIGNBACK,MAX_TIME_FLOORSIGNBACK);
		mAcumTimeFloorSignBack = 0;
	}
	else
		mAcumTimeFloorSignBack += aElapsedTime;

	if(mAcumTimeFloorSignFront>mSwitchTimeFloorSignFront)
	{
		int posterSet = Ogre::Math::RangeRandom(0,7.9f);
		mNewFloorSignFrontMaterialPtr->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName("Poster_" + Ogre::StringConverter::toString(posterSet) + ".png");
		mNewFloorSignFrontMaterialPtr->getTechnique(1)->getPass(0)->getTextureUnitState(0)->setTextureName("PosterGlow_" + Ogre::StringConverter::toString(posterSet) + ".png");
		//mNewFloorSignFrontMaterialPtr->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureScroll(0.33f*imageSet,0);
		//mNewFloorSignFrontMaterialPtr->getTechnique(1)->getPass(0)->getTextureUnitState(0)->setTextureScroll(0.33f*imageSet,0);
		mSwitchTimeFloorSignFront = Ogre::Math::RangeRandom(MIN_TIME_FLOORSIGNFRONT,MAX_TIME_FLOORSIGNFRONT);
		mAcumTimeFloorSignFront = 0;
	}
	else
		mAcumTimeFloorSignFront += aElapsedTime;

	return true;
}

void GameObjectNodeFloorSign::updateLogic(lua_State *L, const float elapsedSeconds)
{			
	// the function name
	lua_getglobal(L, GON_FLOORSIGN_CULLINGFUNCTION);
	
	// push arguments
	lua_pushnumber(L, mGameObjectId);	
	lua_pushnumber(L, mGONFloorSignState);

	// call the function with 1 argument, return 1 result
	lua_call(L, 2, 1);

	// get the result 
	GONFloorSignStates newGONFloorSignState = (GONFloorSignStates)luaL_checkint(L, -1);
	lua_pop(L, 1);

	// state is the new state for the player
	// Do something if and only if the state has changed!
	if(newGONFloorSignState != mGONFloorSignState)
	{		
		switch(newGONFloorSignState)
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
	
		mGONFloorSignState = newGONFloorSignState;
	}
}

void GameObjectNodeFloorSign::_SetGlowOff(Ogre::MaterialPtr aMaterialPtr, Ogre::String aTechniqueName)
{
	aMaterialPtr->getTechnique(1)->getPass(0)->setAmbient(Ogre::ColourValue::Black);
	aMaterialPtr->getTechnique(1)->getPass(0)->setDiffuse(Ogre::ColourValue::Black);
	aMaterialPtr->getTechnique(1)->getPass(0)->setSelfIllumination(Ogre::ColourValue::Black);
}

void GameObjectNodeFloorSign::_SetGlowOn(Ogre::MaterialPtr aMaterialPtr, Ogre::String aTechniqueName)
{
	aMaterialPtr->getTechnique(1)->getPass(0)->setAmbient(Ogre::ColourValue::White);
	aMaterialPtr->getTechnique(1)->getPass(0)->setDiffuse(Ogre::ColourValue::White);
	aMaterialPtr->getTechnique(1)->getPass(0)->setSelfIllumination(Ogre::ColourValue::White);
}
#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectNodes/GameObjectNodeLighter.h"

const char*		 GameObjectNodeLighter::GON_LIGHTER_CULLINGFUNCTION = "GON_LighterCulling";
const Ogre::Real GameObjectNodeLighter::MIN_TIME_PEDRASTIANS = 4.0f;
const Ogre::Real GameObjectNodeLighter::MAX_TIME_PEDRASTIANS = 10.0f;
const Ogre::Real GameObjectNodeLighter::MIN_TIME_REDLIGHTER = 4.0f;
const Ogre::Real GameObjectNodeLighter::MAX_TIME_REDLIGHTER = 10.0f;
const Ogre::Real GameObjectNodeLighter::MIN_TIME_GREENLIGHTER = 4.0f;
const Ogre::Real GameObjectNodeLighter::MAX_TIME_GREENLIGHTER = 10.0f;
const Ogre::Real GameObjectNodeLighter::TIME_YELLOWLIGHTER = 1.0f;

GameObjectNodeLighter::GONLighterStates GameObjectNodeLighter::StringToGONLighterStates(Ogre::String aString)
{
	const char* str = aString.c_str();

	if(strcmp ( "On", str ) == 0)       return GameObjectNodeLighter::On;			
	else								return GameObjectNodeLighter::Off;
}

GameObjectNodeLighter::GameObjectNodeLighter(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, 
											 Ogre::String aLPanelInfoName, Ogre::String aLCarLighterName, Ogre::String aLPedrastianLighterName, 
											 GONLighterStates aGONLighterState)
: GameObjectNode(aGameObjectId, aGONSceneNode)		
, mAcumTimePedrastians(0)
, mSwitchTimePedrastians(0)
, mCurrentPedrastiansState(PedrastianWalk)
, mAcumTimeCars(0)
, mSwitchTimeCars(0)
, mCurrentCarsState(CarStop)
, mLCarLighterGOE(0)
, mLPedrastianLighterGOE(0)
, mLPanelInfoName(aLPanelInfoName)
, mLCarLighterName(aLCarLighterName)
, mLPedrastianLighterName(aLPedrastianLighterName)
, mGONLighterState(aGONLighterState)
{			
}	
 
GameObjectNodeLighter::~GameObjectNodeLighter()
{	
}

void GameObjectNodeLighter::configure()
{
	mLPanelInfoGOE = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(mLPanelInfoName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC);
	mGONLighterInfoMaterialPtr = mLPanelInfoGOE->mGOEEntity->getSubEntity(0)->getMaterial();			
	
	mGONNewInfoMaterialPtr = Ogre::MaterialManager::getSingleton().create(Ogre::StringConverter::toString(mGameObjectId) + "@InfoMaterial#M", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	mGONLighterInfoMaterialPtr->copyDetailsTo(mGONNewInfoMaterialPtr);
	mLPanelInfoGOE->mGOEEntity->getSubEntity(0)->setMaterial(mGONNewInfoMaterialPtr);

	mLCarLighterGOE = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(mLCarLighterName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC);
	mGONRedLighterCarMaterialPtr = mLCarLighterGOE->mGOEEntity->getSubEntity(2)->getMaterial();
	mGONYellowLighterCarMaterialPtr = mLCarLighterGOE->mGOEEntity->getSubEntity(3)->getMaterial();
	mGONGreenLighterCarMaterialPtr = mLCarLighterGOE->mGOEEntity->getSubEntity(0)->getMaterial();
	mSwitchTimeCars = Ogre::Math::RangeRandom(MIN_TIME_REDLIGHTER,MAX_TIME_REDLIGHTER);
	
	mGONNewRedMaterialPtr = Ogre::MaterialManager::getSingleton().create(Ogre::StringConverter::toString(mGameObjectId) + "@RedMaterial#M", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	mGONRedLighterCarMaterialPtr->copyDetailsTo(mGONNewRedMaterialPtr);
	mLCarLighterGOE->mGOEEntity->getSubEntity(2)->setMaterial(mGONNewRedMaterialPtr);
	mLCarLighterGOE->mGOEEntity->getManualLodLevel(0)->getSubEntity(2)->setMaterial(mGONNewRedMaterialPtr);
	mLCarLighterGOE->mGOEEntity->getManualLodLevel(1)->getSubEntity(2)->setMaterial(mGONNewRedMaterialPtr);

	mGONNewYellowMaterialPtr = Ogre::MaterialManager::getSingleton().create(Ogre::StringConverter::toString(mGameObjectId) + "@YellowMaterial#M", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	mGONYellowLighterCarMaterialPtr->copyDetailsTo(mGONNewYellowMaterialPtr);
	mLCarLighterGOE->mGOEEntity->getSubEntity(3)->setMaterial(mGONNewYellowMaterialPtr);
	mLCarLighterGOE->mGOEEntity->getManualLodLevel(0)->getSubEntity(3)->setMaterial(mGONNewYellowMaterialPtr);
	mLCarLighterGOE->mGOEEntity->getManualLodLevel(1)->getSubEntity(3)->setMaterial(mGONNewYellowMaterialPtr);

	mGONNewGreenbMaterialPtr = Ogre::MaterialManager::getSingleton().create(Ogre::StringConverter::toString(mGameObjectId) + "@GreenMaterial#M", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	mGONGreenLighterCarMaterialPtr->copyDetailsTo(mGONNewGreenbMaterialPtr);
	mLCarLighterGOE->mGOEEntity->getSubEntity(0)->setMaterial(mGONNewGreenbMaterialPtr);
	mLCarLighterGOE->mGOEEntity->getManualLodLevel(0)->getSubEntity(0)->setMaterial(mGONNewGreenbMaterialPtr);
	mLCarLighterGOE->mGOEEntity->getManualLodLevel(1)->getSubEntity(0)->setMaterial(mGONNewGreenbMaterialPtr);	
	_SetGlowOff(mGONNewRedMaterialPtr,"glow");
	_SetGlowOff(mGONNewYellowMaterialPtr,"glow");

	mLPedrastianLighterGOE = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(mLPedrastianLighterName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC);
	mGONLighterPedrastiansMaterialPtr = mLPedrastianLighterGOE->mGOEEntity->getSubEntity(0)->getMaterial();
	mSwitchTimePedrastians = Ogre::Math::RangeRandom(MIN_TIME_PEDRASTIANS,MAX_TIME_PEDRASTIANS);	
	mGONNewPedrastiansMaterialPtr = Ogre::MaterialManager::getSingleton().create(Ogre::StringConverter::toString(mGameObjectId) + "@PedrastiansMaterial#M", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	mGONLighterPedrastiansMaterialPtr->copyDetailsTo(mGONNewPedrastiansMaterialPtr);
	mLPedrastianLighterGOE->mGOEEntity->getSubEntity(0)->setMaterial(mGONNewPedrastiansMaterialPtr);
	mLCarLighterGOE->mGOEEntity->getManualLodLevel(0)->getSubEntity(0)->setMaterial(mGONNewPedrastiansMaterialPtr);
	mLCarLighterGOE->mGOEEntity->getManualLodLevel(1)->getSubEntity(0)->setMaterial(mGONNewPedrastiansMaterialPtr);
	_SetGlowOff(mGONNewPedrastiansMaterialPtr,"glow");	
};

void GameObjectNodeLighter::release()
{	
	Ogre::MaterialManager::getSingleton().remove(mGONNewInfoMaterialPtr->getHandle());
	Ogre::MaterialManager::getSingleton().remove(mGONNewRedMaterialPtr->getHandle());
	Ogre::MaterialManager::getSingleton().remove(mGONNewYellowMaterialPtr->getHandle());
	Ogre::MaterialManager::getSingleton().remove(mGONNewGreenbMaterialPtr->getHandle());
	Ogre::MaterialManager::getSingleton().remove(mGONNewPedrastiansMaterialPtr->getHandle());
};

bool GameObjectNodeLighter::update(const Ogre::Real aElapsedTime)
{			
	if(mAcumTimePedrastians>mSwitchTimePedrastians)
	{
		switch(mCurrentPedrastiansState)
		{
			case PedrastianWalk:
				_SetGlowOff(mGONNewPedrastiansMaterialPtr,"glow");
				mCurrentPedrastiansState = PedrastianStop;
			break;
			case PedrastianStop:
				_SetGlowOn(mGONNewPedrastiansMaterialPtr,"glow");
				mCurrentPedrastiansState = PedrastianWalk;
			break;
		};
		mSwitchTimePedrastians = Ogre::Math::RangeRandom(MIN_TIME_PEDRASTIANS,MAX_TIME_PEDRASTIANS);
		mAcumTimePedrastians = 0;
	}
	else
		mAcumTimePedrastians += aElapsedTime;

	if(mAcumTimeCars>mSwitchTimeCars)
	{
		switch(mCurrentCarsState)
		{
			case CarStop:
				_SetGlowOff(mGONNewRedMaterialPtr,"glow");						
				_SetGlowOn(mGONNewYellowMaterialPtr,"glow");						
				mCurrentCarsState = CarWarning;
				mSwitchTimeCars = TIME_YELLOWLIGHTER;
			break;
			case CarWarning:
				_SetGlowOff(mGONNewYellowMaterialPtr,"glow");						
				_SetGlowOn(mGONNewGreenbMaterialPtr,"glow");						
				mCurrentCarsState = CarRun;
				mSwitchTimeCars = Ogre::Math::RangeRandom(MIN_TIME_GREENLIGHTER,MAX_TIME_GREENLIGHTER);
			break;
			case CarRun:
				_SetGlowOff(mGONNewGreenbMaterialPtr,"glow");						
				_SetGlowOn(mGONNewRedMaterialPtr,"glow");						
				mCurrentCarsState = CarStop;
				mSwitchTimeCars = Ogre::Math::RangeRandom(MIN_TIME_REDLIGHTER,MAX_TIME_REDLIGHTER);
			break;
		};
				
		mAcumTimeCars = 0;
	}
	else
		mAcumTimeCars += aElapsedTime;
			

	return true;
}

void GameObjectNodeLighter::updateLogic(lua_State *L, const float elapsedSeconds)
{			
	// the function name
	lua_getglobal(L, GON_LIGHTER_CULLINGFUNCTION);
	
	// push arguments
	lua_pushnumber(L, mGameObjectId);	
	lua_pushnumber(L, mGONLighterState);

	// call the function with 1 argument, return 1 result
	lua_call(L, 2, 1);

	// get the result 
	GONLighterStates newGONLighterState = (GONLighterStates)luaL_checkint(L, -1);
	lua_pop(L, 1);

	// state is the new state for the player
	// Do something if and only if the state has changed!
	if(newGONLighterState != mGONLighterState)
	{		
		switch(newGONLighterState)
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
	
		mGONLighterState = newGONLighterState;
	}
}

void GameObjectNodeLighter::_CreateMaterial(Ogre::String aNewMaterialnName, Ogre::MaterialPtr aCopyMaterial, Ogre::MaterialPtr aNewMaterial, Ogre::Entity* aEntity)
{	
	/*
	aNewMaterial = Ogre::MaterialManager::getSingleton().create(aNewMaterialnName, "Play");
	aCopyMaterial->copyDetailsTo(aNewMaterial);
	aEntity->getSubEntity(0)->setMaterial(aNewMaterial);
	*/
}

void GameObjectNodeLighter::_SetGlowOff(Ogre::MaterialPtr aMaterialPtr, Ogre::String aTechniqueName)
{
	aMaterialPtr->getTechnique(1)->getPass(0)->setAmbient(Ogre::ColourValue::Black);
	aMaterialPtr->getTechnique(1)->getPass(0)->setDiffuse(Ogre::ColourValue::Black);
	aMaterialPtr->getTechnique(1)->getPass(0)->setSelfIllumination(Ogre::ColourValue::Black);
}

void GameObjectNodeLighter::_SetGlowOn(Ogre::MaterialPtr aMaterialPtr, Ogre::String aTechniqueName)
{
	aMaterialPtr->getTechnique(1)->getPass(0)->setAmbient(Ogre::ColourValue::White);
	aMaterialPtr->getTechnique(1)->getPass(0)->setDiffuse(Ogre::ColourValue::White);
	aMaterialPtr->getTechnique(1)->getPass(0)->setSelfIllumination(Ogre::ColourValue::White);
}
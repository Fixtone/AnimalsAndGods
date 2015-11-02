#include "stdafx.h"
#include "../../Header/Tools/ShareData.h"

template<> ShareData::DefferedShading::DefferedShadingSharedData* Ogre::Singleton<ShareData::DefferedShading::DefferedShadingSharedData>::msSingleton = 0;
ShareData::DefferedShading::DefferedShadingSharedData* ShareData::DefferedShading::DefferedShadingSharedData::getSingletonPtr(void)
{
	return msSingleton;
}
 
ShareData::DefferedShading::DefferedShadingSharedData& ShareData::DefferedShading::DefferedShadingSharedData::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

ShareData::DefferedShading::DefferedShadingSharedData::DefferedShadingSharedData()				
{
	iRoot = 0;
	iCamera = 0;
	iWindow = 0;				
	iMainLight = 0;
	iActivate = false;
}

ShareData::DefferedShading::DefferedShadingSharedData::~DefferedShadingSharedData()
{
}


////####################################################

template<> ShareData::GameConfigurations::PlayerConfigurations::GameConfigurationsSharedData* Ogre::Singleton<ShareData::GameConfigurations::PlayerConfigurations::GameConfigurationsSharedData>::msSingleton = 0;
ShareData::GameConfigurations::PlayerConfigurations::GameConfigurationsSharedData* ShareData::GameConfigurations::PlayerConfigurations::GameConfigurationsSharedData::getSingletonPtr(void)
{
	return msSingleton;
}
 
ShareData::GameConfigurations::PlayerConfigurations::GameConfigurationsSharedData& ShareData::GameConfigurations::PlayerConfigurations::GameConfigurationsSharedData::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

ShareData::GameConfigurations::PlayerConfigurations::GameConfigurationsSharedData::GameConfigurationsSharedData()				
{
	iEntityPlayerWalkSpeed = 0;
	iEntityPlayerGlobalInitPositionX = 0;
	iEntityPlayerGlobalInitPositionY = 0;
	iEntityPlayerGlobalInitPositionZ = 0;
	iEntityPlayerArmsMesh = "";
	iEntityPlayerMachineGunMesh = "";
}

ShareData::GameConfigurations::PlayerConfigurations::GameConfigurationsSharedData::~GameConfigurationsSharedData()
{
}

void ShareData::GameConfigurations::PlayerConfigurations::GameConfigurationsSharedData::loadPlayerConfiguration()
{
	// load resource paths from config file
	Ogre::ConfigFile cf;
#ifdef _DEBUG
	cf.load(".\\Resources\\Play\\Configurations\\Player\\PlayerConfig.cfg");
#else
	cf.load(".\\Resources\\Play\\Configurations\\Player\\PlayerConfig.cfg");
#endif	
 
	// go through all settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
 
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements())
	{
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin() ; i != settings->end() ; ++i)
		{
			typeName = i->first;
			archName = i->second;
			
			if(Ogre::StringUtil::match(typeName,"EntityPlayerWalkSpeed",true))
				iEntityPlayerWalkSpeed = Ogre::StringConverter::parseReal(archName);
			else if(Ogre::StringUtil::match(typeName,"EntityPlayerGlobalInitPositionX",true))
				iEntityPlayerGlobalInitPositionX = Ogre::StringConverter::parseReal(archName);
			else if(Ogre::StringUtil::match(typeName,"EntityPlayerGlobalInitPositionY",true))
				iEntityPlayerGlobalInitPositionY = Ogre::StringConverter::parseReal(archName);
			else if(Ogre::StringUtil::match(typeName,"EntityPlayerGlobalInitPositionZ",true))
				iEntityPlayerGlobalInitPositionZ = Ogre::StringConverter::parseReal(archName);
			else if(Ogre::StringUtil::match(typeName,"EntityPlayerArmsMesh",true))
				iEntityPlayerArmsMesh = archName;
			else if(Ogre::StringUtil::match(typeName,"EntityPlayerMachineGunMesh",true))
				iEntityPlayerMachineGunMesh = archName;
			
			//Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}

	//Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup("Essential");
}
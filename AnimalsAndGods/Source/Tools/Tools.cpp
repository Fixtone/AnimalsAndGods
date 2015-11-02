#include "stdafx.h"
#include "../../Header/Tools/Tools.h"

void Tools::Destroy(Ogre::SceneManager* aSceneManager, Ogre::String aSceneNodeName)
{
		if(!aSceneManager->hasSceneNode(aSceneNodeName))
				return;

		Ogre::SceneNode* sceneNode = aSceneManager->getSceneNode(aSceneNodeName);

		Ogre::SceneNode::ChildNodeIterator itn = sceneNode->getChildIterator();

		while(itn.hasMoreElements())
		{
			   Ogre:: SceneNode* node = static_cast<Ogre::SceneNode*>(itn.getNext());

				Destroy(aSceneManager,node->getName());
		}

		Ogre::SceneNode::ObjectIterator ite = sceneNode->getAttachedObjectIterator();
		while (ite.hasMoreElements())
		{
				Ogre::Entity* entity = static_cast<Ogre::Entity*>(ite.getNext());

				sceneNode->detachObject(entity->getName());

				if(aSceneManager->hasEntity(entity->getName()))
						aSceneManager->destroyEntity(entity->getName());
		}               

		Ogre::SceneNode* parentNode = sceneNode->getParentSceneNode();
		
		if(parentNode)
				parentNode->removeAndDestroyChild(sceneNode->getName());
}

void Tools::DestroyLight(Ogre::SceneManager* aSceneManager, Ogre::Light* aLight)
{
	aSceneManager->destroyLight(aLight);
}

bool Tools::fileExists(const Ogre::String& aFilename)
{
	struct stat buf;
	if (stat(aFilename.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}

bool Tools::OrderWayPoints(Ogre::SceneNode* i, Ogre::SceneNode* j)
{
	
	Ogre::StringVector strA = Ogre::StringUtil::split(i->getName(),"#");
	Ogre::StringVector strB = Ogre::StringUtil::split(j->getName(),"#");

	return Ogre::StringConverter::parseUnsignedInt(strA[1])< Ogre::StringConverter::parseUnsignedInt(strB[1]);
}

Ogre::Real Tools::Pulse(float aTime, const float aFrequency, const float aAmplitude) 
{  
	//return 0.5*(1+Ogre::Math::Sin(2 * Ogre::Math::PI * aFrequency * aTime));
	aTime *= aFrequency;
	return   aAmplitude * Ogre::Math::Sin(aTime);
}

Ogre::Entity* Tools::CreateEntity(Ogre::SceneManager* aSceneManager, Ogre::SceneNode* aSceneNode, Ogre::String aEntityName, Ogre::String aResourceGroupName, 
								  Ogre::String aMeshFile, Ogre::String aMaterialFile, bool aCastShadows, bool aHasLODs, int aNumberLODs, 
								  std::vector<Ogre::String> aLODsDistances)
{

	try
	{
		Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load(aMeshFile, aResourceGroupName);
		unsigned short src, dest;		
		if (!mesh->suggestTangentVectorBuildParams(Ogre::VES_TANGENT, src, dest))
			mesh->buildTangentVectors(Ogre::VES_TANGENT, src, dest);	

		if(aHasLODs && !mesh->isLodManual())
		{							
			Ogre::String strLOD;
			for(int index = 0; index < aNumberLODs; index ++)
			{
				strLOD.clear();
				strLOD = Ogre::StringUtil::replaceAll(aMeshFile, ".mesh", "_LOD" +  Ogre::StringConverter::toString(index+1) + ".mesh");
				Ogre::MeshPtr lodMesh = Ogre::MeshManager::getSingleton().load(strLOD, aResourceGroupName);				
				mesh->createManualLodLevel(Ogre::StringConverter::parseReal(aLODsDistances[index]), lodMesh->getName());								
			}		
		}		

		Ogre::Entity* entity = 0;
		entity = aSceneManager->createEntity(aEntityName, mesh);
		entity->setCastShadows(aCastShadows);		
		
		if(!aMaterialFile.empty())
			entity->setMaterialName(aMaterialFile);

		aSceneNode->attachObject(entity);

		return entity;
	}
	catch(Ogre::Exception e)
	{
		return 0;
	}
}

Ogre::Light* Tools::CreateLight(Ogre::SceneManager* aSceneManager, Ogre::String aLightName, Ogre::Light::LightTypes aType, Ogre::Vector3 aPosition, 
								Ogre::Vector3 aDirection, bool aVisible, bool aCastShadows, Ogre::ColourValue aColorDiffuse, Ogre::ColourValue aColorSpecular,
								Ogre::Real aInner, Ogre::Real aOuter, Ogre::Real aFalloff, Ogre::Real aRange, Ogre::Real aConstant, 
								Ogre::Real aLinear, Ogre::Real aQuadratic)
{
	try
	{
		Ogre::Light* tmpLight = aSceneManager->createLight(aLightName);
		tmpLight->setType(aType);		
		tmpLight->setVisible(aVisible);
		tmpLight->setCastShadows(aCastShadows);
		tmpLight->setDiffuseColour(aColorDiffuse);
		tmpLight->setSpecularColour(aColorSpecular);
		tmpLight->setPosition(aPosition);
		tmpLight->setDirection(aDirection);

		switch(aType)
		{
			case Ogre::Light::LT_SPOTLIGHT:
			{
				tmpLight->setSpotlightRange(Ogre::Angle(aInner), Ogre::Angle(aOuter), aFalloff);
				tmpLight->setAttenuation(aRange, aConstant, aLinear, aQuadratic);
				break;
			}
			case Ogre::Light::LT_POINT:
			{
				tmpLight->setAttenuation(aRange, aConstant, aLinear, aQuadratic);
				break;
			}
		};		

		return tmpLight;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[Tools]: " + e.getDescription());
		return false;
	}
}
#include "stdafx.h"
#include "../../Header/GameObject/GameObjectWayPoints/GameObjectWayPointsManager.h"

using namespace GOWP;

template<> GameObjectWayPointsManager* Ogre::Singleton<GameObjectWayPointsManager>::msSingleton = 0;
GameObjectWayPointsManager* GameObjectWayPointsManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
GameObjectWayPointsManager& GameObjectWayPointsManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

GameObjectWayPointsManager::GameObjectWayPointsManager()
{
}

GameObjectWayPointsManager::~GameObjectWayPointsManager()
{
}

void GameObjectWayPointsManager::initialiseGameObjectWayPointsManager(Ogre::SceneManager* aSceneManager)
{
	_SceneManager = aSceneManager;	
}

void GameObjectWayPointsManager::clearGameObjectWayPointsManager()
{
}

void GameObjectWayPointsManager::configureGameObjectWayPointsManager()
{	
}

void GameObjectWayPointsManager::releaseGameObjectWayPointsManager()
{
	std::vector<ShareData::GameConfigurations::GOConfigurations::sWayPointsRoute>::iterator it = _VectorWayPoints.begin();
	for(;it!=_VectorWayPoints.end();it++)
	{
		std::vector<Ogre::SceneNode*>::iterator itWPV = it->mWayPointsVector.begin();
		for(;itWPV!=it->mWayPointsVector.end();itWPV++)
			Tools::Destroy(_SceneManager,(*itWPV)->getName());

		it->mWayPointsVector.clear();

		std::vector<Ogre::SceneNode*>::iterator itWPVDebug = it->mWayPointsVectorDebug.begin();
		for(;itWPVDebug!=it->mWayPointsVectorDebug.end();itWPVDebug++)
			Tools::Destroy(_SceneManager,(*itWPVDebug)->getName());

		it->mWayPointsVectorDebug.clear();

		std::vector<Ogre::SceneNode*>::iterator itWPVLinesDebug = it->mWayPointsVectorLinesDebug.begin();
		for(;itWPVLinesDebug!=it->mWayPointsVectorLinesDebug.end();itWPVLinesDebug++)
			Tools::Destroy(_SceneManager,(*itWPVLinesDebug)->getName());

		it->mWayPointsVectorLinesDebug.clear();

		Tools::Destroy(_SceneManager, it->mWayPointsSceneNodeParent->getName());
	}
	_VectorWayPoints.clear();
}

bool GameObjectWayPointsManager::createGameObjectWayPoints(Ogre::int32 &aGameObjectWorldSGId, Ogre::SceneNode* aGameObjectSceneNodeParent,
														   std::vector<Ogre::SceneNode*> amWayPointsVector, 
														   ShareData::GameConfigurations::LoadersConfigurations::WayPointType aWayPointType,
														   Ogre::String aWayPointsName)
{
	try
	{

		ShareData::GameConfigurations::GOConfigurations::sWayPointsRoute wayPointsRoute;
		wayPointsRoute.mWayPointsSceneNodeParent = aGameObjectSceneNodeParent;
		wayPointsRoute.mWayPointsVector = amWayPointsVector;
		wayPointsRoute.mWayPointType = aWayPointType;
		wayPointsRoute.mWayPointsName = aWayPointsName;
		
		_VectorWayPoints.push_back(wayPointsRoute);

		_buildDebug();

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[GameObjectWayPointsManager]: " + e.getDescription());
		assert(0);
		return false;
	}	
}

bool GameObjectWayPointsManager::update(const float elapsedSeconds)
{
	try
	{		
		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[EntityManager]: " + e.getDescription());
		return false;
	}
}

ShareData::GameConfigurations::GOConfigurations::sWayPointsRoute GameObjectWayPointsManager::GetWayPointsRouteByName(Ogre::String aName)
{
	ShareData::GameConfigurations::GOConfigurations::sWayPointsRoute wayPointsRoute;
	for(std::vector<ShareData::GameConfigurations::GOConfigurations::sWayPointsRoute>::iterator it = _VectorWayPoints.begin(); it!=_VectorWayPoints.end(); it++)
	{
		if(Ogre::StringUtil::match((*it).mWayPointsName,aName))
		{
			wayPointsRoute = *it;
			break;
		}
	}
	return wayPointsRoute;
}

void GameObjectWayPointsManager::showDebug()
{
	for(unsigned int i = 0; i<_VectorWayPoints.size(); i++)
	{
		for(unsigned int j = 0; j<_VectorWayPoints[i].mWayPointsVectorDebug.size(); j++)					
			_VectorWayPoints[i].mWayPointsVectorDebug[j]->setVisible(true);
		
		for(unsigned int j = 0; j<_VectorWayPoints[i].mWayPointsVectorLinesDebug.size(); j++)					
			_VectorWayPoints[i].mWayPointsVectorLinesDebug[j]->setVisible(true);		
	}
}

void GameObjectWayPointsManager::hideDebug()
{
	for(unsigned int i = 0; i<_VectorWayPoints.size(); i++)
	{
		for(unsigned int j = 0; j<_VectorWayPoints[i].mWayPointsVectorDebug.size(); j++)					
			_VectorWayPoints[i].mWayPointsVectorDebug[j]->setVisible(false);
		
		for(unsigned int j = 0; j<_VectorWayPoints[i].mWayPointsVectorLinesDebug.size(); j++)					
			_VectorWayPoints[i].mWayPointsVectorLinesDebug[j]->setVisible(false);		
	}
}

void GameObjectWayPointsManager::_buildDebug()
{
	
	int currentWayRoute = _VectorWayPoints.size()-1;
	for(unsigned int j = 0; j<_VectorWayPoints[currentWayRoute].mWayPointsVector.size(); j++)			
	{
		Ogre::String nameDebugMesh = "sphereMeshWayPoint_DM#" + 
										Ogre::StringConverter::toString(currentWayRoute) + "@" +
										Ogre::StringConverter::toString(j);

		Procedural::SphereGenerator().setRadius(0.25f).setUTile(2).setVTile(2).realizeMesh(nameDebugMesh);
		Ogre::Entity* ent2 = _SceneManager->createEntity(nameDebugMesh);
		Ogre::SceneNode* sn = _SceneManager->getRootSceneNode()->createChildSceneNode();
		sn->attachObject(ent2);
		sn->setPosition(_VectorWayPoints[currentWayRoute].mWayPointsVector[j]->getPosition());
		ent2->setMaterialName("WaypointSphereDebug");
		ent2->setCastShadows(false);			
		sn->setVisible(false);
		_VectorWayPoints[currentWayRoute].mWayPointsVectorDebug.push_back(sn);
	}
	
		
	
	for(unsigned int j = 0; j<_VectorWayPoints[currentWayRoute].mWayPointsVector.size(); j++)			
	{
		if(j>0)
		{
			Ogre::String nameDebugMesh = "lineMeshWayPoint_DL#" + 
											Ogre::StringConverter::toString(currentWayRoute) + "@" +
											Ogre::StringConverter::toString(j);

			Ogre::ManualObject* myManualObject =  _SceneManager->createManualObject(nameDebugMesh); 	
			myManualObject->begin("WaypointLineDebug", Ogre::RenderOperation::OT_LINE_LIST); 
			myManualObject->position(_VectorWayPoints[currentWayRoute].mWayPointsVector[j-1]->getPosition()); 
			myManualObject->position(_VectorWayPoints[currentWayRoute].mWayPointsVector[j]->getPosition()); 
			myManualObject->end(); 
			myManualObject->setCastShadows(false);			

			Ogre::SceneNode* myManualObjectNode = _SceneManager->getRootSceneNode()->createChildSceneNode(nameDebugMesh);  
			myManualObjectNode->attachObject(myManualObject);
			myManualObjectNode->setVisible(false);
			_VectorWayPoints[currentWayRoute].mWayPointsVectorLinesDebug.push_back(myManualObjectNode);

		}		
	}			
		
	Ogre::String nameDebugMesh = "lineMeshWayPoint_DL#" + 
									Ogre::StringConverter::toString(currentWayRoute) + "@" +
									Ogre::StringConverter::toString(_VectorWayPoints[currentWayRoute].mWayPointsVector.size());

	Ogre::ManualObject* myManualObject =  _SceneManager->createManualObject(nameDebugMesh); 	
	myManualObject->begin("WaypointLineDebug", Ogre::RenderOperation::OT_LINE_LIST); 
	myManualObject->position(_VectorWayPoints[currentWayRoute].mWayPointsVector[_VectorWayPoints[currentWayRoute].mWayPointsVector.size()-1]->getPosition()); 
	myManualObject->position(_VectorWayPoints[currentWayRoute].mWayPointsVector[0]->getPosition()); 
	myManualObject->end();  

	Ogre::SceneNode* myManualObjectNode = _SceneManager->getRootSceneNode()->createChildSceneNode(nameDebugMesh);  
	myManualObjectNode->attachObject(myManualObject);
	myManualObjectNode->setVisible(false);
	_VectorWayPoints[currentWayRoute].mWayPointsVectorLinesDebug.push_back(myManualObjectNode);

}
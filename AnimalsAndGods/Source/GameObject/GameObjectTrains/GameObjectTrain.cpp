#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectTrains/GameObjectTrain.h"

GameObjectTrain::GONTrainStates GameObjectTrain::StringToState(Ogre::String string)
{
		const char* str = string.c_str();

		if(strcmp ( "Stop", str ) == 0)			return GameObjectTrain::Stop;
		if(strcmp ( "Run", str) == 0)			return GameObjectTrain::Run;		

		return GameObjectTrain::Stop;
}

GameObjectTrain::GameObjectTrain(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, const Ogre::String &aTrainLightName, 
								 const Ogre::String &aWayPointsRouteName, GameObjectTrain::GONTrainStates aGONTrainState,
								 Ogre::Real aSpeed, Ogre::Real aMinStopTime, Ogre::Real aMaxStopTime)
: GameObjectNode(aGameObjectId, aGONSceneNode)				
, _WayPointsRouteName(aWayPointsRouteName)
, _TrainLightName(aTrainLightName)
, _TrainLight(0)		
, _GONTrainState(aGONTrainState)
, _Direction(Ogre::Vector3::ZERO)
, _Distance(0)
, _DepartureTime(0)
{
	_GameObjectTrainParameters.speed = aSpeed;
	_GameObjectTrainParameters.minStopTime = aMinStopTime;
	_GameObjectTrainParameters.maxStopTime = aMaxStopTime;
}

GameObjectTrain::~GameObjectTrain()
{		
}

void GameObjectTrain::configure()
{	
	_TrainLight = GOL::GameObjectLightManager::getSingletonPtr()->GetGOLTrain(_TrainLightName);
	_TrainLight->mGOLLight->setVisible(false);

	_TrainRoute = GOWP::GameObjectWayPointsManager::getSingletonPtr()->GetWayPointsRouteByName(_WayPointsRouteName);

	unsigned int index = _TrainRoute.mWayPointsVector.size()-1;
	Ogre::SceneNode* sn = _TrainRoute.mWayPointsVector[index];
	_Direction = sn->getPosition() - mGONSceneNode->getPosition();	
	_Direction.normalise();

	_Distance = mGONSceneNode->getPosition().distance(_TrainRoute.mWayPointsVector[_TrainRoute.mWayPointsVector.size()-1]->getPosition());
	_DepartureTime = Ogre::Math::RangeRandom(_GameObjectTrainParameters.minStopTime,_GameObjectTrainParameters.maxStopTime);
};

void GameObjectTrain::release()
{		
};

bool GameObjectTrain::update(const Ogre::Real aElapsedTime)
{
	Ogre::Real move = _GameObjectTrainParameters.speed * aElapsedTime;   

	if(_DepartureTime<=0.0)
	{
		_Distance -= move;		
		if (_Distance <= 0.0)
		{
			_GONTrainState = GameObjectTrain::Stop;
			_Distance = mGONSceneNode->getPosition().distance(_TrainRoute.mWayPointsVector[_TrainRoute.mWayPointsVector.size()-1]->getPosition());
			_DepartureTime = Ogre::Math::RangeRandom(_GameObjectTrainParameters.minStopTime,_GameObjectTrainParameters.maxStopTime);
			mGONSceneNode->setPosition(_TrainRoute.mWayPointsVector[0]->getPosition());
		}
		else
		{
			_GONTrainState = GameObjectTrain::Run;
			mGONSceneNode->translate(move * _Direction);					
		}	
	}
	else
	{
		_DepartureTime -= aElapsedTime;
	}

	return true;
}
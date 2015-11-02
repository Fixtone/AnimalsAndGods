#include "stdafx.h"
#include "../../../Header/GameObject/GameObjectSpaceShips/GameObjectSpaceShip.h"

GameObjectSpaceShip::GONSpaceShipStates GameObjectSpaceShip::StringToState(Ogre::String string)
{
		const char* str = string.c_str();

		if(strcmp	( "Stop", str ) == 0)		return GameObjectSpaceShip::Stop;
		if(strcmp	( "Rotation", str ) == 0)	return GameObjectSpaceShip::Rotation;	
		else									return GameObjectSpaceShip::Fly;
}

GameObjectSpaceShip::GameObjectSpaceShip(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, const Ogre::String &aGOESpaceShipName, const Ogre::String &aSpaceShipNodeTrackAnimationName,
										 const Ogre::String &aSpaceShipWayPointsRouteName, Ogre::Real aSpaceShipSpeed, Ogre::Real aSpaceShipLandMinStopTime,
										 Ogre::Real aSpaceShipLandMaxStopTime, GONSpaceShipStates aGONSpaceShipState)
: GameObjectNode(aGameObjectId, aGONSceneNode)				
, _GOESpaceShipName(aGOESpaceShipName)
, _SpaceShipNodeTrackAnimationName(aSpaceShipNodeTrackAnimationName)
, _WayPointsRouteName(aSpaceShipWayPointsRouteName)
, _GONSpaceShipState(aGONSpaceShipState)
, _Direction(Ogre::Vector3::ZERO)
, _Distance(0)
, _CurrentWaypoint(0)
, _NextWaypoint(1)
, _RotationSlerpProgress(0)
{
	_GONSpaceShipParameters.speed = aSpaceShipSpeed;
	_GONSpaceShipParameters.rotationSpeed = 0.1f;
	_GONSpaceShipParameters.minStopLand = aSpaceShipLandMinStopTime;
	_GONSpaceShipParameters.maxStopLand = aSpaceShipLandMaxStopTime;
}

GameObjectSpaceShip::~GameObjectSpaceShip()
{		
}

void GameObjectSpaceShip::configure()
{
	GameObjectEntity* gOE = GOE::GameObjectEntityManager::getSingletonPtr()->GetGOE(_GOESpaceShipName, ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLD);
	gOE->mGOEEntity->setMaterialName("SS_SpaceShip_25");
	
	_SpaceShipRoute = GOWP::GameObjectWayPointsManager::getSingletonPtr()->GetWayPointsRouteByName(_WayPointsRouteName);

	_Direction = _SpaceShipRoute.mWayPointsVector[_NextWaypoint]->getPosition() - _SpaceShipRoute.mWayPointsVector[_CurrentWaypoint]->getPosition();	
	_Direction.normalise();
	_Distance = mGONSceneNode->getPosition().distance(_SpaceShipRoute.mWayPointsVector[_NextWaypoint]->getPosition());	

	MeshAnimationsLoader* meshAnimLoader;	
	
	meshAnimLoader = new MeshAnimationsLoader();
	_Animations = meshAnimLoader->loadMeshAnimation(mGameObjectId, _SpaceShipNodeTrackAnimationName, "Play",  
													GameManager::getSingletonPtr()->getSceneManager(),
													gOE->mGOESceneNode);

	delete meshAnimLoader;	

	_Animations.mAnimationStates["Idle01"]->setLoop(true);
	_Animations.mAnimationStates["Idle01"]->setEnabled(true);

	_SpaceShipStateCallbackFunc[Stop] = boost::bind(&GameObjectSpaceShip::stateStop, this, _1);
	_SpaceShipStateCallbackFunc[Rotation] = boost::bind(&GameObjectSpaceShip::stateRotation, this, _1);
	_SpaceShipStateCallbackFunc[Fly] = boost::bind(&GameObjectSpaceShip::stateFly, this, _1);

	this->_NextLocation();	
};

void GameObjectSpaceShip::release()
{		
};

bool GameObjectSpaceShip::update(const Ogre::Real aElapsedTime)
{	
	switch(_GONSpaceShipState)
	{
		//Rotation				
		case Rotation:			
		{		
			_RotationSlerpProgress += _GONSpaceShipParameters.rotationSpeed * aElapsedTime;			
			Ogre::Quaternion rotationValue = Ogre::Quaternion::Slerp(_RotationSlerpProgress, _CurrentQuaternion, _NextQuaternion, true);
			mGONSceneNode->setOrientation(rotationValue);
			
			if(mGONSceneNode->getOrientation().equals(_NextQuaternion,Ogre::Radian(0.1f)))
				_GONSpaceShipState = Fly;

			break;
		}
		case Fly:
		{
			Ogre::Real move = _GONSpaceShipParameters.speed * aElapsedTime;
			_Distance -= move;
			mGONSceneNode->translate(move * _Direction);

			if(_Distance <= 0.0)
				this->_NextLocation();

			break;
		}
	};

	_Animations.mAnimationStates["Idle01"]->addTime(aElapsedTime);

	//Ogre::Real move = _GONSpaceShipParameters.speed * aElapsedTime;   	
	//_Distance -= move;	

	//if (_Distance <= 0.0)
	//{		
	//	_NextWaypoint++;
	//	if(_NextWaypoint>_SpaceShipRoute.mWayPointsVector.size()-1)
	//		_NextWaypoint = 0;

	//	_CurrentWaypoint++;
	//	if( _CurrentWaypoint>_SpaceShipRoute.mWayPointsVector.size()-1)
	//		_CurrentWaypoint = 0;
	//	
	//	mGONSceneNode->setFixedYawAxis(true);
	//	_Direction = _SpaceShipRoute.mWayPointsVector[_NextWaypoint]->_getDerivedPosition() - _SpaceShipRoute.mWayPointsVector[_CurrentWaypoint]->_getDerivedPosition();			
	//	Ogre::Real norm = _Direction.normalise();					
	//	
	//	Ogre::Vector3 up_vector = (Ogre::Vector3::UNIT_Y - _Direction.dotProduct(Ogre::Vector3::UNIT_Y)); //this needs to be normal to the direction vector as well as normalised
	//	up_vector.normalise();
	//	
	//	Ogre::Vector3 left_vector = up_vector.crossProduct(_Direction); //since direction and up_vector are orthonormal this vector is also orthonormal to the others; the local x-axes
	//	left_vector.normalise();

	//	Ogre::Quaternion rot_quaternion(left_vector, up_vector, _Direction);
	//	
	//	mGONSceneNode->setOrientation(rot_quaternion);
	//	
	//	_Distance = mGONSceneNode->getPosition().distance(_SpaceShipRoute.mWayPointsVector[_NextWaypoint]->getPosition());			
	//}
	//else
	//{
	//	mGONSceneNode->translate(move * _Direction);					
	//}		

	return true;
}

void GameObjectSpaceShip::stateStop(Ogre::Real aElapsedTime)
{	
}

void GameObjectSpaceShip::stateRotation(Ogre::Real aElapsedTime)
{
}

void GameObjectSpaceShip::stateFly(Ogre::Real aElapsedTime)
{
}

void GameObjectSpaceShip::_NextLocation()
{
	_GONSpaceShipState = Rotation;
	_CurrentQuaternion = mGONSceneNode->getOrientation();
	_NextQuaternion = _SpaceShipRoute.mWayPointsVector[_CurrentWaypoint]->getOrientation();

	Ogre::Degree degCurrent = Ogre::Degree(_CurrentQuaternion.getYaw());
	Ogre::Degree degNext = Ogre::Degree(_NextQuaternion.getYaw());

	_RotationSlerpProgress = 0;   

	_CurrentWaypoint++;
	if(_CurrentWaypoint == _SpaceShipRoute.mWayPointsVector.size())
		_CurrentWaypoint = 0;	

	_NextDistinationPosition = _SpaceShipRoute.mWayPointsVector[_CurrentWaypoint]->getPosition();
	_Direction = _NextDistinationPosition - mGONSceneNode->getPosition();
	_Distance = _Direction.normalise();
}
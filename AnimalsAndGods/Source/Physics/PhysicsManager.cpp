#include "stdafx.h"
#include "../../Header/Physics/PhysicsManager.h"

template<> PhysicsManager* Ogre::Singleton<PhysicsManager>::msSingleton = 0;
PhysicsManager* PhysicsManager::getSingletonPtr(void)
{
	return msSingleton;
}
PhysicsManager& PhysicsManager::getSingleton(void)
{  
	assert( msSingleton );  return ( *msSingleton );  
}

PhysicsManager::PhysicsManager()
: _Pause(false)
{}

PhysicsManager::~PhysicsManager(){}

bool PhysicsManager::InitializePhysicsManager(Ogre::SceneManager* &aSceneManager)
{
	try
	{
		_SceneManager = aSceneManager;

		// Create the world.
		_World = NxOgre::World::createWorld();
		
		// The NxOgre Mesh Manager is responsible for loading and storing all Meshes (Triangle, Convex, Cloth, etc.)
		// - Let's get a copy of it's pointer
		_MeshManager = NxOgre::MeshManager::getSingleton();
		
		return true;
	}
	catch(NxOgre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
	catch(std::exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.what());
		return false;
	}
}

bool PhysicsManager::ClearPhysicsManager()
{
	try
	{
		//Destroy all and visual debugger;
		NxOgre::World::destroyWorld();

		return true;
	}
	catch(NxOgre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
	catch(std::exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.what());
		return false;
	}
}

bool PhysicsManager::createScene()
{
	try
	{
		// Allow NxOgre to use the Ogre resource system, via the Critter OgreResourceProtocol class.
		// - ResourceProtocols are normally owned by the ResourceSystem, so we don't have to delete it later.
		NxOgre::ResourceSystem::getSingleton()->openProtocol(new Critter::OgreResourceProtocol());
  
		// Connect to the Remote Debugger - if there is one.
		_World->getRemoteDebugger()->connect();

		// Create the scene
		NxOgre::SceneDescription scene_description;
		scene_description.mName = "PhysicsScene";
		scene_description.mGravity = NxOgre::Constants::MEAN_EARTH_GRAVITY;
		scene_description.mUseHardware = false;

		_Scene = _World->createScene(scene_description);

		// Set default material properties
		_DefaultMaterial = _Scene->getMaterial(0);
		_DefaultMaterial->setRestitution(0.1f);
		_DefaultMaterial->setDynamicFriction(0.9f);
		_DefaultMaterial->setStaticFriction(0.5f);
		
		// Create the rendersystem.
		_RenderSystem = new Critter::RenderSystem(_Scene, _SceneManager);
		
		_VisualDebugger = _RenderSystem->createVisualDebugger();
		_VisualDebugger->disable();		

		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}

bool PhysicsManager::destroyScene()
{
	try
	{
		_World->destroyScene(_Scene);
		return true;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return false;
	}
}

bool PhysicsManager::updatePhysics(const Ogre::Real aElapsedTime)
{
	if(_Pause)
		_World->advance(0);
	else
		_World->advance(aElapsedTime);

	return true;
}

NxOgre::Scene* PhysicsManager::getScene()
{
	return _Scene;
}

Critter::RenderSystem* PhysicsManager::getPhysicsRenderSystem()
{
	return _RenderSystem;
}

const Critter::AnimatedCharacterDescription PhysicsManager::buildAnimatedCharacterDescription(NxOgre::SimpleCapsule aSimpleCapsule, 
																							  Ogre::Real aMaxGroundSpeed,
																							  Ogre::Real aMaxHeightJumpVelocity)
{
	Critter::AnimatedCharacterDescription desc;
	desc.mShape = aSimpleCapsule;
	desc.mCollisionMask = (ShareData::GameConfigurations::PhysicsConfigurations::Walls) | (ShareData::GameConfigurations::PhysicsConfigurations::Objects);
	desc.mMaxGroundSpeed = aMaxGroundSpeed;
	desc.setJumpVelocityFromMaxHeight(_Scene->getGravity().y, aMaxHeightJumpVelocity);	
	return desc;
}

NxOgre::SceneGeometry* PhysicsManager::buildSceneGeometryEntity(const Ogre::String &aSceneNodeName, const Ogre::Entity* aEntity, const Ogre::String &aEntityMeshFileName,
																const Ogre::Vector3	&aGlobalPosition, const Ogre::Quaternion &aGlobalOrientation)
{
	try
	{
		
			NxOgre::Mesh* sceneGeometryEntityMesh;
			Ogre::String resourcesGroup(Levels::LevelManager::getSingletonPtr()->getGameLevelSceneToLoadString());
			Ogre::String FileName("");
			Ogre::String FileExtension("");
			Ogre::StringUtil::splitBaseFilename(aEntityMeshFileName, FileName, FileExtension);
			FileName.append(".nxs");

			if(!Tools::fileExists("./Resources/" + resourcesGroup + "/Meshes/Physics/" + FileName))
			{
				Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_NORMAL, "Cooking: " + FileName);
					
				NxOgre::MeshData* mesh_data = 0;
				if(aEntity->getMesh()->isLodManual())
				{
					size_t index = aEntity->getNumManualLodLevels();
					Ogre::Entity* entity = aEntity->getManualLodLevel(index-1);
					mesh_data = Critter::MeshFunctions::read(entity->getMesh());
				}
				else
					mesh_data = Critter::MeshFunctions::read(aEntity->getMesh());

				mesh_data->mType = NxOgre::Enums::MeshType_Triangle;
				mesh_data->cook("file://Resources/" + resourcesGroup + "/Meshes/Physics/" + FileName);
				delete mesh_data;
				
				sceneGeometryEntityMesh = NxOgre::MeshManager::getSingleton()->load("file://Resources/" + resourcesGroup + "/Meshes/Physics/" + FileName, FileName);				
			}					
			else	
				sceneGeometryEntityMesh = NxOgre::MeshManager::getSingleton()->load("file://Resources/" + resourcesGroup + "/Meshes/Physics/" + FileName, FileName);				
			
					
		NxOgre::Matrix44 transformSceneGeometryMatrix(aGlobalPosition,aGlobalOrientation);
		
		NxOgre::RigidBodyDescription rigidBodyDesc;
		rigidBodyDesc.mName = aSceneNodeName + "@SceneGeometry";	
		rigidBodyDesc.mGroup = ShareData::GameConfigurations::PhysicsConfigurations::Walls;
		
		NxOgre::TriangleGeometryDescription triangleGeom(sceneGeometryEntityMesh);
		triangleGeom.mGroup = ShareData::GameConfigurations::PhysicsConfigurations::Walls;		
		
		NxOgre::SceneGeometry* scene_geom = _Scene->createSceneGeometry(triangleGeom, transformSceneGeometryMatrix, rigidBodyDesc);
		boost::unordered_map<Ogre::String, NxOgre::SceneGeometry*>::value_type gameObjectSceneGeometry(rigidBodyDesc.mName, scene_geom);
		_MapGameObjectSceneGeometry.insert(gameObjectSceneGeometry);
		
		return _Scene->createSceneGeometry(triangleGeom, transformSceneGeometryMatrix, rigidBodyDesc);
	
	}
	catch(NxOgre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return 0;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return 0;
	}
	catch(std::exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.what());
		return 0;
	}
}

void PhysicsManager::destroySceneGeometry(NxOgre::SceneGeometry* aSceneGeometry)
{
	_Scene->forceDestroySceneGeometry(aSceneGeometry);
}

Critter::Body* PhysicsManager::buildBodyGameObject(const Ogre::String &aSceneBodyName, Ogre::Entity* aEntityBody, 
												   const Ogre::Vector3 &aGlobalPosition, const Ogre::Quaternion &aGlobalOrientation,
												   Ogre::Real aBodyMass)
{
	try
	{	

		NxOgre::Matrix44 transformBodyMatrix(aGlobalPosition,aGlobalOrientation);

		Critter::BodyDescription bodyDescription;
		bodyDescription.mName = aSceneBodyName;		
		bodyDescription.mMass = aBodyMass;				
		bodyDescription.mGroup = ShareData::GameConfigurations::PhysicsConfigurations::Objects;
				
		Ogre::Vector3 meshSize = aEntityBody->getMesh()->getBounds().getSize();
		
		NxOgre::BoxDescription boxDescription(meshSize);				
		NxOgre::Matrix44 localPose(NxOgre::Vec3(0, aEntityBody->getMesh()->getBounds().getSize().y/2,0), NxOgre::Quat::IDENTITY);
		boxDescription.mLocalPose = localPose;				
		
		Critter::Body* body =  _RenderSystem->createBody(boxDescription, transformBodyMatrix, bodyDescription);
		body->getNode()->addEntity(aEntityBody);
		return body;	
	
	}
	catch(NxOgre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return 0;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return 0;
	}
	catch(std::exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.what());
		return 0;
	}
}

NxOgre::SceneGeometry* PhysicsManager::getSceneGeometryByName(const Ogre::String &aName)
{
	NxOgre::SceneGeometry* findSG = 0;
	
	boost::unordered_map<Ogre::String, NxOgre::SceneGeometry*>::const_iterator it = _MapGameObjectSceneGeometry.find(aName);
	if(it!=_MapGameObjectSceneGeometry.end())
		findSG = it->second;

	return findSG;
}

//NxOgre::SceneGeometry* PhysicsManager::MakeSceneGeometryEntityReactive(const Ogre::String &aSceneGeometryEntityMeshName, const Ogre::String &aEntityMeshFileName, const Ogre::String &aSceneGeometryEntityMeshFileName, 
//																	   const NxOgre::Vec3 &aGlobalPosition, const NxOgre::Quat &aGlobalOrientation, bool aCook)
//{
//	try
//	{		
//		NxOgre::Mesh* sceneGeometryEntityMesh;
//
//		if(!NxOgre::MeshManager::getSingleton()->hasMesh(aSceneGeometryEntityMeshFileName))
//		{
//			if(aCook)
//			{				
//				Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_NORMAL, "Cooking: " + aSceneGeometryEntityMeshFileName);
//
//				Ogre::MeshPtr mPtr = Ogre::MeshManager::getSingletonPtr()->getByName(aEntityMeshFileName);
//				NxOgre::MeshData* mesh_data = Critter::MeshFunctions::read(mPtr);
//				mesh_data->mType = NxOgre::Enums::MeshType_Triangle;
//				mesh_data->cook("file://Resources/Play/Meshes/" + aSceneGeometryEntityMeshFileName);
//				delete mesh_data;	
//			}
//
//			sceneGeometryEntityMesh = NxOgre::MeshManager::getSingleton()->load("ogre://Play/" + aSceneGeometryEntityMeshFileName, aSceneGeometryEntityMeshFileName);			
//		}
//		else	
//			sceneGeometryEntityMesh = NxOgre::MeshManager::getSingleton()->getByName(aSceneGeometryEntityMeshFileName);  
//				
//		NxOgre::Matrix44 transformSceneGeometryMatrix(aGlobalPosition,aGlobalOrientation);
//
//		NxOgre::RigidBodyDescription rigidBodyDesc;
//		rigidBodyDesc.mName = aSceneGeometryEntityMeshName;	
//		rigidBodyDesc.mGroup = ShareData::GameConfigurations::PhysicsConfigurations::Walls;
//		
//		NxOgre::SceneGeometry* scene_geom = _Scene->createSceneGeometry(NxOgre::TriangleGeometryDescription(sceneGeometryEntityMesh), transformSceneGeometryMatrix, rigidBodyDesc);		
//		scene_geom->getShape(0)->setId(ShareData::GameConfigurations::LoadersConfigurations::HYDRANTSHAPE);
//
//		_RenderSystem->createSceneNodeEntityPair(aEntityMeshFileName, aGlobalPosition, aGlobalOrientation);
//		return scene_geom;
//	}
//	catch(NxOgre::Exception& e )
//	{
//		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
//		return 0;
//	}
//	catch(Ogre::Exception& e )
//	{
//		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
//		return 0;
//	}
//	catch(std::exception& e )
//	{
//		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.what());
//		return 0;
//	}
//}
//
//Critter::KinematicBody* PhysicsManager::MakeKinematicBody(const Ogre::String& aBodyName, const NxOgre::Real& aBodyMass, const NxOgre::Matrix44& aGlobalPose, const NxOgre::Vec3& aInitialVelocity, 
//														  ShareData::GameConfigurations::LoadersConfigurations::EntityBodyType aBodyType)
//{
//
//	Critter::BodyDescription bodyDescription;
//	bodyDescription.mMass = 0.0001f;
//	bodyDescription.mLinearVelocity = aInitialVelocity;		
//	bodyDescription.mGroup = ShareData::GameConfigurations::PhysicsConfigurations::MGPrimaryBullets;
//
//	Procedural::SphereGenerator().setRadius(0.05f).setUTile(5.).setVTile(5.).realizeMesh(aBodyName);
//	Ogre::Entity* bulletMGPrimaryEntity = _SceneManager->createEntity(aBodyName);
//	NxOgre::BoxDescription boxDescription(bulletMGPrimaryEntity->getMesh()->getBounds().getSize());			
//
//	return _RenderSystem->createKinematicBody(boxDescription, aGlobalPose, bulletMGPrimaryEntity->getMesh()->getName(), bodyDescription);
//}

//Critter::Body* PhysicsManager::MakeBody(const Ogre::String& aBodyName, const Ogre::String& aMeshFile, const Ogre::String& aEnityNxsName, const NxOgre::Real& aBodyMass, const NxOgre::Matrix44& aGlobalPose, const NxOgre::Vec3& aInitialVelocity, ShareData::GameConfigurations::LoadersConfigurations::EntityBodyType aBodyType, bool aCook)
//{
//	try
//	{	
//		switch(aBodyType)
//		{
//			case ShareData::GameConfigurations::LoadersConfigurations::STANDARD:
//			{
//				/*
//				NxOgre::Mesh* bodyEntityMesh;
//				if(!NxOgre::MeshManager::getSingleton()->hasMesh(aEnityNxsName))
//				{
//					if(aCook)
//					{				
//						Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_NORMAL, "Cooking: " + aEnityNxsName);
//					
//						Ogre::MeshPtr mPtr = Ogre::MeshManager::getSingletonPtr()->load("EntityBulletMGPrimary_Mdl.mesh","Play");
//						NxOgre::MeshData* mesh_data = Critter::MeshFunctions::read(mPtr);
//						mesh_data->mType = NxOgre::Enums::MeshType_Convex;
//						mesh_data->cook("file://Resources/Play/Meshes/" + aEnityNxsName);
//						delete mesh_data;	
//					}
//
//					bodyEntityMesh = NxOgre::MeshManager::getSingleton()->load("ogre://Play/"+ aEnityNxsName, aBodyName);
//				}
//				else	
//					bodyEntityMesh = NxOgre::MeshManager::getSingleton()->getByName(aEnityNxsName);  
//			
//				Critter::BodyDescription bodyDescription;
//				bodyDescription.mMass = aBodyMass;
//				bodyDescription.mLinearVelocity = aInitialVelocity;	
//  
//				return _RenderSystem->createBody(NxOgre::ConvexDescription(bodyEntityMesh), aGlobalPose, aMeshFile, bodyDescription);
//				*/
//
//				Critter::BodyDescription bodyDescription;
//				bodyDescription.mMass = 0.4f;
//				bodyDescription.mLinearVelocity = aInitialVelocity;		
//				bodyDescription.mGroup = ShareData::GameConfigurations::PhysicsConfigurations::MGPrimaryBullets;
//				//bodyDescription.
//
//				Procedural::SphereGenerator().setRadius(0.05f).setUTile(5.).setVTile(5.).realizeMesh(aBodyName);
//				Ogre::Entity* bulletMGPrimaryEntity = _SceneManager->createEntity(aBodyName);
//
//				Ogre::Vector3 size(bulletMGPrimaryEntity->getMesh()->getBounds().getSize());				
//				NxOgre::BoxDescription boxDescription(bulletMGPrimaryEntity->getMesh()->getBounds().getSize());				
//				//NxOgre::SphereDescription boxDescription(0.05f);
//				//NxOgre::BoxDescription boxDescription(2,2,2);	
//								
//				Critter::Body*	body = _RenderSystem->createBody(boxDescription, aGlobalPose, bulletMGPrimaryEntity->getMesh()->getName(), bodyDescription);			
//				body->raiseDynamicFlag(NxOgre::DynamicRigidbodyFlags::DisableGravity);		
//
//				return body;
//
//			}
//			break;
//			case ShareData::GameConfigurations::LoadersConfigurations::STREETADDONONE:
//			{
//				Critter::BodyDescription bodyDescription;
//				bodyDescription.mMass = 50;
//				bodyDescription.mForceFieldMaterial = 100;
//				bodyDescription.mLinearVelocity = aInitialVelocity;				
//				Ogre::MeshPtr mPtr = Ogre::MeshManager::getSingletonPtr()->getByName(aMeshFile);
//				Ogre::Vector3 meshSize = mPtr->getBounds().getSize();
//				bodyDescription.mGroup = ShareData::GameConfigurations::PhysicsConfigurations::Objects;
//
//				NxOgre::BoxDescription boxDescription(meshSize);				
//				NxOgre::Matrix44 localPose(NxOgre::Vec3(0,mPtr->getBounds().getSize().y/2,0), NxOgre::Quat::IDENTITY);
//				boxDescription.mLocalPose = localPose;				
//
//				return _RenderSystem->createBody(boxDescription, aGlobalPose, aMeshFile, bodyDescription);  							
//			}
//			break;
//			default:
//			{
//				Critter::BodyDescription bodyDescription;
//				bodyDescription.mMass = aBodyMass;
//				bodyDescription.mLinearVelocity = aInitialVelocity;				
//				Ogre::MeshPtr mPtr = Ogre::MeshManager::getSingletonPtr()->getByName(aMeshFile);
//				Ogre::Vector3 meshSize = mPtr->getBounds().getSize();
//				bodyDescription.mGroup = ShareData::GameConfigurations::PhysicsConfigurations::Walls;
//
//				NxOgre::BoxDescription boxDescription(meshSize);								
//
//				return _RenderSystem->createBody(boxDescription, aGlobalPose, aMeshFile, bodyDescription);  
//			}
//		}
//	}
//	catch(NxOgre::Exception& e )
//	{
//		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
//		return 0;
//	}
//	catch(Ogre::Exception& e )
//	{
//		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
//		return 0;
//	}
//	catch(std::exception& e )
//	{
//		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.what());
//		return 0;
//	}
//}	
//
//Critter::Body* PhysicsManager::makeCameraBody(Ogre::SceneNode* aCameraNode)
//{
//	Ogre::Vector3 cameraNodePosition(aCameraNode->getPosition());
//	Critter::Node* critterCamNode = new Critter::Node(_RenderSystem->getSceneManager(), _RenderSystem);
//	critterCamNode->addSceneNode(aCameraNode);
//	critterCamNode->setPosition(Ogre::Vector3(0,2,10));	
//	
//	Critter::BodyDescription bodyDesc;
//	bodyDesc.mMass = 62.0f;	
//	//bodyDesc.mGroup = Walls;
//	bodyDesc.mAngularDamping = 2;
//	bodyDesc.mLinearDamping = 2;	
//	bodyDesc.mDynamicRigidbodyFlags |= NxOgre::DynamicRigidbodyFlags::FreezeRotation;	
//	//bodyDesc.mDynamicRigidbodyFlags |= NxOgre::DynamicRigidbodyFlags::DisableGravity;	
//	bodyDesc.mNode = critterCamNode;	
//	
//	NxOgre::CapsuleDescription capsuleDesc;
//	capsuleDesc.mRadius = 0.5f;
//	capsuleDesc.mHeight = 4.0f;
//	capsuleDesc.mMass = 62.0f;
//	capsuleDesc.mDensity = 0.0f;	
//	
//	NxOgre::ShapeDescriptions s;	
//	s.push_back(&capsuleDesc);	
//
//	NxOgre::Matrix44 globalPose(NxOgre::Vec3(aCameraNode->getPosition().x,aCameraNode->getPosition().y,aCameraNode->getPosition().z), NxOgre::Quat(aCameraNode->getOrientation()));
//	return _RenderSystem->createBody(s, globalPose,"", bodyDesc);
//}
//
//Critter::KinematicBody* PhysicsManager::makeCameraKinematikBody(Ogre::SceneNode* aPlayerNode)
//{	
//	NxOgre::Matrix44 globalPose(NxOgre::Vec3(aPlayerNode->getPosition().x,aPlayerNode->getPosition().y,aPlayerNode->getPosition().z), NxOgre::Quat(aPlayerNode->getOrientation()));
//	
//	Critter::Node* critterCamNode = new Critter::Node(_RenderSystem->getSceneManager(), _RenderSystem);
//	critterCamNode->setPose(globalPose);
//	aPlayerNode->setPosition(Ogre::Vector3::ZERO);
//	critterCamNode->addSceneNode(aPlayerNode);
//
//	Critter::BodyDescription bodyDescription;
//	bodyDescription.mMass = 62.0f;
//	bodyDescription.mLinearVelocity = NxOgre::Vec3::ZERO;	
//
//	Critter::KinematicBody* cameraKinematikBody = _RenderSystem->createKinematicBody(NxOgre::SphereDescription(0.21f), globalPose, "barrel.mesh", bodyDescription);  
//	//aPlayerNode->setPosition(Ogre::Vector3::ZERO);
//	//cameraKinematikBody->getNode()->addSceneNode(aPlayerNode);
//	return cameraKinematikBody;
//	
//	/*
//	Critter::Node* critterCamNode = new Critter::Node(_RenderSystem->getSceneManager(), _RenderSystem);
//	critterCamNode->setPose(NxOgre::Matrix44(aPlayerNode->_getDerivedPosition(),NxOgre::Quat(aPlayerNode->_getDerivedOrientation().w,
//																							 aPlayerNode->_getDerivedOrientation().x,
//																							 aPlayerNode->_getDerivedOrientation().y,							
//																							 aPlayerNode->_getDerivedOrientation().z)));
//
//	aPlayerNode->setPosition(Ogre::Vector3::ZERO);
//	critterCamNode->addSceneNode(aPlayerNode);
//
//	Critter::BodyDescription bodyDesc;
//	bodyDesc.mMass = 62.0f;
//	//bodyDesc.mDensity = 0.0f;
//	//bodyDesc.mGroup = Walls;
//	//bodyDesc.mAngularDamping = 10;
//	//bodyDesc.mLinearDamping = 10;
//	bodyDesc.mDynamicRigidbodyFlags |= NxOgre::DynamicRigidbodyFlags::FreezeRotation;
//	//bodyDesc.mDynamicRigidbodyFlags |= NxOgre::DynamicRigidbodyFlags::DisableGravity;
//	bodyDesc.mNode = critterCamNode;
//	
//	NxOgre::ShapeDescriptions s;
//
//	NxOgre::CapsuleDescription capsuleDesc;
//	capsuleDesc.mRadius = 0.5f;
//	capsuleDesc.mHeight = 1.5f;
//	capsuleDesc.mMass = 62.0f;
//	//capsuleDesc.mDensity = 0.0f;
//
//	s.push_back(&capsuleDesc);	
//	
//	return _RenderSystem->createKinematicBody(s, NxOgre::Matrix44(aPlayerNode->getPosition(),NxOgre::Quat::IDENTITY), "barrel.mesh", bodyDesc);
//	*/
//}

Critter::AnimatedCharacter* PhysicsManager::makePlayerPhysics(const Ogre::Vector3 &aGlobalPosition, std::vector<Ogre::String> aMeshNameVector)
{

	_RenderSystem->addAnimation("SciFiWeaponArms.mesh", 0, Critter::Enums::StockAnimationID_Idle, "Idle", 5.0f, true);
	_RenderSystem->addAnimation("SciFiWeaponMachineGun.mesh", 0, Critter::Enums::StockAnimationID_Idle, "Idle", 5.0f, true);	

	Critter::AnimatedCharacterDescription desc;
	desc.mShape = NxOgre::SimpleCapsule(0.5f,2);
	desc.mCollisionMask = (ShareData::GameConfigurations::PhysicsConfigurations::Walls) | (ShareData::GameConfigurations::PhysicsConfigurations::Objects << 1);
	desc.mMaxGroundSpeed = 17.0f;
	desc.setJumpVelocityFromMaxHeight(_Scene->getGravity().y, 0.75f);
		
	Critter::Node* critterPlayerSceneNode = new Critter::Node(_RenderSystem->getSceneManager(), _RenderSystem);

	BOOST_FOREACH(std::vector<Ogre::String>::value_type& meshName, aMeshNameVector)	
	{
		critterPlayerSceneNode->createAndAttachEntity(meshName);		
		critterPlayerSceneNode->setScale(Ogre::Vector3(0.06f,0.06f,0.06f));
	}

	//critterCamNode->setPosition(Ogre::Vector3(0,0,0));	

	
	Critter::AnimatedCharacter* animCharacter = _RenderSystem->createAnimatedCharacter(aGlobalPosition, Ogre::Radian(0), "SciFiWeaponArms.mesh", desc);			
	
	return animCharacter;

}

Critter::AnimatedCharacter* PhysicsManager::makePlayerPhysics(const Ogre::Vector3 &aGlobalPosition, Ogre::SceneNode* aScenePlayerNode)
{
	
	// Setup Animations. 	
	//_RenderSystem->addAnimation("SciFiWeaponArms.mesh", 0, Critter::Enums::StockAnimationID_Idle, "Idle");
	//_RenderSystem->addAnimation("SciFiWeaponMachineGun.mesh", 0, Critter::Enums::StockAnimationID_Idle, "Idle");
	
	Critter::AnimatedCharacterDescription desc;
	desc.mShape = NxOgre::SimpleCapsule(0.6f,0.4f);
	desc.mCollisionMask = (ShareData::GameConfigurations::PhysicsConfigurations::Walls) | (ShareData::GameConfigurations::PhysicsConfigurations::Objects << 1);
	desc.mMaxGroundSpeed = 17.0f;
	desc.setJumpVelocityFromMaxHeight(_Scene->getGravity().y, 0.75f);
		
	Critter::Node* critterPlayerSceneNode = new Critter::Node(_RenderSystem->getSceneManager(), _RenderSystem);	
	critterPlayerSceneNode->addSceneNode(aScenePlayerNode);
	
	return _RenderSystem->createAnimatedCharacter(aGlobalPosition, Ogre::Radian(0), critterPlayerSceneNode, desc);

}

void PhysicsManager::ActivePhysicsVisualDebugger(NxOgre::VisualDebuggerDescription aVisualDebuggerDesc)
{	
	_VisualDebugger->loadFromDescription(aVisualDebuggerDesc);
	_VisualDebugger->enable();	
}

void PhysicsManager::DestroyPhysicsVisualDebugger()
{	
	_VisualDebugger->disable();
}

void PhysicsManager::setCallbackFlagsAgainstGroup(Critter::Body* body, unsigned int groupID, unsigned int flags)
{
	Critter::RenderSystem::BodyIterator iter = _RenderSystem->getBodies();

	for(iter;iter !=iter.end();iter++)
	{
		if(iter->getGroup()==groupID)
		{
			_Scene->setActorFlags(body,*iter,flags);
		}
	}
}

void PhysicsManager::setCallbackFlagsAgainstGroup(Critter::KinematicBody* body, unsigned int groupID, unsigned int flags)
{
	Critter::RenderSystem::BodyIterator iter = _RenderSystem->getBodies();

	for(iter;iter !=iter.end();iter++)
	{
		if(iter->getGroup()==groupID)
		{
			_Scene->setActorFlags(body,*iter,flags);
		}
	}
}

bool PhysicsManager::destroyBody(Critter::Body* aBody)
{
	try
	{		
		_RenderSystem->destroyBody(aBody);
		return true;
	}
	catch(NxOgre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return 0;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return 0;
	}
	catch(std::exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.what());
		return 0;
	}
}

bool PhysicsManager::destroyBody(Critter::KinematicBody* aBody)
{
	try
	{		
		_RenderSystem->destroyKinematicBody(aBody);
		return true;
	}
	catch(NxOgre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return 0;
	}
	catch(Ogre::Exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.getDescription());
		return 0;
	}
	catch(std::exception& e )
	{
		Ogre::LogManager::getSingletonPtr()->logMessage(Ogre::LML_CRITICAL, e.what());
		return 0;
	}
}
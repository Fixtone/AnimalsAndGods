#ifndef PhyscisManager_H_
#define PhyscisManager_H_

#include "../../Header/Tools/ShareData.h"

class PhysicsManager : public Ogre::Singleton<PhysicsManager>
{
	public:
			
		PhysicsManager();
		~PhysicsManager();
			
		static PhysicsManager& getSingleton(void);
		static PhysicsManager* getSingletonPtr(void);

		bool InitializePhysicsManager(Ogre::SceneManager* &aSceneManager);
		bool ClearPhysicsManager();

		const Critter::AnimatedCharacterDescription buildAnimatedCharacterDescription(NxOgre::SimpleCapsule aSimpleCapsule, 
																					  Ogre::Real aMaxGroundSpeed,
																					  Ogre::Real aMaxHeightJumpVelocity);

		Critter::AnimatedCharacter* makePlayerPhysics(const Ogre::Vector3 &aGlobalPosition, std::vector<Ogre::String> aMeshNameVector);			
		Critter::AnimatedCharacter* makePlayerPhysics(const Ogre::Vector3 &aGlobalPosition, Ogre::SceneNode* aScenePlayerNode);			

		//Critter::Body* makeCameraBody(Ogre::SceneNode* aCameraNode);
		//Critter::KinematicBody* makeCameraKinematikBody(Ogre::SceneNode* aPlayerNode);			

		NxOgre::SceneGeometry* buildSceneGeometryEntity(const Ogre::String &aSceneNodeName, const Ogre::Entity* aEntity, const Ogre::String &aEntityMeshFileName,
														const Ogre::Vector3	&aGlobalPosition, const Ogre::Quaternion &aGlobalOrientation);		
		void destroySceneGeometry(NxOgre::SceneGeometry* aSceneGeometry);

		Critter::Body* buildBodyGameObject(const Ogre::String &aSceneBodyName, Ogre::Entity* aEntityBody, const Ogre::Vector3	&aGlobalPosition, const Ogre::Quaternion &aGlobalOrientation, Ogre::Real aBodyMass);
		bool destroyBody(Critter::Body* aBody);
		bool destroyBody(Critter::KinematicBody* aBody);

		/*NxOgre::SceneGeometry* PhysicsManager::MakeSceneGeometryEntityReactive(const Ogre::String &aSceneGeometryEntityMeshName, const Ogre::String &aEntityMeshFileName, const Ogre::String &aSceneGeometryEntityMeshFileName, 
																			   const NxOgre::Vec3 &aGlobalPosition, const NxOgre::Quat &aGlobalOrientation, bool aCook);*/

		/*Critter::Body* MakeBody(const Ogre::String& aBodyName, const Ogre::String& aMeshFile, const Ogre::String& aEnityNxsName, 
								const NxOgre::Real& aBodyMass, const NxOgre::Matrix44& aGlobalPose, const NxOgre::Vec3& aInitialVelocity, 
								ShareData::GameConfigurations::LoadersConfigurations::EntityBodyType aBodyType, bool aCook = false);

		Critter::KinematicBody* MakeKinematicBody(const Ogre::String& aBodyName, const NxOgre::Real& aBodyMass, const NxOgre::Matrix44& aGlobalPose, const NxOgre::Vec3& aInitialVelocity, 
												  ShareData::GameConfigurations::LoadersConfigurations::EntityBodyType aBodyType);*/

		bool createScene();
		bool destroyScene();

		

		void ActivePhysicsVisualDebugger(NxOgre::VisualDebuggerDescription aVisualDebuggerDesc);
		void DestroyPhysicsVisualDebugger();			
		
		void setCallbackFlagsAgainstGroup(Critter::Body* body, unsigned int groupID, unsigned int flags);
		void setCallbackFlagsAgainstGroup(Critter::KinematicBody* body, unsigned int groupID, unsigned int flags);

		bool updatePhysics(const Ogre::Real aElapsedTime);

		NxOgre::Scene* getScene();
		Critter::RenderSystem* getPhysicsRenderSystem();

		NxOgre::SceneGeometry* getSceneGeometryByName(const Ogre::String &aName);

		void setPause(){_Pause= true;}

	private:		

		bool					_Pause;
		Ogre::SceneManager*		_SceneManager;
		NxOgre::World*          _World;
		NxOgre::Scene*          _Scene;
		NxOgre::Material*       _DefaultMaterial;
		NxOgre::MeshManager*    _MeshManager;
		NxOgre::VisualDebugger* _VisualDebugger;
		Critter::RenderSystem*  _RenderSystem;		

		typedef boost::unordered_map<Ogre::String, NxOgre::SceneGeometry*> MapGameObjectSceneGeometry;
		MapGameObjectSceneGeometry _MapGameObjectSceneGeometry;
};

#endif
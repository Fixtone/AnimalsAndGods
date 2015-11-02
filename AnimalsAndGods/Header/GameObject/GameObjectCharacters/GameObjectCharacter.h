#ifndef GameObjectCharacter_H
#define GameObjectCharacter_H

class GameObjectCharacter : public NxOgre::CharacterController
						  , public NxOgre::TimeListener
						  , public NxOgre::Callback
{
 
	public: 
		
		/*friend class RenderSystem;*/
  
		//NXOGRE_GC_FRIEND_NEW4
		//NXOGRE_GC_FRIEND_DELETE

		Critter::Node*	getCharacterNode(){return mNode;}

	protected:
  
		GameObjectCharacter(Critter::Node*, Critter::RenderSystem*);
		GameObjectCharacter(Ogre::uint32 aGOCHId, Critter::Node*, Critter::RenderSystem*);
  
		virtual ~GameObjectCharacter();
  
		virtual void advancePhysics(float deltaTime, const NxOgre::Enums::Priority&);
  
		virtual void advanceAnimation(float deltaTime, const NxOgre::Enums::Priority&);
  
		virtual Critter::Enums::CharacterType getType() const;	
  
		bool advance(float deltaTime, const NxOgre::Enums::Priority&, const NxOgre::Enums::SceneFunction&);
  
		Critter::RenderSystem*          mRenderSystem;
		Critter::Node*					mNode;
		NxOgre::Enums::Priority			mPriority;
		Ogre::Radian					mYaw;
		NxOgre::SimpleCapsule			mShape, mAlternateShape;
		bool							mIsUsingAlternateShape;		
		NxOgre::Enums::Axis				mUpDirection;

		Ogre::uint32					mGOCHId;

};

#endif


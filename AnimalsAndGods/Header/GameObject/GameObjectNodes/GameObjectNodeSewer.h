#ifndef GameObjectNodeSewer_H
#define GameObjectNodeSewer_H

class GameObjectNodeSewer : public GameObjectNode
						  , public IClever
{						
	public:		
				
		enum GONSewerStates
		{
			On   = 0,			
			Off  = 1
		};

		GameObjectNodeSewer(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aSewerEntityName, Ogre::String aSewerPUName,
							GONSewerStates aGONSewerState);
 
		virtual ~GameObjectNodeSewer();

		static GameObjectNodeSewer::GONSewerStates StringToGONSewerState(Ogre::String aString);		

		void configure();
		void release();
		bool frameStarted(const Ogre::Real aElapsedTime){return true;}
		bool frameEnded(const Ogre::Real aElapsedTime){return true;}		
		bool update(const Ogre::Real aElapsedTime);
		void updateLogic(lua_State *L, const float elapsedSeconds);

	private:		

		Ogre::String					mSewerEntityName;		
		Ogre::String					mSewerPUName;
		GONSewerStates					mGONSewerState;						
		GameObjectEntity*				mSewerEntity;		
		GameObjectPU*					mGOPUSewer;
		
 };
#endif

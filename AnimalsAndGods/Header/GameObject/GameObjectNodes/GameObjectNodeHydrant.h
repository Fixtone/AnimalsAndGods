#ifndef GameObjectNodeHydrant_H
#define GameObjectNodeHydrant_H

class GameObjectNodeHydrant : public GameObjectNode
						, public IClever
{
	public:

		 /** List of Street Light Types */
		enum GONHydrantStates
		{
			Open    = 0,			
			Close   = 1
		};
		
						
		struct GONHydrantParameters
		{		
			Ogre::uint timeLife;			
		};
		

		GameObjectNodeHydrant(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, Ogre::String aHydrantEntityName, Ogre::String aHydrantLeftPUName,
						  Ogre::String aHydrantRightPUName, GONHydrantStates aGONHydrantState);	

		~GameObjectNodeHydrant();				

		static GameObjectNodeHydrant::GONHydrantStates StringToGONHydrantState(Ogre::String aString);		

		void configure();
		void release();
		bool frameStarted(const Ogre::Real aElapsedTime){return true;}
		bool frameEnded(const Ogre::Real aElapsedTime){return true;}		
		bool update(const Ogre::Real aElapsedTime){return true;}	
		void updateLogic(lua_State *L, const float elapsedSeconds){};

	private:							

		Ogre::String					_HydrantEntityName;		
		Ogre::String					_HydrantLeftPUName;
		Ogre::String					_HydrantRightPUName;

		GameObjectEntity*				_HydrantEntity;		
		GameObjectPU*					_HydrantLeftPU;
		GameObjectPU*					_HydrantRightPU;

		GONHydrantStates				_GONHydrantState;		
		GONHydrantParameters			_GONHydrantParameters;	

};
#endif
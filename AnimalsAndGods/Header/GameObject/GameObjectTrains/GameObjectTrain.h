#ifndef GameObjectTrain_H
#define GameObjectTrain_H

class GameObjectTrain : public GameObjectNode
					  , public IClever 
{
	public:
		
		enum GONTrainStates
		{
			Stop	= 0,
			Run		= 1
		};
				
		struct GameObjectTrainParameters
		{			
			Ogre::Real speed;
			Ogre::Real minStopTime;
			Ogre::Real maxStopTime;			
		};

		GameObjectTrain(Ogre::int32 aGameObjectId, Ogre::SceneNode* aGONSceneNode, const Ogre::String &aTrainLightName, 
						const Ogre::String &aWayPointsRouteName, GameObjectTrain::GONTrainStates aGONTrainState,
						Ogre::Real aSpeed, Ogre::Real aMinStopTime, Ogre::Real aMaxStopTime);

		~GameObjectTrain();		
			
		void configure();
		void release();
		bool frameStarted(const Ogre::Real aElapsedTime){return true;}
		bool frameEnded(const Ogre::Real aElapsedTime){return true;}		
		bool update(const Ogre::Real aElapsedTime);
		void updateLogic(lua_State *L, const float elapsedSeconds){};
		
		static GONTrainStates StringToState (Ogre::String string);

	private:					
				
		Ogre::String														_TrainLightName;
		Ogre::String														_WayPointsRouteName;
		
		GameObjectLight*													_TrainLight;
		ShareData::GameConfigurations::GOConfigurations::sWayPointsRoute	_TrainRoute;

		GONTrainStates														_GONTrainState;	
		GameObjectTrainParameters											_GameObjectTrainParameters;

		Ogre::Vector3														_Direction;
		Ogre::Real															_Distance;
		Ogre::Real															_DepartureTime;

};

#endif
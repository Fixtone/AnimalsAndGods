#ifndef MindManager_H
#define MindManager_H
	 
namespace Mind
{
	class MindManager : public Ogre::Singleton<MindManager>
	{
		public:										

			MindManager();
			~MindManager();		

			static MindManager& getSingleton(void);
			static MindManager* getSingletonPtr(void);

			void initialiseManager();
			void clearManager();		
			
			void configureMind();
			void releaseMind();			

			bool frameStartedMind(const Ogre::Real aElapsedTime);			
			bool frameEndedMind(const Ogre::Real aElapsedTime);

			bool updateMind(const Ogre::Real aElapsedTime);						

			void setGui3DPanelMindThoughts(Gui3D::ScreenPanel* aGui3DPanelMindThoughts);

			bool isFinishThoughts();

		private:						

			std::vector<ShareData::GameConfigurations::GOConfigurations::sMindData>	_MindsData;

			Gui3D::ScreenPanel*											_Gui3DPanelMindThoughts;

			Gui3D::Caption*	_LineOne;
			Gui3D::Caption*	_LineTwo;
			Gui3D::Caption*	_LineThree;

			Ogre::uint32												_ThougtId;
			Ogre::Real													_ThougtBetweenTime;

			bool														_FinishThoughts;
	};
}
#endif
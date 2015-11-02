#ifndef GUI3DManager_H
#define GUI3DManager_H

namespace UI
{
	class GUI3DManager : public Ogre::Singleton<GUI3DManager>
	{
		public:				

			GUI3DManager();
			~GUI3DManager();		

			static GUI3DManager& getSingleton(void);
			static GUI3DManager* getSingletonPtr(void);

			void initializeManager();			
			void clearManager();	

			Gui3D::Gui3D* getGUI3D(){ return _Gui3D; }

		private:

			Ogre::String			_ClassName;

			// Gui3D main object
			Gui3D::Gui3D*			_Gui3D;		
			MyStandardPanelColors	_MyStandardPanelColors;
	};
}
#endif
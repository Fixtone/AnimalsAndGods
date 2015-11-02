#ifndef __MenuLoader_h_
#define __MenuLoader_h_

class MenuLoader
{
		public:					
 
			MenuLoader();
			virtual ~MenuLoader();
 
			ShareData::GameConfigurations::LoadersConfigurations::sMenuData loadMenuConfig(const Ogre::String &aMenuConfig, const Ogre::String &groupName);
			
		private:

			bool																			_PocessMenuConfig(rapidxml::xml_node<>* XMLRoot);			
			void																			_ProcessLanguage(rapidxml::xml_node<>* aElement);			
			std::vector<ShareData::GameConfigurations::LoadersConfigurations::sPageData>	_ProcessPages(rapidxml::xml_node<>* aElement);			
			std::vector<Ogre::String>														_ProcessLines(rapidxml::xml_node<>* aElement);
			
			Ogre::String getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, const Ogre::String &defaultValue = "");
			Ogre::Real getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, Ogre::Real defaultValue = 0);
			bool getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, bool defaultValue = false);
			
			Ogre::String														_sGroupName;			
			ShareData::GameConfigurations::LoadersConfigurations::sMenuData		_MenuData;
				
};

#endif
#ifndef __MindLoader_h_
#define __MindLoader_h_

class MindLoader
{
		public:					
 
			MindLoader();
			virtual ~MindLoader();
 
			ShareData::GameConfigurations::GOConfigurations::sMindData loadMind(const Ogre::String &aMindName, const Ogre::String &groupName);
			
		private:

			bool						_PocessMind(rapidxml::xml_node<>* XMLRoot);			
			void						_ProcessLanguage(rapidxml::xml_node<>* aElement);
			std::vector<Thought*>		_ProcessThoughts(rapidxml::xml_node<>* aElement);
			std::vector<Ogre::String>	_ProcessLines(rapidxml::xml_node<>* aElement);
			
			Ogre::String getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, const Ogre::String &defaultValue = "");
			Ogre::Real getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, Ogre::Real defaultValue = 0);
			bool getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, bool defaultValue = false);
			
			Ogre::String														_sGroupName;			
			ShareData::GameConfigurations::GOConfigurations::sMindData			_MindData;
				
};

#endif
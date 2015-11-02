#include "stdafx.h"
#include "../../Header/Loaders/MindLoader/MindLoader.h"

#pragma warning(disable:4390)
#pragma warning(disable:4305)

MindLoader::MindLoader()
{	
}
 
 
 MindLoader::~MindLoader()
{	
}
 
ShareData::GameConfigurations::GOConfigurations::sMindData MindLoader::loadMind(const Ogre::String &aMindName, const Ogre::String &groupName)
{	
	rapidxml::xml_document<> XMLDoc;    // character type defaults to char
	rapidxml::xml_node<>* XMLRoot;
 
	Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource("PlayerMind.xml", "Play");
	char* mind = strdup(stream->getAsString().c_str());
	XMLDoc.parse<0>(mind);
 
	//// Grab the scene node
	XMLRoot = XMLDoc.first_node("mind");
 
	// Validate the File
	if( getAttrib(XMLRoot, "version", "") == "")
	{
		Ogre::LogManager::getSingleton().logMessage( "[MindLoader] Error: Invalid .xml File. Missing <mind>" );
		delete mind;
	}

	// Process Mind
	Ogre::String version = getAttrib(XMLRoot, "formatVersion", "unknown");
 
	Ogre::String message = "[MindLoader] Parsing mind file with version " + version;	
	if(XMLRoot->first_attribute("name"))
		message += ", name " + Ogre::String(XMLRoot->first_attribute("name")->value());
 
	Ogre::LogManager::getSingleton().logMessage(message);
 
	rapidxml::xml_node<>* pElement;
 
	// Process Animations (?)
	pElement = XMLRoot->first_node("languages");
	if(pElement)
		_ProcessLanguage(pElement);		

	delete mind;	

	return _MindData;
}
 
void MindLoader::_ProcessLanguage(rapidxml::xml_node<>* aElement)
{
	rapidxml::xml_node<>* pElement;			
	pElement = aElement->first_node("language");
	while(pElement)
	{
		Ogre::String languageName = getAttrib(pElement,"value");
		std::vector<Thought*> thoughts;

		rapidxml::xml_node<>*pElementThoughts = pElement->first_node("thoughts");
		if(pElement)			
			thoughts = _ProcessThoughts(pElementThoughts);
		
		boost::unordered_map<Ogre::String, std::vector<Thought*>>::value_type thoughtType(languageName, 
																						  thoughts);
		_MindData.mMind.insert(thoughtType);		
		pElement = pElement->next_sibling("language");
	}
}

std::vector<Thought*> MindLoader::_ProcessThoughts(rapidxml::xml_node<>* aElement)
{
	std::vector<Thought*> thoughts;
		
	rapidxml::xml_node<>* pElement;			
	pElement = aElement->first_node("thought");
	while(pElement)
	{

		Ogre::int32 id = Ogre::StringConverter::parseInt(getAttrib(pElement, "id"));
		Ogre::Real time = Ogre::StringConverter::parseReal(getAttrib(pElement, "time"));
		
		std::vector<Ogre::String> text = _ProcessLines(pElement);
		thoughts.push_back(new Thought(id,text,time));
		pElement = pElement->next_sibling("thought");
	}

	return thoughts;
}

std::vector<Ogre::String> MindLoader::_ProcessLines(rapidxml::xml_node<>* aElement)
{
	std::vector<Ogre::String> text;
		
	rapidxml::xml_node<>* pElement;			
	pElement = aElement->first_node("line");
	while(pElement)
	{		
		Ogre::String encodedString = pElement->value();

		int wchars_num =  MultiByteToWideChar( CP_UTF8 , 0 , encodedString.c_str() , -1, NULL , 0 );
		wchar_t* wstr = new wchar_t[wchars_num];
		MultiByteToWideChar( CP_UTF8 , 0 , encodedString.c_str() , -1, wstr , wchars_num );
		
		std::wstring ws(wstr);
		// your new String
		std::string str(ws.begin(), ws.end());
		text.push_back(str);	
		// do whatever with wstr
		delete[] wstr;

 		pElement = pElement->next_sibling("line");
	}

	return text;
}

Ogre::String MindLoader::getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, const Ogre::String &defaultValue)
{
	if(XMLNode->first_attribute(attrib.c_str()))
		return XMLNode->first_attribute(attrib.c_str())->value();
	else
		return defaultValue;
}
 
Ogre::Real MindLoader::getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, Ogre::Real defaultValue)
{
	if(XMLNode->first_attribute(attrib.c_str()))
		return Ogre::StringConverter::parseReal(XMLNode->first_attribute(attrib.c_str())->value());
	else
		return defaultValue;
}
 
bool MindLoader::getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, bool defaultValue)
{
	if(!XMLNode->first_attribute(attrib.c_str()))
		return defaultValue;
 
	if(Ogre::String(XMLNode->first_attribute(attrib.c_str())->value()) == "true")
		return true;
 
	return false;
}

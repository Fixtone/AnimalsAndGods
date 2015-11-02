#include "stdafx.h"
#include "../../Header/Loaders/MenuLoader/MenuLoader.h"

#pragma warning(disable:4390)
#pragma warning(disable:4305)

MenuLoader::MenuLoader()
{	
}
 
 
 MenuLoader::~MenuLoader()
{	
}
 
ShareData::GameConfigurations::LoadersConfigurations::sMenuData MenuLoader::loadMenuConfig(const Ogre::String &aMenuConfig, const Ogre::String &groupName)
{	
	rapidxml::xml_document<> XMLDoc;    // character type defaults to char
	rapidxml::xml_node<>* XMLRoot;
 
	Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(aMenuConfig, groupName);
	char* mind = strdup(stream->getAsString().c_str());
	XMLDoc.parse<0>(mind);
 
	//// Grab the scene node
	XMLRoot = XMLDoc.first_node("story");
 
	// Validate the File
	if( getAttrib(XMLRoot, "version", "") == "")
	{
		Ogre::LogManager::getSingleton().logMessage( "[MindLoader] Error: Invalid .xml File. Missing <story>" );
		delete mind;
	}

	// Process Mind
	Ogre::String version = getAttrib(XMLRoot, "formatVersion", "unknown");
 
	Ogre::String message = "[MenuLoader] Parsing mind file with version " + version;	
	if(XMLRoot->first_attribute("name"))
		message += ", name " + Ogre::String(XMLRoot->first_attribute("name")->value());
 
	Ogre::LogManager::getSingleton().logMessage(message);
 
	rapidxml::xml_node<>* pElement;
 
	// Process Animations (?)
	pElement = XMLRoot->first_node("languages");
	if(pElement)
		_ProcessLanguage(pElement);		

	delete mind;	

	return _MenuData;
}
 
void MenuLoader::_ProcessLanguage(rapidxml::xml_node<>* aElement)
{
	rapidxml::xml_node<>* pElement;			
	pElement = aElement->first_node("language");
	while(pElement)
	{
		Ogre::String languageName = getAttrib(pElement,"value");
		std::vector<ShareData::GameConfigurations::LoadersConfigurations::sPageData> pages;

		pages = _ProcessPages(pElement);
		
		boost::unordered_map<Ogre::String, std::vector<ShareData::GameConfigurations::LoadersConfigurations::sPageData>>::value_type storyType(languageName, 
																																			   pages);
		_MenuData.mStory.insert(storyType);		

		pElement = pElement->next_sibling("language");
	}
}

std::vector<ShareData::GameConfigurations::LoadersConfigurations::sPageData> MenuLoader::_ProcessPages(rapidxml::xml_node<>* aElement)
{
	rapidxml::xml_node<>* pElement;			
	std::vector<ShareData::GameConfigurations::LoadersConfigurations::sPageData> pages;

	pElement = aElement->first_node("page");
	while(pElement)
	{
		Ogre::String numberPage = getAttrib(pElement,"value");
		std::vector<Ogre::String> textLines;

		ShareData::GameConfigurations::LoadersConfigurations::sPageData pageData;
		pageData.mLines = _ProcessLines(pElement);		
		pageData.mPageNumber = Ogre::StringConverter::parseUnsignedInt(numberPage);
		
		pages.push_back(pageData);

		pElement = pElement->next_sibling("page");
	}

	return pages;
}

std::vector<Ogre::String> MenuLoader::_ProcessLines(rapidxml::xml_node<>* aElement)
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

Ogre::String MenuLoader::getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, const Ogre::String &defaultValue)
{
	if(XMLNode->first_attribute(attrib.c_str()))
		return XMLNode->first_attribute(attrib.c_str())->value();
	else
		return defaultValue;
}
 
Ogre::Real MenuLoader::getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, Ogre::Real defaultValue)
{
	if(XMLNode->first_attribute(attrib.c_str()))
		return Ogre::StringConverter::parseReal(XMLNode->first_attribute(attrib.c_str())->value());
	else
		return defaultValue;
}
 
bool MenuLoader::getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, bool defaultValue)
{
	if(!XMLNode->first_attribute(attrib.c_str()))
		return defaultValue;
 
	if(Ogre::String(XMLNode->first_attribute(attrib.c_str())->value()) == "true")
		return true;
 
	return false;
}

#include "stdafx.h"
#include "../../Header/Loaders/MeshAnimationsLoader/MeshAnimationsLoader.h"

#pragma warning(disable:4390)
#pragma warning(disable:4305)

MeshAnimationsLoader::MeshAnimationsLoader()
: _SceneManager(0)
{	
}
 
 
MeshAnimationsLoader::~MeshAnimationsLoader()
{	
}
 
ShareData::GameConfigurations::GOConfigurations::sAnimationsData MeshAnimationsLoader::loadMeshAnimation(const Ogre::uint32	aGOMeshAnimationId, const Ogre::String &SceneName, const Ogre::String &groupName, Ogre::SceneManager *yourSceneMgr, Ogre::SceneNode *pAttachNode)
{
	// set up shared object values
	_sGroupName = groupName;
	_SceneManager = yourSceneMgr;
	_GOMeshAnimationId = aGOMeshAnimationId;
 
	rapidxml::xml_document<> XMLDoc;    // character type defaults to char
	rapidxml::xml_node<>* XMLRoot;
 
	Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(SceneName, groupName);
	char* scene = strdup(stream->getAsString().c_str());
	XMLDoc.parse<0>(scene);
 
	//// Grab the scene node
	XMLRoot = XMLDoc.first_node("scene");
 
	// Validate the File
	if( getAttrib(XMLRoot, "formatVersion", "") == "")
	{
		Ogre::LogManager::getSingleton().logMessage( "[DotSceneLoader] Error: Invalid .scene File. Missing <scene>" );
		delete scene;
		return _Animations;
	}
 
	//// figure out where to attach any nodes we create
	_AttachNode = pAttachNode;
	if(!_AttachNode)
		_AttachNode = _SceneManager->getRootSceneNode();

	//// Process the scene
	processMeshAnimation(XMLRoot);
 
	delete scene;

	return _Animations;
}
 
void MeshAnimationsLoader::processMeshAnimation(rapidxml::xml_node<>* XMLRoot)
{
	//// Process the scene parameters
	Ogre::String version = getAttrib(XMLRoot, "formatVersion", "unknown");
 
	Ogre::String message = "[MeshAnimationsLoader] Parsing anim file with version " + version;
	if(XMLRoot->first_attribute("ID"))
		message += ", id " + Ogre::String(XMLRoot->first_attribute("ID")->value());
	if(XMLRoot->first_attribute("sceneManager"))
		message += ", scene manager " + Ogre::String(XMLRoot->first_attribute("sceneManager")->value());
	if(XMLRoot->first_attribute("minOgreVersion"))
		message += ", min. Ogre version " + Ogre::String(XMLRoot->first_attribute("minOgreVersion")->value());
	if(XMLRoot->first_attribute("author"))
		message += ", author " + Ogre::String(XMLRoot->first_attribute("author")->value());
 
	Ogre::LogManager::getSingleton().logMessage(message);
 
	rapidxml::xml_node<>* pElement;
 
	// Process Animations (?)
	pElement = XMLRoot->first_node("animations");
	if(pElement)
		processAnimations(pElement);		
}

void MeshAnimationsLoader::processAnimations(rapidxml::xml_node<>* XMLNode)
{
	rapidxml::xml_node<>* pElement;	
	Ogre::uint32 nodeTrackHandle = _GOMeshAnimationId;	
		
	pElement = XMLNode->first_node("animation");
	while(pElement)
	{
		Ogre::String name = getAttrib(pElement,"name");

		Ogre::AnimationState* animationState;		
		animationState = processAnimation(nodeTrackHandle, pElement);
		
		boost::unordered_map<Ogre::String, Ogre::AnimationState*>::value_type animationType(name, 
																						    animationState);
		_Animations.mAnimationStates.insert(animationType);
		pElement = pElement->next_sibling("animation");
		nodeTrackHandle++;
	}
}

Ogre::AnimationState* MeshAnimationsLoader::processAnimation(Ogre::uint32 aNodeTrackHandle, rapidxml::xml_node<>* XMLNode)
{	
	Ogre::String name = "SpaceShip@Handle_" + Ogre::StringConverter::toString(aNodeTrackHandle);
	Ogre::Real animLenght = getAttribReal(XMLNode, "length");

	Ogre::Animation* anim = _SceneManager->createAnimation(name, animLenght);
	anim->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	anim->setRotationInterpolationMode(Ogre::Animation::RIM_LINEAR);

	Ogre::NodeAnimationTrack* nodeTrack = anim->createNodeTrack(aNodeTrackHandle, _AttachNode);
	
	rapidxml::xml_node<>* pElement;
	pElement = XMLNode->first_node("keyframe");
	while(pElement)
	{
		processKeyFrame(pElement, nodeTrack);
		pElement = pElement->next_sibling("keyframe");
	}

	// create a new animation state to track this
	return _SceneManager->createAnimationState(name);	
}

void MeshAnimationsLoader::processKeyFrame(rapidxml::xml_node<>* XMLNode, Ogre::NodeAnimationTrack* pNumTrack)
{
	Ogre::Real time = getAttribReal(XMLNode, "time");
	Ogre::TransformKeyFrame* keyFrame = pNumTrack->createNodeKeyFrame(time);

	rapidxml::xml_node<>* pElement;
	// Process position (?)
	pElement = XMLNode->first_node("translation");
	if(pElement)	
		keyFrame->setTranslate(parseVector3(pElement));
		 
	// Process rotation (?)
	pElement = XMLNode->first_node("rotation");
	if(pElement)
		keyFrame->setRotation(parseQuaternion(pElement));		
 
	// Process scale (?)
	pElement = XMLNode->first_node("scale");
	if(pElement)	
		keyFrame->setScale(parseVector3(pElement));
}


Ogre::String MeshAnimationsLoader::getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, const Ogre::String &defaultValue)
{
	if(XMLNode->first_attribute(attrib.c_str()))
		return XMLNode->first_attribute(attrib.c_str())->value();
	else
		return defaultValue;
}
 
Ogre::Real MeshAnimationsLoader::getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, Ogre::Real defaultValue)
{
	if(XMLNode->first_attribute(attrib.c_str()))
		return Ogre::StringConverter::parseReal(XMLNode->first_attribute(attrib.c_str())->value());
	else
		return defaultValue;
}
 
bool MeshAnimationsLoader::getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, bool defaultValue)
{
	if(!XMLNode->first_attribute(attrib.c_str()))
		return defaultValue;
 
	if(Ogre::String(XMLNode->first_attribute(attrib.c_str())->value()) == "true")
		return true;
 
	return false;
}

Ogre::Vector3 MeshAnimationsLoader::parseVector3(rapidxml::xml_node<>* XMLNode)
{
	return Ogre::Vector3(
		Ogre::StringConverter::parseReal(XMLNode->first_attribute("x")->value()),
		Ogre::StringConverter::parseReal(XMLNode->first_attribute("y")->value()),
		Ogre::StringConverter::parseReal(XMLNode->first_attribute("z")->value())
	);
}
 
Ogre::Quaternion MeshAnimationsLoader::parseQuaternion(rapidxml::xml_node<>* XMLNode)
{
	//! @todo Fix this crap!
 
	Ogre::Quaternion orientation;
 
	if(XMLNode->first_attribute("qx"))
	{
		orientation.x = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qx")->value());
		orientation.y = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qy")->value());
		orientation.z = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qz")->value());
		orientation.w = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qw")->value());
	}
	if(XMLNode->first_attribute("qw"))
	{
		orientation.w = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qw")->value());
		orientation.x = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qx")->value());
		orientation.y = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qy")->value());
		orientation.z = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qz")->value());
	}
	else if(XMLNode->first_attribute("axisX"))
	{
		Ogre::Vector3 axis;
		axis.x = Ogre::StringConverter::parseReal(XMLNode->first_attribute("axisX")->value());
		axis.y = Ogre::StringConverter::parseReal(XMLNode->first_attribute("axisY")->value());
		axis.z = Ogre::StringConverter::parseReal(XMLNode->first_attribute("axisZ")->value());
		Ogre::Real angle = Ogre::StringConverter::parseReal(XMLNode->first_attribute("angle")->value());;
		orientation.FromAngleAxis(Ogre::Angle(angle), axis);
	}
	else if(XMLNode->first_attribute("angleX"))
	{
		Ogre::Vector3 axis;
		axis.x = Ogre::StringConverter::parseReal(XMLNode->first_attribute("angleX")->value());
		axis.y = Ogre::StringConverter::parseReal(XMLNode->first_attribute("angleY")->value());
		axis.z = Ogre::StringConverter::parseReal(XMLNode->first_attribute("angleZ")->value());
		//orientation.FromAxes(&axis);
		//orientation.F
	}
	else if(XMLNode->first_attribute("x"))
	{
		orientation.x = Ogre::StringConverter::parseReal(XMLNode->first_attribute("x")->value());
		orientation.y = Ogre::StringConverter::parseReal(XMLNode->first_attribute("y")->value());
		orientation.z = Ogre::StringConverter::parseReal(XMLNode->first_attribute("z")->value());
		orientation.w = Ogre::StringConverter::parseReal(XMLNode->first_attribute("w")->value());
	}
	else if(XMLNode->first_attribute("w"))
	{
		orientation.w = Ogre::StringConverter::parseReal(XMLNode->first_attribute("w")->value());
		orientation.x = Ogre::StringConverter::parseReal(XMLNode->first_attribute("x")->value());
		orientation.y = Ogre::StringConverter::parseReal(XMLNode->first_attribute("y")->value());
		orientation.z = Ogre::StringConverter::parseReal(XMLNode->first_attribute("z")->value());
	}
 
	return orientation;
}
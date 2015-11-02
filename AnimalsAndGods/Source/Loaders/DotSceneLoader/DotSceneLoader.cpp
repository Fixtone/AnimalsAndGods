#include "stdafx.h"
#include "../../Header/Loaders/DotSceneLoader/DotSceneLoader.h"

#pragma warning(disable:4390)
#pragma warning(disable:4305)
 
 
DotSceneLoader::DotSceneLoader() : mSceneMgr(0), mTerrainGroup(0) 
{
	mTerrainGlobalOptions = OGRE_NEW Ogre::TerrainGlobalOptions();
}
 
 
DotSceneLoader::~DotSceneLoader()
{
	if(mTerrainGroup)
	{
		OGRE_DELETE mTerrainGroup;
	}
 
	OGRE_DELETE mTerrainGlobalOptions;
}
 
void DotSceneLoader::parseDotScene(const Ogre::String &SceneName, const Ogre::String &groupName, Ogre::SceneManager *yourSceneMgr, Ogre::SceneNode *pAttachNode, const Ogre::String &sPrependNode)
{
	// set up shared object values
	m_sGroupName = groupName;
	mSceneMgr = yourSceneMgr;
	m_sPrependNode = sPrependNode;	
 
	rapidxml::xml_document<> XMLDoc;    // character type defaults to char
 
	rapidxml::xml_node<>* XMLRoot;
 
	Ogre::DataStreamPtr stream = Ogre::ResourceGroupManager::getSingleton().openResource(SceneName, groupName );
	char* scene = strdup(stream->getAsString().c_str());
	XMLDoc.parse<0>(scene);
 
	// Grab the scene node
	XMLRoot = XMLDoc.first_node("scene");
 
	// Validate the File
	if( getAttrib(XMLRoot, "formatVersion", "") == "")
	{
		Ogre::LogManager::getSingleton().logMessage( "[DotSceneLoader] Error: Invalid .scene File. Missing <scene>" );
		delete scene;
		return;
	}
 
	// figure out where to attach any nodes we create
	mAttachNode = pAttachNode;
	if(!mAttachNode)
		mAttachNode = mSceneMgr->getRootSceneNode();

	// Process the scene
	processScene(XMLRoot);
 
	delete scene;
}
 
void DotSceneLoader::processScene(rapidxml::xml_node<>* XMLRoot)
{
	// Process the scene parameters
	Ogre::String version = getAttrib(XMLRoot, "formatVersion", "unknown");
 
	Ogre::String message = "[DotSceneLoader] Parsing dotScene file with version " + version;
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
 
	// Process environment (?)
	/*pElement = XMLRoot->first_node("environment");
	if(pElement)
		processEnvironment(pElement);*/
 
	// Process nodes (?)
	pElement = XMLRoot->first_node("nodes");
	if(pElement)
		processNodes(pElement);
 
	// Process externals (?)
	pElement = XMLRoot->first_node("externals");
	if(pElement)
		processExternals(pElement);
 
	// Process userDataReference (?)
	pElement = XMLRoot->first_node("userDataReference");
	if(pElement)
		processUserDataReference(pElement);
 
	// Process octree (?)
	pElement = XMLRoot->first_node("octree");
	if(pElement)
		processOctree(pElement);

	// Process light (?)
	pElement = XMLRoot->first_node("light");
	if(pElement)
	   processLight(pElement);
 
	// Process camera (?)
	pElement = XMLRoot->first_node("camera");
	if(pElement)
		processCamera(pElement);
 
	// Process terrain (?)
	pElement = XMLRoot->first_node("terrain");
	if(pElement)
		processTerrain(pElement);
}
 
void DotSceneLoader::processNodes(rapidxml::xml_node<>* XMLNode)
{
	rapidxml::xml_node<>* pElement;
 
	// Process node (*)
	pElement = XMLNode->first_node("node");
	while(pElement)
	{
		processNode(pElement);
		pElement = pElement->next_sibling("node");
	}
 
	// Process position (?)
	pElement = XMLNode->first_node("position");
	if(pElement)
	{
		mAttachNode->setPosition(parseVector3(pElement));
		mAttachNode->setInitialState();
	}
 
	// Process rotation (?)
	pElement = XMLNode->first_node("rotation");
	if(pElement)
	{
		mAttachNode->setOrientation(parseQuaternion(pElement));
		mAttachNode->setInitialState();
	}
 
	// Process scale (?)
	pElement = XMLNode->first_node("scale");
	if(pElement)
	{
		mAttachNode->setScale(parseVector3(pElement));
		mAttachNode->setInitialState();
	}
}
 
void DotSceneLoader::processExternals(rapidxml::xml_node<>* XMLNode)
{
	//! @todo Implement this
}
 
void DotSceneLoader::processEnvironment(rapidxml::xml_node<>* XMLNode)
{
	rapidxml::xml_node<>* pElement;
 
	// Process camera (?)
	pElement = XMLNode->first_node("camera");
	if(pElement)
		processCamera(pElement);
 
	// Process fog (?)
	pElement = XMLNode->first_node("fog");
	if(pElement)
		processFog(pElement);
 
	// Process skyBox (?)
	pElement = XMLNode->first_node("skyBox");
	if(pElement)
		processSkyBox(pElement);
 
	// Process skyDome (?)
	pElement = XMLNode->first_node("skyDome");
	if(pElement)
		processSkyDome(pElement);
 
	// Process skyPlane (?)
	pElement = XMLNode->first_node("skyPlane");
	if(pElement)
		processSkyPlane(pElement);
 
	// Process clipping (?)
	pElement = XMLNode->first_node("clipping");
	if(pElement)
		processClipping(pElement);
 
	// Process colourAmbient (?)
	pElement = XMLNode->first_node("colourAmbient");
	if(pElement)
		mSceneMgr->setAmbientLight(parseColour(pElement));
 
	// Process colourBackground (?)
	//! @todo Set the background colour of all viewports (RenderWindow has to be provided then)
	pElement = XMLNode->first_node("colourBackground");
	if(pElement)
		;//mSceneMgr->set(parseColour(pElement)); 
 
	// Process userDataReference (?)
	pElement = XMLNode->first_node("userDataReference");
	if(pElement)
		processUserDataReference(pElement);
}
 
void DotSceneLoader::processTerrain(rapidxml::xml_node<>* XMLNode)
{
	Ogre::Real worldSize = getAttribReal(XMLNode, "worldSize");
	int mapSize = Ogre::StringConverter::parseInt(XMLNode->first_attribute("mapSize")->value());
	bool colourmapEnabled = getAttribBool(XMLNode, "colourmapEnabled");
	int colourMapTextureSize = Ogre::StringConverter::parseInt(XMLNode->first_attribute("colourMapTextureSize")->value());
	int compositeMapDistance = Ogre::StringConverter::parseInt(XMLNode->first_attribute("tuningCompositeMapDistance")->value());
	int maxPixelError = Ogre::StringConverter::parseInt(XMLNode->first_attribute("tuningMaxPixelError")->value());
 
	Ogre::Vector3 lightdir(0, -0.3, 0.75);
	lightdir.normalise();
	Ogre::Light* l = mSceneMgr->createLight("tstLight");
	l->setType(Ogre::Light::LT_DIRECTIONAL);
	l->setDirection(lightdir);
	l->setDiffuseColour(Ogre::ColourValue(1.0, 1.0, 1.0));
	l->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.6, 0.6, 0.6));
 
	mTerrainGlobalOptions->setMaxPixelError((Ogre::Real)maxPixelError);
	mTerrainGlobalOptions->setCompositeMapDistance((Ogre::Real)compositeMapDistance);
	mTerrainGlobalOptions->setLightMapDirection(lightdir);
	mTerrainGlobalOptions->setCompositeMapAmbient(mSceneMgr->getAmbientLight());
	mTerrainGlobalOptions->setCompositeMapDiffuse(l->getDiffuseColour());
 
	mTerrainGroup = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, mapSize, worldSize);
	mTerrainGroup->setOrigin(Ogre::Vector3::ZERO);
 
	mTerrainGroup->setResourceGroup("General");
 
	rapidxml::xml_node<>* pElement;
	rapidxml::xml_node<>* pPageElement;
 
	// Process terrain pages (*)
	pElement = XMLNode->first_node("terrainPages");
	if(pElement)
	{
		pPageElement = pElement->first_node("terrainPage");
		while(pPageElement)
		{
			processTerrainPage(pPageElement);
			pPageElement = pPageElement->next_sibling("terrainPage");
		}
	}
	mTerrainGroup->loadAllTerrains(true);
 
	mTerrainGroup->freeTemporaryResources();
	//mTerrain->setPosition(mTerrainPosition);
}
 
void DotSceneLoader::processTerrainPage(rapidxml::xml_node<>* XMLNode)
{
	Ogre::String name = getAttrib(XMLNode, "name");
	int pageX = Ogre::StringConverter::parseInt(XMLNode->first_attribute("pageX")->value());
	int pageY = Ogre::StringConverter::parseInt(XMLNode->first_attribute("pageY")->value());
 
	if (Ogre::ResourceGroupManager::getSingleton().resourceExists(mTerrainGroup->getResourceGroup(), name))
	{
		mTerrainGroup->defineTerrain(pageX, pageY, name);
	}
}
 
void DotSceneLoader::processUserDataReference(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
	//! @todo Implement this

}
 
void DotSceneLoader::processOctree(rapidxml::xml_node<>* XMLNode)
{
	//! @todo Implement this
}
void DotSceneLoader::processLight(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
	// Process attributes	
	Ogre::String name = getAttrib(XMLNode, "name");
	Ogre::String id = getAttrib(XMLNode, "id");

	Ogre::Light::LightTypes lightType;
	Ogre::String sValue = getAttrib(XMLNode, "type");
	if(sValue == "point")
	{		
		lightType = Ogre::Light::LT_POINT;
	}
	else if(sValue == "directional")
	{
		lightType = Ogre::Light::LT_DIRECTIONAL;		
	}
	else if(sValue == "spot")
	{
		lightType = Ogre::Light::LT_SPOTLIGHT;
	}
	else if(sValue == "radPoint")
	{
		lightType = Ogre::Light::LT_POINT;		
	}
 
	bool visible = getAttribBool(XMLNode, "visible", true);
	bool castShadows = getAttribBool(XMLNode, "castShadows", true);

	rapidxml::xml_node<>* pElement;
	// Process position (?)
	Ogre::Vector3 position;
	pElement = XMLNode->first_node("position");
	if(pElement)
	{
		position = parseVector3(pElement);
	}
 
	// Process normal (?)
	Ogre::Vector3 direction;
	pElement = XMLNode->first_node("normal");
	if(pElement)
	{
		direction = parseVector3(pElement);
	}
 
	pElement = XMLNode->first_node("directionVector");
	if(pElement)
	{
		direction = parseVector3(pElement);
	}
 
	// Process colourDiffuse (?)
	Ogre::ColourValue colorDiffuse;
	pElement = XMLNode->first_node("colourDiffuse");
	if(pElement)
		colorDiffuse = parseColour(pElement);
 
	// Process colourSpecular (?)
	Ogre::ColourValue colorSpecular;
	pElement = XMLNode->first_node("colourSpecular");
	if(pElement)
		colorSpecular = parseColour(pElement);	

	Ogre::Real inner = 0;
	Ogre::Real outer = 0;
	Ogre::Real falloff = 0;
	Ogre::Real range = 0;
	Ogre::Real constant = 0;
	Ogre::Real linear = 0;
	Ogre::Real quadratic = 0;
	
	if(lightType != Ogre::Light::LT_DIRECTIONAL)
	{
		// Process lightRange (?)
		pElement = XMLNode->first_node("lightRange");
		if(pElement)
		{
			// Process attributes
			inner = getAttribReal(pElement, "inner");
			outer = getAttribReal(pElement, "outer");
			falloff = getAttribReal(pElement, "falloff", 1.0);
		}
 
		// Process lightAttenuation (?)
		pElement = XMLNode->first_node("lightAttenuation");
		if(pElement)
		{
			// Process attributes
			range = getAttribReal(pElement, "range");
			constant = getAttribReal(pElement, "constant");
			linear = getAttribReal(pElement, "linear");
			quadratic = getAttribReal(pElement, "quadratic");
		}	
	}	
	
	pElement = XMLNode->first_node("userData");
	if(pElement)
		processLightUserData(pElement, pParent, name, Ogre::StringConverter::parseInt(id), lightType, visible, castShadows, position, direction, 
							 colorDiffuse, colorSpecular, inner, outer, falloff, range, constant, linear, quadratic);
}
 
void DotSceneLoader::processCamera(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
	// Process attributes
	Ogre::String name = getAttrib(XMLNode, "name");
	Ogre::String id = getAttrib(XMLNode, "id");
	Ogre::Real fov = getAttribReal(XMLNode, "fov", 45);
	Ogre::Real aspectRatio = getAttribReal(XMLNode, "aspectRatio", 1.3333);
	Ogre::String projectionType = getAttrib(XMLNode, "projectionType", "perspective");
 
	// Create the camera
	Ogre::Camera *pCamera = mSceneMgr->createCamera(name);
 
	//TODO: make a flag or attribute indicating whether or not the camera should be attached to any parent node.
	//if(pParent)
	//    pParent->attachObject(pCamera);
 
	// Set the field-of-view
	//! @todo Is this always in degrees?
	//pCamera->setFOVy(Ogre::Degree(fov));
 
	// Set the aspect ratio
	//pCamera->setAspectRatio(aspectRatio);
 
	// Set the projection type
	if(projectionType == "perspective")
		pCamera->setProjectionType(Ogre::PT_PERSPECTIVE);
	else if(projectionType == "orthographic")
		pCamera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
 
	rapidxml::xml_node<>* pElement;
 
	// Process clipping (?)
	pElement = XMLNode->first_node("clipping");
	if(pElement)
	{
		Ogre::Real nearDist = getAttribReal(pElement, "near");
		pCamera->setNearClipDistance(nearDist);
 
		Ogre::Real farDist =  getAttribReal(pElement, "far");
		pCamera->setFarClipDistance(farDist);
	}
 
	// Process position (?)
	pElement = XMLNode->first_node("position");
	if(pElement)
		pCamera->setPosition(parseVector3(pElement));
 
	// Process rotation (?)
	pElement = XMLNode->first_node("rotation");
	if(pElement)
		pCamera->setOrientation(parseQuaternion(pElement));
 
	// Process normal (?)
	pElement = XMLNode->first_node("normal");
	if(pElement)
		;//!< @todo What to do with this element?
 
	// Process lookTarget (?)
	pElement = XMLNode->first_node("lookTarget");
	if(pElement)
		;//!< @todo Implement the camera look target
 
	// Process trackTarget (?)
	pElement = XMLNode->first_node("trackTarget");
	if(pElement)
		;//!< @todo Implement the camera track target
 
	// Process userDataReference (?)
	pElement = XMLNode->first_node("userDataReference");
	if(pElement)
		;//!< @todo Implement the camera user data reference
 
	// construct a scenenode is no parent
	if(!pParent)
	{
		Ogre::SceneNode* pNode = mAttachNode->createChildSceneNode(name);
		pNode->setPosition(pCamera->getPosition());
		pNode->setOrientation(pCamera->getOrientation());
		pNode->scale(1,1,1);
	}
}
 
void DotSceneLoader::processNode(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
	// Construct the node's name
	Ogre::String name = m_sPrependNode + getAttrib(XMLNode, "name");
 
	// Create the scene node
	Ogre::SceneNode *pNode;
	if(name.empty())
	{
		// Let Ogre choose the name
		if(pParent)
			pNode = pParent->createChildSceneNode();
		else
			pNode = mAttachNode->createChildSceneNode();
	}
	else
	{
		// Provide the name
		if(pParent)
			pNode = pParent->createChildSceneNode(name);
		else
			pNode = mAttachNode->createChildSceneNode(name);
	}
 
	// Process other attributes
	Ogre::int32 id = Ogre::StringConverter::parseInt(getAttrib(XMLNode, "id"));
	bool isTarget = getAttribBool(XMLNode, "isTarget");
 
	rapidxml::xml_node<>* pElement;
 
	// Process position (?)
	pElement = XMLNode->first_node("position");
	if(pElement)
	{
		pNode->setPosition(parseVector3(pElement));
		pNode->setInitialState();
	}
 
	// Process rotation (?)
	pElement = XMLNode->first_node("rotation");
	if(pElement)
	{
		pNode->setOrientation(parseQuaternion(pElement));
		pNode->setInitialState();
	}
 
	// Process scale (?)
	pElement = XMLNode->first_node("scale");
	if(pElement)
	{
		pNode->setScale(parseVector3(pElement));
		pNode->setInitialState();
	}
 
	// Process lookTarget (?)
	pElement = XMLNode->first_node("lookTarget");
	if(pElement)
		processLookTarget(pElement, pNode);
 
	// Process trackTarget (?)
	pElement = XMLNode->first_node("trackTarget");
	if(pElement)
		processTrackTarget(pElement, pNode);	

	// Process node (*)
	pElement = XMLNode->first_node("node");
	while(pElement)
	{
		processNode(pElement, pNode);
		pElement = pElement->next_sibling("node");
	}
 
	// Process entity (*)
	pElement = XMLNode->first_node("entity");
	while(pElement)
	{
		processEntity(pElement, pNode, id);
		pElement = pElement->next_sibling("entity");
	}

#ifndef TESTING
	// Process light (*)
	pElement = XMLNode->first_node("light");
	while(pElement)
	{		
		processLight(pElement, pNode);	
		pElement = pElement->next_sibling("light");
	}
#endif

	// Process camera (*)
	pElement = XMLNode->first_node("camera");
	while(pElement)
	{
		processCamera(pElement, pNode);
		pElement = pElement->next_sibling("camera");
	}
 
	// Process particleSystem (*)
	pElement = XMLNode->first_node("particleSystem");
	while(pElement)
	{
		processParticleSystem(pElement, pNode);
		pElement = pElement->next_sibling("particleSystem");
	}
 
	// Process billboardSet (*)
	pElement = XMLNode->first_node("billboardSet");
	while(pElement)
	{
		processBillboardSet(pElement, pNode);
		pElement = pElement->next_sibling("billboardSet");
	}
 
	// Process plane (*)
	pElement = XMLNode->first_node("plane");
	while(pElement)
	{
		processPlane(pElement, pNode);
		pElement = pElement->next_sibling("plane");
	}	

	// Process userDataReference (?)
	pElement = XMLNode->first_node("userDataReference");
	if(pElement)
		processUserDataReference(pElement, pNode);	

	// Process userDataReference (?)
#ifndef TESTING
	pElement = XMLNode->first_node("userData");
	if(pElement)
		processNodeUserData(pElement, pNode, id);
#endif
}
 
void DotSceneLoader::processLookTarget(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
	//! @todo Is this correct? Cause I don't have a clue actually
 
	// Process attributes
	Ogre::String nodeName = getAttrib(XMLNode, "nodeName");
 
	Ogre::Node::TransformSpace relativeTo = Ogre::Node::TS_PARENT;
	Ogre::String sValue = getAttrib(XMLNode, "relativeTo");
	if(sValue == "local")
		relativeTo = Ogre::Node::TS_LOCAL;
	else if(sValue == "parent")
		relativeTo = Ogre::Node::TS_PARENT;
	else if(sValue == "world")
		relativeTo = Ogre::Node::TS_WORLD;
 
	rapidxml::xml_node<>* pElement;
 
	// Process position (?)
	Ogre::Vector3 position;
	pElement = XMLNode->first_node("position");
	if(pElement)
		position = parseVector3(pElement);
 
	// Process localDirection (?)
	Ogre::Vector3 localDirection = Ogre::Vector3::NEGATIVE_UNIT_Z;
	pElement = XMLNode->first_node("localDirection");
	if(pElement)
		localDirection = parseVector3(pElement);
 
	// Setup the look target
	try
	{
		if(!nodeName.empty())
		{
			Ogre::SceneNode *pLookNode = mSceneMgr->getSceneNode(nodeName);
			position = pLookNode->_getDerivedPosition();
		}
 
		pParent->lookAt(position, relativeTo, localDirection);
	}
	catch(Ogre::Exception &/*e*/)
	{
		Ogre::LogManager::getSingleton().logMessage("[DotSceneLoader] Error processing a look target!");
	}
}
 
void DotSceneLoader::processTrackTarget(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
	// Process attributes
	Ogre::String nodeName = getAttrib(XMLNode, "nodeName");
 
	rapidxml::xml_node<>* pElement;
 
	// Process localDirection (?)
	Ogre::Vector3 localDirection = Ogre::Vector3::NEGATIVE_UNIT_Z;
	pElement = XMLNode->first_node("localDirection");
	if(pElement)
		localDirection = parseVector3(pElement);
 
	// Process offset (?)
	Ogre::Vector3 offset = Ogre::Vector3::ZERO;
	pElement = XMLNode->first_node("offset");
	if(pElement)
		offset = parseVector3(pElement);
 
	// Setup the track target
	try
	{
		Ogre::SceneNode *pTrackNode = mSceneMgr->getSceneNode(nodeName);
		pParent->setAutoTracking(true, pTrackNode, localDirection, offset);
	}
	catch(Ogre::Exception &/*e*/)
	{
		Ogre::LogManager::getSingleton().logMessage("[DotSceneLoader] Error processing a track target!");
	}
}
 
bool DotSceneLoader::fileExists(const Ogre::String& aFilename)
{
	struct stat buf;
	if (stat(aFilename.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}	

void DotSceneLoader::processEntity(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent, Ogre::int32 aId)
{
	// Process attributes
	Ogre::String name = getAttrib(XMLNode, "name");
	Ogre::int32 id = aId;
	Ogre::String meshFile = getAttrib(XMLNode, "meshFile");
	Ogre::String materialFile = getAttrib(XMLNode, "materialFile");
	bool isStatic = getAttribBool(XMLNode, "static", false);;
	bool castShadows = getAttribBool(XMLNode, "castShadows", true);	
  
	rapidxml::xml_node<>* pElement;
 
	// Process vertexBuffer (?)
	pElement = XMLNode->first_node("userData");
	if(pElement)
	{
		nodeProperties.clear();
		processNodeEntityUserData(pElement,pParent);
	}	

	//<userData>
	//    <property type="7" name="GameObjectEntityType" data="1" />
	//    <property type="7" name="GameObjectEntityPhysicsType" data="1" />
	//    <property type="12" name="HasLOD" data="true" />
	//    <property type="2" name="NumberLODs" data="2" />
	//    <property type="7" name="DistanceLODs" data="40#80" />
	//</userData>
	switch(Ogre::StringConverter::parseInt(getProperty("Property", "GameObjectEntityType")))
	{
		case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC:
		{			
				bool HasLODs = Ogre::StringConverter::parseBool(getProperty("Property", "HasLOD"));
				Ogre::String distanceLODs = getProperty("Property", "DistanceLODs");
				std::vector<Ogre::String> tokens; 
				_mySplit(tokens,distanceLODs,'#');						
				int numberLods = Ogre::StringConverter::parseInt((getProperty("Property", "NumberLODs")));
			
				GOE::GameObjectEntityManager::getSingletonPtr()->createGOE(id, ShareData::GameConfigurations::PhysicsConfigurations::GOEPT_SCENEGEOMETRY,
																		   ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDSTATIC,
																		   pParent, meshFile, materialFile, castShadows, HasLODs, numberLods, tokens);	

			break;
		}

		case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDMOVABLE:
		{			
			//#Has Lods
			bool HasLODs = Ogre::StringConverter::parseBool(getProperty("Property", "HasLOD"));
			
			//#Distance of Lods
			Ogre::String distanceLODs = getProperty("Property", "DistanceLODs");
			std::vector<Ogre::String> tokens; 
			_mySplit(tokens,distanceLODs,'#');						
			
			//#Number of lods
			int numberLods = Ogre::StringConverter::parseInt((getProperty("Property", "NumberLODs")));

			//#Mass of worldMovable
			Ogre::Real mass = Ogre::StringConverter::parseReal((getProperty("Property", "BodyMass")));
			
			GOE::GameObjectEntityManager::getSingletonPtr()->createGOE(id, ShareData::GameConfigurations::PhysicsConfigurations::GOEPT_BODY,
																	   ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLDMOVABLE,
																	   pParent, meshFile, materialFile, castShadows, HasLODs, numberLods, tokens,
																	   mass);

			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLD:
		{			
			bool HasLODs = Ogre::StringConverter::parseBool(getProperty("Property", "HasLOD"));
			Ogre::String distanceLODs = getProperty("Property", "DistanceLODs");
			std::vector<Ogre::String> tokens; 
			_mySplit(tokens,distanceLODs,'#');						
			int numberLods = Ogre::StringConverter::parseInt((getProperty("Property", "NumberLODs")));
			
			GOE::GameObjectEntityManager::getSingletonPtr()->createGOE(id, ShareData::GameConfigurations::PhysicsConfigurations::GOEPT_NONE,
																		ShareData::GameConfigurations::LoadersConfigurations::GOE_WORLD,
																		pParent, meshFile, materialFile, castShadows, HasLODs, numberLods, tokens);
		
			break;
		}
	};
	//pEntity = this->_createEntity(pParent,name,meshFile,materialFile, castShadows, true);
	//switch(Ogre::StringConverter::parseInt(getProperty("Property", "EntityType")))
	//{
	//	/*
	//	case ShareData::GameConfigurations::LoadersConfigurations::E_WORLD:
	//	{
	//		pEntity = this->_createEntity(pParent,name,meshFile,materialFile, castShadows, true);
	//		break;
	//	}
	//	case ShareData::GameConfigurations::LoadersConfigurations::E_WORLDSCENEGEOMETRY:
	//	{
	//		pEntity = this->_createEntity(pParent,name,meshFile,materialFile, castShadows, true);
	//		GO::GameObjectManager::getSingletonPtr()->createGameObjectWorldSceneGeometry(id, pParent, pEntity, meshFile, isStatic, castShadows);

	//		break;
	//	}
	//	*/
	//	default:
	//	{
	//		pEntity = this->_createEntity(pParent,name,meshFile,materialFile, castShadows, true);
	//		//GO::GameObjectManager::getSingletonPtr()->createGameObjectWorld(id,pParent,isStatic,castShadows);
	//		//Ogre::LogManager::getSingleton().logMessage("[DotSceneLoader] Warning loading! not EntityType:" + name);
	//	}
	//};	

	
	nodeProperties.clear();
	// Process userDataReference (?)
	//pElement = XMLNode->first_node("userDataReference");
	//if(pElement)
	//	processUserDataReference(pElement, pEntity);
}

void DotSceneLoader::processLightUserData(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent, Ogre::String aLightName, Ogre::int32 aNodeId, Ogre::Light::LightTypes aType, bool aVisible,
										  bool aCastShadows, Ogre::Vector3 aPosition, Ogre::Vector3 aDirection, Ogre::ColourValue aColorDiffuse, Ogre::ColourValue aColorSpecular,
										  Ogre::Real aInner, Ogre::Real aOuter, Ogre::Real aFalloff, Ogre::Real aRange, Ogre::Real aConstant, 
										  Ogre::Real aLinear, Ogre::Real aQuadratic)
{
	rapidxml::xml_node<>* pElement;
	pElement = XMLNode->first_node("property");
	if(pElement)
	{
		while(pElement)
		{
			processUserDataProperty(pElement);
			pElement = pElement->next_sibling("property");
		}
	}	

	Ogre::Light* pLight = Tools::CreateLight(mSceneMgr, aLightName, aType, aPosition, aDirection, aVisible, aCastShadows, aColorDiffuse, aColorSpecular,
											 aInner, aOuter, aFalloff, aRange, aConstant, aLinear, aQuadratic);	

	switch(Ogre::StringConverter::parseInt(getProperty("Property", "GameObjectLightType")))
	{	
		case ShareData::GameConfigurations::LoadersConfigurations::GOL_AMBIENT:
		{
			/*<userData>
				<property type="7" name="GameObjectLightType" data="0" />
			</userData>*/						
			GOL::GameObjectLightManager::getSingletonPtr()->createGOLight(aNodeId,ShareData::GameConfigurations::LoadersConfigurations::GOL_FARAMBIENT,
																		  pParent, pLight);
			break;
		}	
		case ShareData::GameConfigurations::LoadersConfigurations::GOL_FARAMBIENT:
		{
			/*<userData>
				<property type="7" name="GameObjectLightType" data="0" />
			</userData>*/
			GOL::GameObjectLightManager::getSingletonPtr()->createGOLight(aNodeId,ShareData::GameConfigurations::LoadersConfigurations::GOL_FARAMBIENT,
																		  pParent, pLight);
			break;
		}	
		case ShareData::GameConfigurations::LoadersConfigurations::GOL_STREETLIGHT:
		{
			/*<userData>
				 <property type="7" name="GameObjectLightType" data="2" />
			</userData>*/
			GOL::GameObjectLightManager::getSingletonPtr()->createGOLight(aNodeId,ShareData::GameConfigurations::LoadersConfigurations::GOL_STREETLIGHT,
																		  pParent, pLight);
			break;
		}	
		case ShareData::GameConfigurations::LoadersConfigurations::GOL_TRAIN:
		{
			/*<userData>
					<property type="7" name="GameObjectLightType" data="3" />
			</userData>*/
			GOL::GameObjectLightManager::getSingletonPtr()->createGOLight(aNodeId,ShareData::GameConfigurations::LoadersConfigurations::GOL_TRAIN,
																		  pParent, pLight);
			break;
		}	
	};

	nodeProperties.clear();
}

 
void DotSceneLoader::processNodeUserData(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent, Ogre::int32 aNodeId)
{
	rapidxml::xml_node<>* pElement;
	pElement = XMLNode->first_node("property");
	if(pElement)
	{
		while(pElement)
		{
			processUserDataProperty(pElement);
			pElement = pElement->next_sibling("property");
		}
	}	

	switch(Ogre::StringConverter::parseInt(getProperty("Property", "GameObjectNodeType")))
	{
		case ShareData::GameConfigurations::LoadersConfigurations::GON_LIGHTER:
		{
			/*<userData>
				<property type="7" name="GameObjectNodeType" data="1" />
				<property type="7" name="PanelInfoName" data="Streetlight1#0" />
				<property type="7" name="PanelInfoState" data="OnInfo" />
				<property type="7" name="PedrastianLighterName" data="Streetlight2#0" />
				<property type="7" name="PedrastianLighterState" data="OnPedrastiansLight" />
				<property type="7" name="CarLighterName" data="Streetlight5#0" />
				<property type="7" name="CarLighterState" data="GreenLight" />
			</userData>*/
			GON::GameObjectNodeManager::getSingletonPtr()->createGONLighter(aNodeId, 
																			pParent,
																			getProperty("Property", "PanelInfoName"),																			
																			getProperty("Property", "CarLighterName"),																			
																			getProperty("Property", "PedrastianLighterName"),
																			GameObjectNodeLighter::StringToGONLighterStates(getProperty("Property", "GONLighterState")));
			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GON_STREETLIGHT:
		{
			/*<userData>
				<property type="7" name="GameObjectNodeType" data="2" />
				<property type="7" name="LightName" data="Light#67" />
				<property type="7" name="StreetLightName" data="StreetLight1#16" />
				<property type="7" name="GONStreetLightState" data="On" />
			</userData>*/
			GON::GameObjectNodeManager::getSingletonPtr()->createGONStreetLight(aNodeId, 
																				pParent,
																				getProperty("Property", "LightName"),																			
																				getProperty("Property", "StreetLightName"),		
																				GameObjectNodeStreetLight::StringToGONStreetLightState(getProperty("Property", "GONStreetLightState")));
			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GON_PU:
		{
			/*<userData>
				<property type="7" name="GameObjectNodeType" data="3" />
				<property type="7" name="PUScriptName" data="RedSmokeSewer" />
			</userData>*/
			GOPS::GameObjectParticleSystemsManager::getSingletonPtr()->createGOPSParticleUnivers(aNodeId, 
																								 pParent,
																								 getProperty("Property", "PUScriptName"));
			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GON_SEWER:
		{
			/*<userData>
				<property type="7" name="GameObjectNodeType" data="4" />
				<property type="7" name="SewerEntityName" data="Sewer2#0" />
				<property type="7" name="SewerPUName" data="Sewer2PU#0" />
				<property type="7" name="GONSewerState" data="On" />
			</userData>*/
			GON::GameObjectNodeManager::getSingletonPtr()->createGONSewer(aNodeId, 
																		pParent,
																		getProperty("Property", "SewerEntityName"),																			
																		getProperty("Property", "SewerPUName"),																			
																		GameObjectNodeSewer::StringToGONSewerState(getProperty("Property", "GONSewerState")));
			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GON_HYDRANT:
		{
			/*<userData>
				<property type="7" name="GameObjectNodeType" data="9" />
				<property type="7" name="HydrantEntityName" data="Hydrant1#0" />
				<property type="7" name="HydrantLeftPUName" data="Hydrant1PUNode#0" />
				<property type="7" name="HydrantRightPUName" data="Hydrant1PUNode#1" />
				<property type="7" name="HydrantState" data="Close" />
			</userData>*/
			GON::GameObjectNodeManager::getSingletonPtr()->createGONHydrant(aNodeId, 
																			pParent,
																			getProperty("Property", "HydrantEntityName"),																			
																			getProperty("Property", "HydrantLeftPUName"),
																			getProperty("Property", "HydrantRightPUName"),
																			GameObjectNodeHydrant::StringToGONHydrantState(getProperty("Property", "HydrantState")));
			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GON_FLOORSIGN:
		{
			/*
			<userData>
				<property type="7" name="GameObjectNodeType" data="5" />
				<property type="7" name="FloorSignEntityName" data="Billboard_frame1#0" />
				<property type="7" name="FloorSignBackEntityName" data="Billboard_bckg1#0" />
				<property type="7" name="FloorSignFrontEntityName" data="Billboard_bckg1#1" />
				<property type="2" name="GONFloorSignState" data="0" />
			</userData>
			*/
			GON::GameObjectNodeManager::getSingletonPtr()->createGONFloorSign(aNodeId, 
																			  pParent,
																			  getProperty("Property", "FloorSignEntityName"),																			
																			  getProperty("Property", "FloorSignBackEntityName"),																			
																			  getProperty("Property", "FloorSignFrontEntityName"),
																			  GameObjectNodeFloorSign::StringToGONFloorSignState(getProperty("Property", "GONFloorSignState")));
			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GON_ADDON_ONE:
		{
			 /* <userData>
				<property type="7" name="GameObjectNodeType" data="6" />
				<property type="7" name="AddonOneEntityName" data="Street_Addon1#0" />				
				<property type="7" name="AddonOneState" data="On" />
			</userData>*/
			GON::GameObjectNodeManager::getSingletonPtr()->createGONStreetAddonOne(aNodeId, 
																				   pParent,
																				   getProperty("Property", "AddonOneEntityName"),																																							   
																				   GameObjectNodeStreetAddonOne::StringToGONStreetAddonOneState(getProperty("Property", "AddonOneState")));
			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GON_ADDON_TWO:
		{
			 /*<userData>
				<property type="7" name="GameObjectNodeType" data="7" />
				<property type="7" name="StreetAddonTwoEntityName" data="Street_Addon2#9" />
				<property type="7" name="StreetAddonTwoState" data="On" />
			   </userData>*/
			GON::GameObjectNodeManager::getSingletonPtr()->createGONStreetAddonTwo(aNodeId, 
																				   pParent,
																				   getProperty("Property", "StreetAddonTwoEntityName"),			
																				   GameObjectNodeStreetAddonTwo::StringToGONStreetAddonTwoState(getProperty("Property", "StreetAddonTwoState")));
			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GON_ADDON_THREE:
		{
			 /*<userData>
				<property type="7" name="GameObjectNodeType" data="8" />
				<property type="7" name="AddonThreeEntityName" data="Street_Addon3#0" />				
				<property type="7" name="AddonThreeState" data="0" />
			</userData>*/
			GON::GameObjectNodeManager::getSingletonPtr()->createGONStreetAddonThree(aNodeId, 
																					 pParent,
																					 getProperty("Property", "AddonThreeEntityName"),																																								 
																					 GameObjectNodeStreetAddonThree::StringToGONStreetAddonThreeState(getProperty("Property", "AddonThreeState")));
			break;
		}		
		case ShareData::GameConfigurations::LoadersConfigurations::GON_WAYPOINT:
		{
			Ogre::Node::ChildNodeIterator it = pParent->getChildIterator();
			
			std::vector<Ogre::SceneNode*> wayPoints;
			while(it.hasMoreElements())			
				wayPoints.push_back(dynamic_cast<Ogre::SceneNode*>(it.getNext()));

			std::sort(wayPoints.begin(),wayPoints.end(), Tools::OrderWayPoints);

			ShareData::GameConfigurations::LoadersConfigurations::WayPointType wPType;
			switch(Ogre::StringConverter::parseInt(getProperty("Property", "WayPointType")))
			{
				case ShareData::GameConfigurations::LoadersConfigurations::WP_TRAIN:
				{
					wPType = ShareData::GameConfigurations::LoadersConfigurations::WP_TRAIN;
					break;
				}
				case ShareData::GameConfigurations::LoadersConfigurations::WP_DROID:
				{
					wPType = ShareData::GameConfigurations::LoadersConfigurations::WP_DROID;
					break;
				}
				case ShareData::GameConfigurations::LoadersConfigurations::WP_CAMERA:
				{
					wPType = ShareData::GameConfigurations::LoadersConfigurations::WP_CAMERA;
					break;
				}
				default:
				{
					wPType = ShareData::GameConfigurations::LoadersConfigurations::WP_TRAIN;
				}
			};

			GOWP::GameObjectWayPointsManager::getSingletonPtr()->createGameObjectWayPoints(aNodeId,pParent,wayPoints,wPType,pParent->getName());

			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GON_TRAIN:
		{
			/*<userData>
				<property type="7" name="GameObjectNodeType" data="11" />
				<property type="7" name="TrainLightName" data="Light#24" />
				<property type="7" name="TrainWayPointsRouteName" data="WayPointsTrainNode#0" />
				<property type="6" name="Speed" data="100" />
				<property type="6" name="MinStopTime" data="10" />
				<property type="6" name="MaxStopTime" data="20" />
				<property type="7" name="GONTrainState" data="Stop" />
			</userData>*/
			GOT::GameObjectTrainsManager::getSingletonPtr()->createGONTrain(aNodeId, 
																			pParent,
																			getProperty("Property", "TrainLightName"),
																			getProperty("Property", "TrainWayPointsRouteName"),
																			GameObjectTrain::StringToState(getProperty("Property", "GONTrainState")),
																			Ogre::StringConverter::parseReal(getProperty("Property", "Speed")),
																			Ogre::StringConverter::parseReal(getProperty("Property", "MinStopTime")),
																			Ogre::StringConverter::parseReal(getProperty("Property", "MaxStopTime")));

																					 
			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GON_SPACESHIP:
		{
			/*<userData>
				<property type="7" name="GameObjectNodeType" data="12" />
				<property type="7" name="GOESpaceShipName" data="SpaceShip#0" />
				<property type="7" name="SpaceShipNodeTrackAnimationName" data="SpaceShip.animation" />
				<property type="7" name="SpaceShipWayPointsRouteName" data="WayPointsDroidNode#0" />
				<property type="6" name="SpaceShipSpeed" data="100" />
				<property type="6" name="SpaceShipLandMinStopTime" data="10" />
				<property type="6" name="SpaceShipLandMaxStopTime" data="20" />
				<property type="7" name="GONSpaceShipState" data="Stop" />
			</userData>*/
			GOSS::GameObjectSpaceShipsManager::getSingletonPtr()->createGONSpaceShip(aNodeId,
																					 pParent,
																					 getProperty("Property", "GOESpaceShipName"),
																					 getProperty("Property", "SpaceShipNodeTrackAnimationName"),
																					 getProperty("Property", "SpaceShipWayPointsRouteName"),																					
																					 Ogre::StringConverter::parseReal(getProperty("Property", "SpaceShipSpeed")),
																					 Ogre::StringConverter::parseReal(getProperty("Property", "SpaceShipLandMinStopTime")),
																					 Ogre::StringConverter::parseReal(getProperty("Property", "SpaceShipLandMaxStopTime")),
																					 GameObjectSpaceShip::StringToState(getProperty("Property", "GONSpaceShipState")));
																					 
			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GOCH_PLAYER:
		{
			/*<userData>
				<property type="7" name="GameObjectNodeType" data="100" />
				<property type="7" name="PlayerCameraNodeName" data="PlayerCameraNode#0" />
			</userData>*/
			GOCH::GameObjectCharactersManager::getSingletonPtr()->createGOCHPlayer(pParent,
																				   getProperty("Property", "PlayerCameraNodeName"));

			break;
		}
		case ShareData::GameConfigurations::LoadersConfigurations::GOCH_POLICE:
		{
			/*<userData>
				<property type="7" name="GameObjectNodeType" data="101" />
				<property type="7" name="PoliceEntityMeshName" data="SFKillerEntity#0" />
				<property type="7" name="PoliceTalkCameraNodeName" data="SFKillerTalkCameraNode#0" />
				<property type="7" name="GOCHPoliceState" data="Idle" />
			</userData>*/
			GOCH::GameObjectCharactersManager::getSingletonPtr()->createGOCHPolice(aNodeId,
																				   pParent,
																				   getProperty("Property", "PoliceEntityMeshName"),
																				   getProperty("Property", "PoliceTalkCameraNodeName"),
																				   GameObjectPolice::StringToGOCHPoliceState(getProperty("Property", "GOCHPoliceState")));

			break;
		}		
	};

	nodeProperties.clear();
}

void DotSceneLoader::processNodeEntityUserData(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
	rapidxml::xml_node<>* pElement;
	pElement = XMLNode->first_node("property");
	if(pElement)
	{
		while(pElement)
		{
			processUserDataProperty(pElement);
			pElement = pElement->next_sibling("property");
		}
	}		
}

void DotSceneLoader::processUserDataProperty(rapidxml::xml_node<>* XMLNode)
{
	nodeProperties.push_back(nodeProperty("Property", getAttrib(XMLNode, "name"), getAttrib(XMLNode, "data"), getAttrib(XMLNode, "type")));
}

void DotSceneLoader::processParticleSystem(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
	// Process attributes
	Ogre::String name = getAttrib(XMLNode, "name");
	Ogre::String id = getAttrib(XMLNode, "id");
	Ogre::String file = getAttrib(XMLNode, "file");
 
	// Create the particle system
	try
	{
		Ogre::ParticleSystem *pParticles = mSceneMgr->createParticleSystem(name, file);
		pParent->attachObject(pParticles);
	}
	catch(Ogre::Exception &/*e*/)
	{
		Ogre::LogManager::getSingleton().logMessage("[DotSceneLoader] Error creating a particle system!");
	}
}
 
void DotSceneLoader::processBillboardSet(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
	//! @todo Implement this
}
 
void DotSceneLoader::processPlane(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent)
{
	Ogre::String name = getAttrib(XMLNode, "name");
	Ogre::Real distance = getAttribReal(XMLNode, "distance");
	Ogre::Real width = getAttribReal(XMLNode, "width");
	Ogre::Real height = getAttribReal(XMLNode, "height");
	int xSegments = Ogre::StringConverter::parseInt(getAttrib(XMLNode, "xSegments"));
	int ySegments = Ogre::StringConverter::parseInt(getAttrib(XMLNode, "ySegments"));
	int numTexCoordSets = Ogre::StringConverter::parseInt(getAttrib(XMLNode, "numTexCoordSets"));
	Ogre::Real uTile = getAttribReal(XMLNode, "uTile");
	Ogre::Real vTile = getAttribReal(XMLNode, "vTile");
	Ogre::String material = getAttrib(XMLNode, "material");
	bool hasNormals = getAttribBool(XMLNode, "hasNormals");
	Ogre::Vector3 normal = parseVector3(XMLNode->first_node("normal"));
	Ogre::Vector3 up = parseVector3(XMLNode->first_node("upVector"));
 
	Ogre::Plane plane(normal, distance);
	Ogre::MeshPtr res = Ogre::MeshManager::getSingletonPtr()->createPlane(
						name + "mesh", "General", plane, width, height, xSegments, ySegments, hasNormals,
	numTexCoordSets, uTile, vTile, up);
	Ogre::Entity* ent = mSceneMgr->createEntity(name, name + "mesh");
 
	ent->setMaterialName(material);
 
	pParent->attachObject(ent);
}
 
void DotSceneLoader::processFog(rapidxml::xml_node<>* XMLNode)
{
	// Process attributes
	Ogre::Real expDensity = getAttribReal(XMLNode, "density", 0.001);
	Ogre::Real linearStart = getAttribReal(XMLNode, "start", 0.0);
	Ogre::Real linearEnd = getAttribReal(XMLNode, "end", 1.0);
 
	Ogre::FogMode mode = Ogre::FOG_NONE;
	Ogre::String sMode = getAttrib(XMLNode, "mode");
	if(sMode == "none")
		mode = Ogre::FOG_NONE;
	else if(sMode == "exp")
		mode = Ogre::FOG_EXP;
	else if(sMode == "exp2")
		mode = Ogre::FOG_EXP2;
	else if(sMode == "linear")
		mode = Ogre::FOG_LINEAR;
	else
		mode = (Ogre::FogMode)Ogre::StringConverter::parseInt(sMode);
 
	rapidxml::xml_node<>* pElement;
 
	// Process colourDiffuse (?)
	Ogre::ColourValue colourDiffuse = Ogre::ColourValue::White;
	pElement = XMLNode->first_node("colour");
	if(pElement)
		colourDiffuse = parseColour(pElement);
 
	// Setup the fog
	mSceneMgr->setFog(mode, colourDiffuse, expDensity, linearStart, linearEnd);
}
 
void DotSceneLoader::processSkyBox(rapidxml::xml_node<>* XMLNode)
{
	// Process attributes
	Ogre::String material = getAttrib(XMLNode, "material", "BaseWhite");
	Ogre::Real distance = getAttribReal(XMLNode, "distance", 5000);
	bool drawFirst = getAttribBool(XMLNode, "drawFirst", true);
	bool active = getAttribBool(XMLNode, "active", false);
	if(!active)
		return;
 
	rapidxml::xml_node<>* pElement;
 
	// Process rotation (?)
	Ogre::Quaternion rotation = Ogre::Quaternion::IDENTITY;
	pElement = XMLNode->first_node("rotation");
	if(pElement)
		rotation = parseQuaternion(pElement);
 
	// Setup the sky box
	mSceneMgr->setSkyBox(true, material, distance, drawFirst, rotation, m_sGroupName);
}
 
void DotSceneLoader::processSkyDome(rapidxml::xml_node<>* XMLNode)
{
	// Process attributes
	Ogre::String material = XMLNode->first_attribute("material")->value();
	Ogre::Real curvature = getAttribReal(XMLNode, "curvature", 10);
	Ogre::Real tiling = getAttribReal(XMLNode, "tiling", 8);
	Ogre::Real distance = getAttribReal(XMLNode, "distance", 4000);
	bool drawFirst = getAttribBool(XMLNode, "drawFirst", true);
	bool active = getAttribBool(XMLNode, "active", false);
	if(!active)
		return;
 
	rapidxml::xml_node<>* pElement;
 
	// Process rotation (?)
	Ogre::Quaternion rotation = Ogre::Quaternion::IDENTITY;
	pElement = XMLNode->first_node("rotation");
	if(pElement)
		rotation = parseQuaternion(pElement);
 
	// Setup the sky dome
	mSceneMgr->setSkyDome(true, material, curvature, tiling, distance, drawFirst, rotation, 16, 16, -1, m_sGroupName);
}
 
void DotSceneLoader::processSkyPlane(rapidxml::xml_node<>* XMLNode)
{
	// Process attributes
	Ogre::String material = getAttrib(XMLNode, "material");
	Ogre::Real planeX = getAttribReal(XMLNode, "planeX", 0);
	Ogre::Real planeY = getAttribReal(XMLNode, "planeY", -1);
	Ogre::Real planeZ = getAttribReal(XMLNode, "planeX", 0);
	Ogre::Real planeD = getAttribReal(XMLNode, "planeD", 5000);
	Ogre::Real scale = getAttribReal(XMLNode, "scale", 1000);
	Ogre::Real bow = getAttribReal(XMLNode, "bow", 0);
	Ogre::Real tiling = getAttribReal(XMLNode, "tiling", 10);
	bool drawFirst = getAttribBool(XMLNode, "drawFirst", true);
 
	// Setup the sky plane
	Ogre::Plane plane;
	plane.normal = Ogre::Vector3(planeX, planeY, planeZ);
	plane.d = planeD;
	mSceneMgr->setSkyPlane(true, plane, material, scale, tiling, drawFirst, bow, 1, 1, m_sGroupName);
}
 
void DotSceneLoader::processClipping(rapidxml::xml_node<>* XMLNode)
{
	//! @todo Implement this
 
	// Process attributes
	Ogre::Real fNear = getAttribReal(XMLNode, "near", 0);
	Ogre::Real fFar = getAttribReal(XMLNode, "far", 1);
}
 
void DotSceneLoader::processLightRange(rapidxml::xml_node<>* XMLNode, Ogre::Light *pLight)
{
	// Process attributes
	Ogre::Real inner = getAttribReal(XMLNode, "inner");
	Ogre::Real outer = getAttribReal(XMLNode, "outer");
	Ogre::Real falloff = getAttribReal(XMLNode, "falloff", 1.0);

	// Setup the light range
	pLight->setSpotlightRange(Ogre::Angle(inner), Ogre::Angle(outer), falloff);
}
 
void DotSceneLoader::processLightAttenuation(rapidxml::xml_node<>* XMLNode, Ogre::Light *pLight)
{
	// Process attributes
	Ogre::Real range = getAttribReal(XMLNode, "range");
	Ogre::Real constant = getAttribReal(XMLNode, "constant");
	Ogre::Real linear = getAttribReal(XMLNode, "linear");
	Ogre::Real quadratic = getAttribReal(XMLNode, "quadratic");
 
	// Setup the light attenuation
	//Ogre::Vector4 attParams = Ogre::Vector4(20, 1.0f, 0.22f, 0.20f);
	pLight->setAttenuation(range, constant, linear, quadratic);
	//pLight->setAttenuation(attParams.x, attParams.y, attParams.z, attParams.w);
}
 
 
Ogre::String DotSceneLoader::getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, const Ogre::String &defaultValue)
{
	if(XMLNode->first_attribute(attrib.c_str()))
		return XMLNode->first_attribute(attrib.c_str())->value();
	else
		return defaultValue;
}
 
Ogre::Real DotSceneLoader::getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, Ogre::Real defaultValue)
{
	if(XMLNode->first_attribute(attrib.c_str()))
		return Ogre::StringConverter::parseReal(XMLNode->first_attribute(attrib.c_str())->value());
	else
		return defaultValue;
}
 
bool DotSceneLoader::getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, bool defaultValue)
{
	if(!XMLNode->first_attribute(attrib.c_str()))
		return defaultValue;
 
	if(Ogre::String(XMLNode->first_attribute(attrib.c_str())->value()) == "true")
		return true;
 
	return false;
}
 
Ogre::Vector3 DotSceneLoader::parseVector3(rapidxml::xml_node<>* XMLNode)
{
	return Ogre::Vector3(
		Ogre::StringConverter::parseReal(XMLNode->first_attribute("x")->value()),
		Ogre::StringConverter::parseReal(XMLNode->first_attribute("y")->value()),
		Ogre::StringConverter::parseReal(XMLNode->first_attribute("z")->value())
	);
}
 
Ogre::Quaternion DotSceneLoader::parseQuaternion(rapidxml::xml_node<>* XMLNode)
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
 
Ogre::ColourValue DotSceneLoader::parseColour(rapidxml::xml_node<>* XMLNode)
{
	return Ogre::ColourValue(
		Ogre::StringConverter::parseReal(XMLNode->first_attribute("r")->value()),
		Ogre::StringConverter::parseReal(XMLNode->first_attribute("g")->value()),
		Ogre::StringConverter::parseReal(XMLNode->first_attribute("b")->value()),
		XMLNode->first_attribute("a") != NULL ? Ogre::StringConverter::parseReal(XMLNode->first_attribute("a")->value()) : 1
	);
}
 
Ogre::String DotSceneLoader::getProperty(const Ogre::String &ndNm, const Ogre::String &prop)
{
	for ( unsigned int i = 0 ; i < nodeProperties.size(); i++ )
	{
		if ( nodeProperties[i].nodeName == ndNm && nodeProperties[i].propertyNm == prop )
		{
			return nodeProperties[i].valueName;
		}
	}
 
	return "";
}
 
void DotSceneLoader::processUserDataReference(rapidxml::xml_node<>* XMLNode, Ogre::Entity *pEntity)
{
	Ogre::String str = XMLNode->first_attribute("id")->value();
	pEntity->setUserAny(Ogre::Any(str));
}

void DotSceneLoader::_mySplit(std::vector<Ogre::String> &tokens, const Ogre::String &text, char sep) 
{
  int start = 0, end = 0;

  while ((end = text.find(sep, start)) != Ogre::String::npos) 
  {
	tokens.push_back(text.substr(start, end - start));
	start = end + 1;
  }

  tokens.push_back(text.substr(start));
}

std::vector<Ogre::Real> DotSceneLoader::parseStringLodDistance(Ogre::String aDistanceLods)
{
	std::vector<Ogre::Real> lodDistancesValues;
		
	std::vector<Ogre::String> tokens; 
	_mySplit(tokens,aDistanceLods,'#');						
				
	lodDistancesValues.push_back(Ogre::StringConverter::parseReal(tokens[0]));
	lodDistancesValues.push_back(Ogre::StringConverter::parseReal(tokens[1]));

	return 	lodDistancesValues;	
}

Ogre::Entity* DotSceneLoader::_createEntity(Ogre::SceneNode* aSceneNode, Ogre::String aName, Ogre::String aMeshFile, Ogre::String aMaterialFile, 
											bool aCastShadows, bool createLODs)
{

	try
	{
		Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().load(aMeshFile, m_sGroupName, Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY, 
																	Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY, true, true);
		unsigned short src, dest;		
		if (!mesh->suggestTangentVectorBuildParams(Ogre::VES_TANGENT, src, dest))
		{
			mesh->buildTangentVectors(Ogre::VES_TANGENT, src, dest);
			mesh->buildEdgeList();
		}

		if(createLODs)
		{
			std::vector<Ogre::Real> lodDistancesValues;
			bool isLodLoad = false;
			unsigned int numberLods = 0;
						
			if(Ogre::StringConverter::parseBool(getProperty("Property", "HasLOD")))
			{
				Ogre::String distanceLODs = getProperty("Property", "DistanceLODs");
				std::vector<Ogre::String> tokens; 
				_mySplit(tokens,distanceLODs,'#');						
			
				numberLods = Ogre::StringConverter::parseInt((getProperty("Property", "NumberLODs")));
				for(unsigned int index = 0; index < numberLods; index ++)
					lodDistancesValues.push_back(Ogre::StringConverter::parseReal(tokens[index]));		
			}				
			
			bool ant = false;
			if(!mesh->isLodManual())
				ant= true;

			if(lodDistancesValues.size()!=0 && !mesh->isLodManual())
			{
				Ogre::String strLOD;

				for(unsigned int index = 0; index < numberLods; index ++)
				{
					strLOD.clear();
					strLOD = Ogre::StringUtil::replaceAll(aMeshFile, ".mesh", "_LOD" +  Ogre::StringConverter::toString(index+1) + ".mesh");
					Ogre::MeshPtr lodMesh = Ogre::MeshManager::getSingleton().load(strLOD, m_sGroupName);
					mesh->createManualLodLevel(lodDistancesValues[index], lodMesh->getName());		
				}		
			}		
		}		

		 // Create the entity
		Ogre::Entity* pEntity = 0;
		pEntity = mSceneMgr->createEntity(aName, mesh);
		pEntity->setCastShadows(aCastShadows);			
		
		/*if(Ogre::StringUtil::startsWith(aName,"pPlane9") || Ogre::StringUtil::startsWith(aName,"Road") || Ogre::StringUtil::startsWith(aName,"Ground20M"))
			pEntity->setCastShadows(false);		
		else
			pEntity->setCastShadows(true);*/

		aSceneNode->attachObject(pEntity);
 
		if(!aMaterialFile.empty())
			pEntity->setMaterialName(aMaterialFile);

		return pEntity;
	}
	catch(Ogre::Exception e)
	{
		return 0;
	}
}
#ifndef TOOLS_H_
#define TOOLS_H_
	
class Tools
{
	public:

		static void Destroy(Ogre::SceneManager* aSceneManager, Ogre::String aSceneNodeName);		
		static void DestroyLight(Ogre::SceneManager* aSceneManager, Ogre::Light* aLight);

		static bool fileExists(const Ogre::String& aFilename);
		static bool OrderWayPoints(Ogre::SceneNode* i, Ogre::SceneNode* j);
		static Ogre::Real Pulse(float aTime, const float aFrequency = 1, const float aAmplitude = 1);	
		static Ogre::Entity* CreateEntity(Ogre::SceneManager* aSceneManager, Ogre::SceneNode* aSceneNode, Ogre::String aEntityName, Ogre::String aResourceGroupName, 
										  Ogre::String aMeshFile, Ogre::String aMaterialFile, bool aCastShadows, bool aHasLODs, int aNumberLODs, 
										  std::vector<Ogre::String> aLODsDistances);

		static Ogre::Light* CreateLight(Ogre::SceneManager* aSceneManager, Ogre::String aLightName, Ogre::Light::LightTypes aType, Ogre::Vector3 aPosition, 
										Ogre::Vector3 aDirection, bool aVisible, bool aCastShadows, Ogre::ColourValue aColorDiffuse, Ogre::ColourValue aColorSpecular,
										Ogre::Real aInner, Ogre::Real aOuter, Ogre::Real aFalloff, Ogre::Real aRange, Ogre::Real aConstant, 
										Ogre::Real aLinear, Ogre::Real aQuadratic);

};
#endif //TOOLS_H_
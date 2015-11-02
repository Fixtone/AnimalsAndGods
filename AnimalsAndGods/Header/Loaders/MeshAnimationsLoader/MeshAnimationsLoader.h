#ifndef __MeshAnimationsLoader_h_
#define __MeshAnimationsLoader_h_

class MeshAnimationsLoader
{
		public:					
 
			MeshAnimationsLoader();
			virtual ~MeshAnimationsLoader();
 
			ShareData::GameConfigurations::GOConfigurations::sAnimationsData loadMeshAnimation(const Ogre::uint32	aGOMeshAnimationId, const Ogre::String &SceneName, 
																							   const Ogre::String &groupName, Ogre::SceneManager *yourSceneMgr, 
							 																   Ogre::SceneNode *pAttachNode = NULL);

		private:

			void processMeshAnimation(rapidxml::xml_node<>* XMLRoot);
			
			Ogre::String getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, const Ogre::String &defaultValue = "");
			Ogre::Real getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, Ogre::Real defaultValue = 0);
			bool getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, bool defaultValue = false);
 
			Ogre::Vector3 parseVector3(rapidxml::xml_node<>* XMLNode);
			Ogre::Quaternion parseQuaternion(rapidxml::xml_node<>* XMLNode);
			Ogre::ColourValue parseColour(rapidxml::xml_node<>* XMLNode);
					
			void processAnimations(rapidxml::xml_node<>* XMLNode);
			Ogre::AnimationState* processAnimation(Ogre::uint32 aNodeTrackHandle, rapidxml::xml_node<>* XMLNode);			
			void processKeyFrame(rapidxml::xml_node<>* XMLNode, Ogre::NodeAnimationTrack* pNumTrack);

			Ogre::SceneManager*													_SceneManager;
			Ogre::SceneNode*													_AttachNode;
			Ogre::String														_sGroupName;			
			ShareData::GameConfigurations::GOConfigurations::sAnimationsData	_Animations;
				
			Ogre::uint32														_GOMeshAnimationId;
};

#endif
#ifndef GLOWMATERIALLISTENER_H__
#define GLOWMATERIALLISTENER_H__
 
class GlowMaterialListener : public Ogre::MaterialManager::Listener
{
	protected:
		
		Ogre::MaterialPtr mBlackMat;
		Ogre::MaterialPtr mBlackMatAlpha;

	public:

		GlowMaterialListener()
		{
			mBlackMat = Ogre::MaterialManager::getSingleton().create("mGlowBlack", "Internal");
			mBlackMat->getTechnique(0)->getPass(0)->setDiffuse(0,0,0,0);
			mBlackMat->getTechnique(0)->getPass(0)->setSpecular(0,0,0,0);
			mBlackMat->getTechnique(0)->getPass(0)->setAmbient(0,0,0);
			mBlackMat->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,0);

			mBlackMatAlpha = Ogre::MaterialManager::getSingleton().create("mGlowBlackAlpha", "Internal");
			mBlackMatAlpha->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
			mBlackMatAlpha->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
			mBlackMatAlpha->getTechnique(0)->getPass(0)->setDiffuse(0,0,0,0);
			mBlackMatAlpha->getTechnique(0)->getPass(0)->setSpecular(0,0,0,0);
			mBlackMatAlpha->getTechnique(0)->getPass(0)->setAmbient(0,0,0);
			mBlackMatAlpha->getTechnique(0)->getPass(0)->setSelfIllumination(0,0,0);
		}
 
		
		Ogre::Technique *handleSchemeNotFound(unsigned short, const Ogre::String& schemeName, Ogre::Material*mat, unsigned short, const Ogre::Renderable*)
		{
			if (schemeName == "glow")
			{
				//LogManager::getSingleton().logMessage(">> adding glow to material: "+mat->getName());
				if(Ogre::StringUtil::match(mat->getTechnique(0)->getPass(0)->getName(),"AlphaBlend",true))
					return mBlackMatAlpha->getTechnique(0);
				else
					return mBlackMat->getTechnique(0);
			}
			return NULL;
		}
		
};
 
#endif //GLOWMATERIALLISTENER_H__
#include "stdafx.h"
#include "../../Header/Shaders/DeferredShadingManager.h"

using namespace Shaders;

const Ogre::uint8 DeferredShadingManager::PRE_GBUFFER_RENDER_QUEUE = Ogre::RENDER_QUEUE_1;
const Ogre::uint8 DeferredShadingManager::POST_GBUFFER_RENDER_QUEUE = Ogre::RENDER_QUEUE_8;

template<> DeferredShadingManager* Ogre::Singleton<DeferredShadingManager>::msSingleton = 0;
DeferredShadingManager* DeferredShadingManager::getSingletonPtr(void)
{
	return msSingleton;
}
 
DeferredShadingManager& DeferredShadingManager::getSingleton(void)
{  
	assert(msSingleton);
	return *msSingleton;
}

DeferredShadingManager::DeferredShadingManager()
{
}

DeferredShadingManager::~DeferredShadingManager()
{
}

bool DeferredShadingManager::initializeDeferredShadingManager(Ogre::SceneManager* aSceneManager, Ogre::Viewport* aViewport,
															  Ogre::ShadowTechnique aShowTechnique, Ogre::String aShadowTextureCasterMaterial,
															  size_t aShadowTextureCount, Ogre::Real aShadowFarDistance, Ogre::Real aShadowDirectionalLightExtrusionDistance)
{
	try
	{	
		_SceneManager = aSceneManager;
		_Viewport = aViewport;

		_SceneManager->setShadowTechnique(aShowTechnique);
		_SceneManager->setShadowTextureCasterMaterial(aShadowTextureCasterMaterial);
		_SceneManager->setShadowTextureCount(aShadowTextureCount);
		_SceneManager->setShadowFarDistance(aShadowFarDistance);
		
		//Use a value of "2" to use a different depth buffer pool and avoid sharing this with the Backbuffer's
		_SceneManager->setShadowTextureConfig( 0, 1024, 1024, Ogre::PF_FLOAT16_R, 0, 2 );
		_SceneManager->setShadowDirectionalLightExtrusionDistance(aShadowDirectionalLightExtrusionDistance);

		//Initialize OgreCompositors instances
		for(unsigned short index = 0; index < DSM_COUNT; ++index)
			_CompositorInstances[index] = 0;

		createDefferedShadingResources();

		_Active = false;	
		_SSAO = false;
		_CurrentMode = DSM_SHOWLIT;
		setActive(true);		

		return true;
	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[DeferredShadingManager]: " + e.getDescription());
		return false;
	}
}

bool DeferredShadingManager::clearDeferredShadingManager()
{
	try
	{
		
		Ogre::CompositorChain *chain = Ogre::CompositorManager::getSingleton().getCompositorChain(_Viewport);
				
		for(int i=0; i<DSM_COUNT; ++i)
		{			
			chain->_removeInstance(_CompositorInstances[i]);
		}

		Ogre::CompositorManager::getSingleton().removeCompositorChain(_Viewport);

		Ogre::CompositorManager& compMgr = Ogre::CompositorManager::getSingleton();
		CompositorLogicMap::const_iterator itor = _CompositorLogics.begin();
		CompositorLogicMap::const_iterator end  = _CompositorLogics.end();
		while( itor != end )
		{
			compMgr.unregisterCompositorLogic( itor->first );
			delete itor->second;
			++itor;
		}
		
		_CompositorLogics.clear();	

		//Ilumination::IluminationManager::getSingletonPtr()->removeLightByName("DefferedShadingMainStaticDirectionalLight", Ogre::Light::LT_DIRECTIONAL);

		return true;

	}
	catch(Ogre::Exception& e)
	{
		Ogre::LogManager::getSingletonPtr()->logMessage("[DeferredShadingManager]: " + e.getDescription());
		return false;
	}
}

void DeferredShadingManager::createDefferedShadingResources()
{
	Ogre::CompositorManager* compositorManager = Ogre::CompositorManager::getSingletonPtr();

	//Hook up the compositor logic and scheme handlers.
	//This can theoretically happen in a loaded plugin, but in this case the demo contains the code.
	static bool firstTime = true;
	if (firstTime)
	{
		Ogre::MaterialManager::getSingleton().addListener(new GBufferSchemeHandler, "GBuffer");
		Ogre::MaterialManager::getSingleton().addListener(new NullSchemeHandler, "NoGBuffer");

		compositorManager->registerCustomCompositionPass("DeferredLight", new DeferredLightCompositionPass);

		firstTime = false;
	}

	_CompositorLogics["SSAOLogic"] = new SSAOLogic;
	compositorManager->registerCompositorLogic("SSAOLogic", _CompositorLogics["SSAOLogic"]);

	// Create the main GBuffer compositor
	_GBufferInstance						= compositorManager->addCompositor(_Viewport, "DeferredShading/GBuffer");
	
	// Create filters
	_CompositorInstances[DSM_SHOWLIT]		= compositorManager->addCompositor(_Viewport, "DeferredShading/ShowLit");
	_CompositorInstances[DSM_SHOWNORMALS]	= compositorManager->addCompositor(_Viewport, "DeferredShading/ShowNormals");
	_CompositorInstances[DSM_SHOWDSP]		= compositorManager->addCompositor(_Viewport, "DeferredShading/ShowDepthSpecular");
	_CompositorInstances[DSM_SHOWCOLOUR]	= compositorManager->addCompositor(_Viewport, "DeferredShading/ShowColour");
	
	_SSAOInstance							= compositorManager->addCompositor(_Viewport, "DeferredShading/SSAO");

	setSSAO(true);

	//Ilumination::IluminationManager::getSingletonPtr()->createDirectionalLight("DefferedShadingMainStaticDirectionalLight", 
	//																		   Ogre::ColourValue::White,
	//																		   //Ogre::ColourValue(0.8f, 0.8f, 0.8f),  
	//																		   Ogre::Vector3::NEGATIVE_UNIT_Y,
	//																		   Ogre::Real(15000),
	//																		   Ogre::Real(7500),
	//																		   true);
}

void DeferredShadingManager::setActive(bool active)
{
	if (_Active != active)
	{
		_Active = active;
		_GBufferInstance->setEnabled(active);

		// mCurrentMode could have changed with a prior call to setMode, so iterate all
		setMode(_CurrentMode);
	}
}


void DeferredShadingManager::setMode(DSMode mode)
{
	assert( 0 <= mode && mode < DSM_COUNT);

	// prevent duplicate setups
	if (_CurrentMode == mode && _CompositorInstances[mode]->getEnabled() == _Active)
		return;

	for(int i=0; i<DSM_COUNT; ++i)
	{
		if(i == mode)
		{
			_CompositorInstances[i]->setEnabled(_Active);
		}
		else
		{
			_CompositorInstances[i]->setEnabled(false);
		}
	}

	_CurrentMode = mode;

	_SSAOInstance->setEnabled(_Active && _SSAO && _CurrentMode == DSM_SHOWLIT);
}


void DeferredShadingManager::setSSAO(bool ssao)
{
	if (ssao != _SSAO) 
	{
		_SSAO = ssao;
		if (_Active && _CurrentMode == DSM_SHOWLIT)
		{
			_SSAOInstance->setEnabled(ssao);
		}
	}
}

bool DeferredShadingManager::getSSAO() const
{
	return _SSAO;
}
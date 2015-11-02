#ifndef DeferredShadingManager_H
#define DeferredShadingManager_H

#include "GBufferSchemeHandler.h"
#include "NullSchemeHandler.h"
#include "DeferredLightCP.h"
#include "SSAOLogic.h"

namespace Shaders
{
	class DeferredShadingManager : public Ogre::Singleton<DeferredShadingManager>
								 , public Ogre::RenderTargetListener
	{
		public:	

			DeferredShadingManager();
			~DeferredShadingManager();		

			static DeferredShadingManager& getSingleton(void);
			static DeferredShadingManager* getSingletonPtr(void);

			enum DSMode
			{
				DSM_SHOWLIT = 0,     // The deferred shading mode
				DSM_SHOWCOLOUR = 1,  // Show diffuse (for debugging)
				DSM_SHOWNORMALS = 2, // Show normals (for debugging)
				DSM_SHOWDSP = 3,	 // Show depth and specular channel (for debugging)
				DSM_COUNT = 4
			};

			//The first render queue that does get rendered into the GBuffer
			//place objects (like skies) that should be before gbuffer before this one.
			static const Ogre::uint8 PRE_GBUFFER_RENDER_QUEUE;
	
			//The first render queue that does not get rendered into the GBuffer
			//place transparent (or other non gbuffer) objects after this one
			static const Ogre::uint8 POST_GBUFFER_RENDER_QUEUE;

			bool initializeDeferredShadingManager(Ogre::SceneManager* aSceneManager, Ogre::Viewport* aViewport,
												  Ogre::ShadowTechnique aShowTechnique, Ogre::String aShadowTextureCasterMaterial,
												  size_t aShadowTextureCount, Ogre::Real aShadowFarDistance, Ogre::Real aShadowDirectionalLightExtrusionDistance);

			bool clearDeferredShadingManager();

			bool isActive(){return _Active;}
			void setActive(bool active);
			void setMode(DSMode mode);		
			
			/*
			 * Set screen space ambient occlusion mode
			*/
			void setSSAO(bool ssao);	
			bool getSSAO() const;

		private:

			void createDefferedShadingResources();				

			Ogre::Viewport*			_Viewport;
			Ogre::SceneManager*		_SceneManager;
			Ogre::Camera*			_Camera;

			bool	_Active;
			DSMode	_CurrentMode;
			bool	_SSAO;

			Ogre::CompositorInstance* _CompositorInstances[DSM_COUNT];

			//Used to unregister compositor logics and free memory
			typedef Ogre::map<Ogre::String, Ogre::CompositorLogic*>::type CompositorLogicMap;
			CompositorLogicMap  _CompositorLogics;

			Ogre::CompositorInstance* _GBufferInstance;

			Ogre::CompositorInstance* _SSAOInstance;
	};
}
#endif
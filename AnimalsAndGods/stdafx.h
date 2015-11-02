#pragma once

// any other header can be included, as usual
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#include <stdint.h>

// Ogre headers you need
#include <Ogre.h>
#include <OgreSingleton.h>
#include <OgreException.h>
#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreCamera.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreEntity.h>
#include <OgreWindowEventUtilities.h>
#include <OgreLogManager.h>
#include <OgreCompositorInstance.h>
#include <OgreGpuProgramManager.h>
#include <OgreHighLevelGpuProgram.h>
#include <OgreHighLevelGpuProgramManager.h>
#include <OgreSimpleRenderable.h>
#include <OgreMaterialManager.h>
#include <OgreRenderSystem.h>
#include <OgreCustomCompositionPass.h>
#include <OgreHardwareBufferManager.h>
#include <OgreSceneNode.h>
#include <OgreLight.h>
#include <OgreTechnique.h>
#include <OgreMaterial.h>
#include <OgreStringVector.h>
#include <OgreStringConverter.h>
#include <OgrePass.h>
#include <OgreRenderTargetListener.h>
#include <OgrePrerequisites.h>
#include <OgreCompositorLogic.h>
#include <OgreProfiler.h>
#include <OgreLodStrategy.h>

#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include <Terrain/OgreTerrainMaterialGeneratorA.h>

// Ogre OIS headers you need
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <SdkTrays.h>
#include <SdkCameraMan.h>

// XML
#include <rapidxml.hpp>

// NXOGRE
#include <NxOgre.h>

//CRITTER
#include <Critter.h>
//#include "CritterCommon.h"
//#include "CritterCharacterInput.h"

// OGRE PROCEDURAL
#include <Procedural.h>

// BOOST
#include <boost\unordered_map.hpp>
#include <boost\foreach.hpp>
#include <boost\enable_shared_from_this.hpp>
#include <boost\algorithm\string.hpp>
#include <boost\bind.hpp>

// STD
#include <vector>
#include <string>
#include <sstream>
#include <vptype.h>

// OGRE VIDEO PLUGIN
#include <FFmpegVideoPlayer.h>
// anything you want after that

//SHADOWS
#include "Header\Shaders\Shadows\CSMGpuConstants.h"
#include "Header\Shaders\Shadows\ShadowCameraSetupStableCSM.h"

//#VORVIS
#include <vorbis\codec.h>
#include <vorbis\vorbisenc.h>
#include <vorbis\vorbisfile.h>

//SOUND
#include "Header\Sound\SoundManager.h"

//LUA & LOGIC
#include "Header\Lua\LuaDefines.h"
#include "Header\Lua\LuaInterface.h"
#include "Header\Lua\LuaManager.h"
#include "Header\Logic\LogicManager.h"
#include "Header\Logic\LogicInterface.h"

//PHYSICS
#include "Header\Physics\PhysicsManager.h"

//PARTICLES
#include "Header\Particles\ParticleUniverse\ParticleUniverseManager.h"
#include "Header\Particles\OgreParticles\ParticleOgreManager.h"

//CAMERAS
#include "Header\Camera\CameraManager.h"
#include "Header\Camera\CustomCamera.h"
#include "Header\Camera\FPSCamera.h"
#include "Header\Camera\FreeCamera.h"
#include "Header\Camera\StaticCamera.h"

//Game Includes
#include "Header\GameObject\GameObjectInterfaces\IClever.h"
#include "Header\GameObject\GameObjectInterfaces\IReactive.h"
#include "Header\GameObject\GameObjectBase\GameObject.h"
#include "Header\GameObject\GameObjectEntities\GameObjectEntity.h"
#include "Header\GameObject\GameObjectEntities\GameObjectEntityManager.h"
#include "Header\GameObject\GameObjectLights\GameObjectLight.h"
#include "Header\GameObject\GameObjectLights\GameObjectLightManager.h"
#include "Header\GameObject\GameObjectParticleSystems\GameObjectPU.h"


#include "Header\GameObject\GameObjectCharacters\GameObjectCharacter.h"
#include "Header\GameObject\GameObjectCharacters\GameObjectPlayers\GameObjectPlayer.h"
#include "Header\GameObject\GameObjectCharacters\GameObjectPeople\GameObjectPolice.h"

#include "Header\GameObject\GameObjectNodes\GameObjectNode.h"
#include "Header\GameObject\GameObjectTrains\GameObjectTrain.h"
#include "Header\GameObject\GameObjectNodes\GameObjectNodeHydrant.h"
#include "Header\GameObject\GameObjectNodes\GameObjectNodeLighter.h"
#include "Header\GameObject\GameObjectNodes\GameObjectNodeStreetLight.h"
#include "Header\GameObject\GameObjectNodes\GameObjectNodeSewer.h"
#include "Header\GameObject\GameObjectNodes\GameObjectNodeFloorSign.h"
#include "Header\GameObject\GameObjectNodes\GameObjectNodeStreetAddonOne.h"
#include "Header\GameObject\GameObjectNodes\GameObjectNodeStreetAddonTwo.h"
#include "Header\GameObject\GameObjectNodes\GameObjectNodeStreetAddonThree.h"
#include "Header\GameObject\GameObjectNodes\GameObjectNodeManager.h"
#include "Header\GameObject\GameObjectSpaceShips\GameObjectSpaceShip.h"
#include "Header\GameObject\GameObjectTrains\GameObjectTrainsManager.h"
#include "Header\GameObject\GameObjectParticleSystems\GameObjectParticleSystemsManager.h"
#include "Header\GameObject\GameObjectCharacters\GameObjectCharactersManager.h"
#include "Header\GameObject\GameObjectSpaceShips\GameObjectSpaceShipsManager.h"
#include "Header\GameObject\GameObjectWayPoints\GameObjectWayPointsManager.h"

#include "Header\Video\VideoManager.h"
#include "Header\Log\MyLogListener.h"
//#include "Header\Weapons\WeaponsManager.h"
#include "Header\Loaders\Levels\LevelManager.h"
#include "Header\Loaders\DotSceneLoader\DotSceneLoader.h"
#include "Header\Loaders\MeshAnimationsLoader\MeshAnimationsLoader.h"
#include "Header\Shaders\DeferredShadingManager.h"
#include "Header\Materials\GlowMaterialListener.h"
#include "Header\Tools\Tools.h"

//#GUI
#include <Gui3D.h>
#include <Gui3DPanel.h>
#include <Gui3DScreenPanel.h>
#include <Gui3DPanelColors.h>
#include "Header\GUI\GUI3D\Customisation\MyStandardPanelColors.h"
#include "Header\GUI\GUI3D\GUI3DManager.h"

//#MIND
#include "Header\Mind\Thought.h"
#include "Header\Mind\MindManager.h"
#include "Header\Loaders\MindLoader\MindLoader.h"

//#CONFIGS
#include "Header\Loaders\MenuLoader\MenuLoader.h"

#include "Header\GameStates\GameManager.h"
#include "Header\GameStates\ConsoleState.h"
#include "Header\GameStates\GameState.h"
#include "Header\GameStates\IntroState.h"
#include "Header\GameStates\LoadingState.h"
#include "Header\GameStates\MainMenuState.h"
#include "Header\GameStates\PauseState.h"
#include "Header\GameStates\PlayState.h"
#include "Header\GameStates\FinishState.h"

#include "Header\Tools\ShareData.h"
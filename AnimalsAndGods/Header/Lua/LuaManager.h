/*
-----------------------------------------------------------------------------
Wyverns' Assault 3D Videgame.
Copyright (C) 2010  Giorgio Tino, Javier Soto Huesa, Jordi Carreras Ribot,
										Marc Serena, Elm Oliver Torres

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

-----------------------------------------------------------------------------
*/
#ifndef __LUA_MANAGER_H__
#define __LUA_MANAGER_H__

//#include "stdafx.h"
#include "..\Lua\LuaInterface.h"
/*#include "..\Graphics\LightsManager.h"
#include "..\Camera\CameraManager.h"
#include "..\Physics\PhysicsManager.h"
#include "..\Entity\Enemy\EnemyManager.h"
#include "..\Entity\Player\PlayerManager.h"
#include "..\Entity\Item\ItemManager.h"
#include "..\Audio\AudioManager.h"*/

namespace Lua
{
		typedef std::vector<LuaInterface*> LuaInterfaceList;
		typedef std::vector<LuaInterface*>::iterator LuaInterfaceListIterator;

		/**
		Class used to load/manage logic and AI scripts
		*/
		class LuaManager : public Ogre::Singleton<LuaManager>,
						   public boost::enable_shared_from_this<LuaManager>
		{
		public:
				LuaManager();
				~LuaManager();

				static LuaManager& getSingleton(void);
				static LuaManager* getSingletonPtr(void);

		public:
				/** Initialize Lua and load Lua default libs */
				bool initializeLuaManager();
				// Register a new interface to this manager
				bool registerInterface(LuaInterface* luaInterface);
				/** Finalize Lua and unload Lua libs */        
				void finalize();
				/** Reloads scripts */
				bool reload();

				/** Runs all loaded scripts */
				bool update(const float elapsedSeconds);
				void enable();
				void disable();
				bool isEnabled();

		private:
				bool mEnabled;

		private:
				//
				// The Lua interpreter!
				// BEWARE! This is THE ONLY ONE we create/use/destroy!
				//
				lua_State* L;

				//
				// List of registered Lua interfaces
				//
				LuaInterfaceList mLuaInterfaceList;
		};

		typedef boost::shared_ptr<LuaManager> LuaManagerPtr;
}

#endif // __LUA_MANAGER_H__

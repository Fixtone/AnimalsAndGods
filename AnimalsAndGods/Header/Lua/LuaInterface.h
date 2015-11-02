#ifndef __LUA_INTERFACE_H__
#define __LUA_INTERFACE_H__


#include "LuaDefines.h"
/**
Interface to export Lua scripting methods
*/
class LuaInterface
{
	public:
			virtual const char* luaGetLibraryName() const = 0;
			virtual const struct luaL_reg* luaGetLibrary() = 0;
			virtual void luaLoadScripts() = 0;
               
			virtual void luaFinalize(){};
			virtual void luaReload(){};
			virtual bool luaLoadScript(const char* name);
			virtual void luaInitialize(lua_State* L){this->L = L;}
			virtual void luaEnable(){mLuaEnabled = true;}
			virtual void luaDisable(){mLuaEnabled = false;}

	protected:
			/* the Lua interpreter */
			lua_State* L;

			bool mLuaEnabled;
};

typedef boost::shared_ptr<LuaInterface> LuaInterfacePtr;


#endif // __LUA_INTERFACE_H__

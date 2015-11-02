#include "stdafx.h"
#include "../../Header/Lua/LuaInterface.h"

bool LuaInterface::luaLoadScript(const char* name)
{
		/* run the script */
		int retval = lua_dofile(L, name);

		return (retval == 0);
}


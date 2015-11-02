#ifndef __LUA_DEFINES_H__
#define __LUA_DEFINES_H__

extern "C" 
{
	#include "..\..\Libraries\luaSDK\include\lua.h"
	#include "..\..\Libraries\luaSDK\include\lualib.h"
	#include "..\..\Libraries\luaSDK\include\lauxlib.h"
}

#define LUA_SCRIPTS_FOLDER
#define LUA_CLASS LuaClassUndefined
#define LUA_INTERFACE() void luaLoadScripts();

#define LUA_LIBRARY(n,l) static const struct luaL_reg l[]; const char* luaGetLibraryName() const {return n;} ; const struct luaL_reg* luaGetLibrary() {return l;}
#define LUA_FUNCTION(f) static int _lua##f##(lua_State *L);
#define LUA_DEFINE_FUNCTION(c,f) int c##::_lua##f##(lua_State *L)

#define LUA_OPEN_LIBRARY(n,l) luaL_openlib(L, n, l, 0);

#define LUA_BEGIN_BINDING(c,l) const struct luaL_reg c##::##l##[] = {
#define LUA_BIND(c,f) {#f, c##::_lua##f},
#define LUA_END_BINDING() {NULL, NULL}};

//#ifdef LUA_CLASS
//#undef LUA_CLASS
//#endif
//#define LUA_CLASS

#define LUA_BEGIN_LOAD_SCRIPTS(c)       void c##::luaLoadScripts() \
																		{
#define LUA_LOAD_SCRIPT(s)                      luaLoadScript(s);
#define LUA_END_LOAD_SCRIPTS()          }

#define LUA_PROPERTY(n,t)               private : t m_lua##n; \
																public : t n##_get(){return m_lua##n;} \
																public : void n##_set(const t n){m_lua##n=n;}

#define LUA_PROPERTY_SET(c,p,v) c##::getSingleton().##p##_set(v)
#define LUA_PROPERTY_GET(c,p) c##::getSingleton().##p##_get()

#endif // __LUA_DEFINES_H__


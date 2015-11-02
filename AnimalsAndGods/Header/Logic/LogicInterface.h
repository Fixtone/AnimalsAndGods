#ifndef __LOGIC_INTERFACE_H__
#define __LOGIC_INTERFACE_H__

#include "../../stdafx.h"
#include "../Lua/LuaInterface.h"

namespace Logic
{
        /**
        Interface implemented by objects with logic
        */
        class LogicInterface
        {
        public:
                // Initialize logic with callback to Lua scripting
                virtual void initializeLogic(){return;}

                virtual void finalizeLogic(){return;}

                virtual void updateLogic(lua_State *L, const float elapsedSeconds){return;}
        };

        typedef boost::shared_ptr<LogicInterface> LogicInterfacePtr;
}

#endif // __LOGIC_INTERFACE_H__

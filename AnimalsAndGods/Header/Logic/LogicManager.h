#ifndef __LOGIC_MANAGER_H__
#define __LOGIC_MANAGER_H__

namespace Logic
{
		/**
		Class used to load/manage logic and AI scripts
		*/
		class LogicManager : public Ogre::Singleton<LogicManager>
						   , public boost::enable_shared_from_this<LogicManager>
						   , public LuaInterface
		{
		public:
				LogicManager();
				~LogicManager();
				static LogicManager& getSingleton(void);
				static LogicManager* getSingletonPtr(void);

				bool initializeLogicManager();
				void finalize();
				bool update(const float elapsedSeconds);

				void enable() {mEnabled = true;}
				void disable(){mEnabled = false;}
				bool isEnabled(){return mEnabled;}

				Ogre::Real getRandomRange(Ogre::Real a, Ogre::Real b){return Ogre::Math::RangeRandom(a,b);}

		private: // Game data
				bool mEnabled;

				LUA_PROPERTY(TotalSeconds,float);
				LUA_PROPERTY(ElapsedSeconds,float);

		public:
				LUA_INTERFACE();

				// Game Lib (exported to Lua)
				LUA_LIBRARY("Logic", logicLib)

				// From Lua to C++
				LUA_FUNCTION(enable)
				LUA_FUNCTION(disable)
				LUA_FUNCTION(isEnabled)
				LUA_FUNCTION(getTotalSeconds)
				LUA_FUNCTION(getElapsedSeconds)
				LUA_FUNCTION(getRandomRange)

				void luaInitialize(lua_State *L);
		};

		typedef boost::shared_ptr<LogicManager> LogicManagerPtr;
}

#endif // __LOGIC_MANAGER_H__

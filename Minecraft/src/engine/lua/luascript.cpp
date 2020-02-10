#include "mcpch.h"
#include "luascript.h"

namespace Lua
{
	LuaScript::LuaScript(const std::string& filename)
	{
		L = luaL_newstate();
		if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0))
		{
			MC_ERROR("Error: script not loaded ({0})", filename);
			L = nullptr;
		}
	}

	LuaScript::~LuaScript()
	{
		if (L) lua_close(L);
	}

	void LuaScript::PrintError(const std::string& variable, const std::string& message)
	{
		MC_ERROR("Error: can't get [{0}]. {1}", variable, message);
	}

	void 
}
#pragma once

extern "C"
{
#include "lualib/lua.h"
#include "lualib/lauxlib.h"
#include "lualib/lualib.h"
}

namespace Lua
{
	class LuaScript
	{
	public:
		LuaScript(const std::string& filename);
		~LuaScript();
		void PrintError(const std::string& variableName, const std::string& message);

		template<typename T>
		T Get(const std::string& name)
		{
			if (!L)
			{
				PrintError(name, "Script is not loaded");
				return LuaGetDefault<T>();
			}

			T result;
			if (LuaGetToStack(name))
			{
				result = lua_get<T>(name);
			}
			else
			{
				result = LuaGetDefault<T>();
			}

			lua_pop(L, level + 1);
			return result;
		}

		bool LuaGetToStack(const std::string& name)
		{
			m_Level = 0;
			std::string var = "";
			for (uint32_t i = 0; i < name.size(); i++)
			{
				if (name.at(i) == '.')
				{
					if (m_Level = 0)
					{
						lua_getglobal(L, var.c_str());
					}
					else
					{
						lua_getfield(L, -1, var.c_str());
					}

					if (lua_isnil(L, -1))
					{
						PrintError(name, var + " is not defined");
					}
					else
					{
						var = "";
						m_Level++;
					}
				}
				else
				{
					var += name.at(i);
				}
			}
			if (m_Level == 0)
			{
				lua_getglobal(L, var.c_str());
			}
			else
			{
				lua_getfield(L, -1, var.c_str());
			}
			if (lua_isnil(L, -1))
			{
				PrintError(name, var + " is not defined");
				return false;
			}
			return true;
		}

		template<typename T>
		T LuaGet(const std::string& name)
		{
			return 0;
		}

		template<typename T>
		T LuaGetDefault()
		{
			return 0;
		}

	private:
		lua_State* L;
		int m_Level;
		std::string m_Filename;
	};
}

template <>
inline bool Lua::LuaScript::LuaGet<bool>(const std::string& name)
{
	return (bool)lua_toboolean(L, -1);
}

template <>
inline int Lua::LuaScript::LuaGet<int>(const std::string& name)
{
	if (!lua_isnumber(L, -1))
	{
		PrintError(name, "Not a number");
	}

	return (int)lua_tointeger(L, -1);
}
template <>
inline float Lua::LuaScript::LuaGet<float>(const std::string& name)
{
	if (!lua_isnumber(L, -1))
	{
		PrintError(name, "Not a number");
	}

	return (float)lua_tointeger(L, -1);
}

template <>
inline std::string Lua::LuaScript::LuaGet<std::string>(const std::string& name)
{
	std::string s = "null";
	if (lua_isstring(L, -1))
	{
		s = std::string(lua_tostring(L, -1));
	}
	else
	{
		PrintError(name, "Not a string");
	}
	return s;
}

template <>
inline std::string Lua::LuaScript::LuaGetDefault<std::string>()
{
	return "null";
}
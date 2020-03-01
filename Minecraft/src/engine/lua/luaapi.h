#pragma once
#include <sol.hpp>

namespace Minecraft
{
	class LuaApi
	{
	public:
		static void LuaWorldApiInit();
		static void LuaDataApiInit();
		static void LuaUtilApiInit();

	private:
		static void AddBlockApi(sol::table& table);
		static void AddEnums();

	private:
		LuaApi();
		LuaApi(LuaApi& other);
		void operator=(LuaApi& other) = delete;
	};
}
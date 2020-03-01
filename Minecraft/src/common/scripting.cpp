#include "mcpch.h"
#include "scripting.h"

namespace Minecraft
{

	void ScriptingEngine::InitImpl()
	{
		game = lua["game"].get_or_create<sol::table>();
		lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::math);
	}

	bool ScriptingEngine::ExecuteStringImpl(const std::string& script)
	{
		auto res = lua.script(script, [](auto L, auto res)
			{
				(void)L;
				return res;
			});

		return ValidateScriptRun(res, "string");
	}

	bool ScriptingEngine::ValidateScriptRun(const sol::protected_function_result& res, const std::string& name)
	{
		if (res.valid())
		{
			MC_INFO("Script {0} ran successfully.", name);
		}
		else
		{
			sol::error err = res;
			MC_CRITICAL("Lua script is invalid. Error: {0}", err.what());
		}

		return res.valid();
	}

	bool ScriptingEngine::ExecuteFileImpl(const std::string& filepath)
	{
		auto script = lua.load_file(filepath);
		if (script.valid())
		{
			auto res = script();
			return ValidateScriptRun(res, filepath);
		}
		else
		{
			sol::error err = script;

			MC_CRITICAL("Lua file is invalid. Error: {0}", err.what());
			return false;
		}
	}

	sol::function ScriptingEngine::GetLuaFunctionImpl(const std::string& name)
	{
		return game[name];
	}

	void ScriptingEngine::AddCallbackApiImpl(const std::string& name, std::vector<sol::function>& callbacks)
	{
		auto f = AddFunctionImpl(name, [&callbacks](sol::function f) { callbacks.push_back(f); });
	}

	template<typename R, typename... Args>
	std::optional<R> ScriptingEngine::RunLuaFunctionSafeImpl(const std::string& name, Args&&... args)
	{
		sol::protected_function func = game[name];
		sol::protected_function_result result = function(std::forward<Args>(args)...);

		if (result.valid())
		{
			R res = result;
			return res;
		}
		else
		{
			sol::error err = result;
			MC_CRITICAL("Error running lua function: {0}, Message: {1}", name, err.what());
			return {};
		}
	}

}
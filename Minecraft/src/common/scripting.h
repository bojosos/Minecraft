#pragma once

#include <sol.hpp>

namespace Minecraft
{
	class ScriptingEngine
	{
	public:
		static inline void Init() { Get().InitImpl(); }
		static inline bool ExecuteString(const std::string& script) { return Get().ExecuteStringImpl(script); }
		static inline bool ExecuteFile(const std::string& filepath) { return Get().ExecuteFileImpl(filepath); }
		static inline void AddCallbackApi(const std::string& name, std::vector<sol::function>& callbacks) { Get().AddCallbackApiImpl(name, callbacks); }
		static inline sol::function GetLuaFunction(const std::string& name) { return Get().GetLuaFunctionImpl(name); }

		template<typename Ret, typename... Args>
		static inline std::optional<Ret> RunLuaFunctionSafe(const std::string& name, Args&&... args) { return Get().RunLuaFunctionSafeImpl(name, std::forward<Args>(args)...); }

		template<typename... Args>
		static auto AddTable(const std::string& name, Args&&... args) { return Get().AddTableImpl(name, std::forward<Args>(args)...); }

		template<typename T, typename... Args>
		static inline auto AddType(const std::string& name, Args&&... args) { return Get().AddTypeImpl(name, std::forward<Args>(args)...); }

		template<typename F>
		static auto AddFunction(const std::string& name, F function) { return Get().AddFunctionImpl(name, function); }

	private:
		bool ValidateScriptRun(const sol::protected_function_result& res, const std::string& name);
		bool ExecuteStringImpl(const std::string& script);
		bool ExecuteFileImpl(const std::string& filepath);

		void InitImpl();
		void AddCallbackApiImpl(const std::string& name, std::vector<sol::function>& callbacks);
		sol::function GetLuaFunctionImpl(const std::string& name);

		template<typename T, typename... Args>
		auto AddTypeImpl(const std::string& name, Args&&... args);
		
		template<typename... Args>
		auto AddTableImpl(const std::string& name, Args&&... args);

		template<typename F>
		auto AddFunctionImpl(const std::string& name, F function);

		template<typename Ret, typename... Args>
		std::optional<Ret> RunLuaFunctionSafeImpl(const std::string& name, Args&&... args);

		static ScriptingEngine& Get()
		{
			static ScriptingEngine instance;
			return instance;
		}

		sol::state lua;
		sol::table game;
	};

	template<typename... Args>
	void RunLuaCallbacks(const std::vector<sol::function>& callbacks, Args &&... args)
	{
		for (auto& callback : callbacks)
		{
			callback(std::forward<Args>(args)...);
		}
	}

	template<typename T, typename... Args>
	auto ScriptingEngine::AddTypeImpl(const std::string& name, Args&&... args)
	{
		return lua.new_usertype<T>(name, std::forward<Args>(args)...);
	}

	template<typename... Args>
	auto ScriptingEngine::AddTableImpl(const std::string& name, Args&&... args)
	{
		return game.create_named(name, std::forward<Args>(args)...);
	}

	template<typename F>
	auto ScriptingEngine::AddFunctionImpl(const std::string& name, F function)
	{
		return game[name] = function;
	}
}
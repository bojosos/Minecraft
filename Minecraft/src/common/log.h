#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "common.h"

namespace Minecraft
{
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetLogger() { return s_Logger; }
		inline static bool IsInitialized() { return s_Logger != nullptr; }
	private:
		static Ref<spdlog::logger> s_Logger;
	};
}

#define MC_TRACE(...) ::Minecraft::Log::GetLogger()->trace(__VA_ARGS__)
#define MC_INFO(...) ::Minecraft::Log::GetLogger()->info(__VA_ARGS__)
#define MC_WARN(...) ::Minecraft::Log::GetLogger()->warn(__VA_ARGS__)
#define MC_ERROR(...) ::Minecraft::Log::GetLogger()->error(__VA_ARGS__)
#define MC_CRITICAL(...) ::Minecraft::Log::GetLogger()->critical(__VA_ARGS__)
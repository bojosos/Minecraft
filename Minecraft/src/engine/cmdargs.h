#pragma once

#include "common/common.h"

namespace Minecraft
{
	class CommandLineArgs
	{
	public:
		static void Create(int argc, char** argv);
		inline static std::vector<std::string>& Get() { return s_Instance->m_Args; }
	private:
		static Scope<CommandLineArgs> s_Instance;
		CommandLineArgs(int argc, char** argv);
		std::vector<std::string> m_Args;
	};
}
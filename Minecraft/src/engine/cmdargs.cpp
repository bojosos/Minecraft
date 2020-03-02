#include "mcpch.h"
#include "cmdargs.h"

namespace Minecraft
{
	CommandLineArgs::CommandLineArgs(int argc, char** argv) : m_Args(std::vector<std::string>(argv, argv + argc))
	{

	}

	void CommandLineArgs::Create(int argc, char** argv)
	{
		MC_ASSERT(s_Instance, "Only one instance of command line args is allowed!");
		s_Instance = CreateScope<CommandLineArgs>(argc, argv);
	}
}
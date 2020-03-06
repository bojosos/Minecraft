#include "mcpch.h"
#include "cmdargs.h"

namespace Minecraft
{
	CommandLineArgs::CommandLineArgs()
	{

	}

	void CommandLineArgs::Create(int argc, char** argv)
	{
		MC_ASSERT(Instance().m_Args.size() == 0, "Only one instance of command line args is allowed!");
		Instance().m_Args = std::vector<std::string>(argv, argv + argc);
	}
}
#include "mcpch.h"
#include "infolog.h"
#include "common/memory.h"

namespace Minecraft
{
	InfoLog::InfoLog()
	{

	}

	void InfoLog::Init(float logtime)
	{
		Get().m_LogTime = logtime;
	}

	void InfoLog::IUpdate(Timestep ts)
	{
		m_Frames++;
		m_Time += ts;
		while (m_Time >= m_LogTime) {
			m_Time -= m_LogTime;
			MC_WARN("Allocated: {0}, FPS: {1} at {2}ms.", Memory::GetAllocated(), m_Frames, 1.0f / m_Frames * 1000.0f);
			m_Frames = 0;
		}
	}

}
#pragma once
#include "common/timestep.h"

namespace Minecraft
{
	class InfoLog
	{
	public:
		static void Init(float logtime = 1.0f);
		static inline uint32_t GetFps() { return Get().m_Fps; };
		static inline void Update(Timestep ts) { Get().IUpdate(ts); }

		void IUpdate(Timestep ts);
	private:
		static InfoLog& Get()
		{
			static InfoLog instance;
			return instance;
		}
		InfoLog();
		uint32_t m_Frames = 0;
		uint32_t m_Fps = 0;
		float m_LogTime = 1.0f, m_Time = 0.0f;
	};
}
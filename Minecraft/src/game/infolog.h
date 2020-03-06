#pragma once
#include "common/timestep.h"

namespace Minecraft
{
	class InfoLog
	{
	public:
		static void Init(float logtime = 1.0f);
		static inline void Update(Timestep ts) { Get().IUpdate(ts); }

		void IUpdate(Timestep ts);
	private:
		static InfoLog& Get()
		{
			static InfoLog instance;
			return instance;
		}
		InfoLog();
		int32_t m_Time = 0, m_Frames = 0, m_LogTime = 1.0f;
	};
}
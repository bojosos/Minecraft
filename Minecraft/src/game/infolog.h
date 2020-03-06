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
		int32_t m_Frames = 0;
		float m_LogTime = 1.0f, m_Time = 0.0f;
	};
}
#pragma once
#include "common/types.h"

namespace Minecraft
{
	class Panel
	{
	public:
		Panel(Position position);


	private:
		Position m_Position;
		int32_t width, height;

	};
}
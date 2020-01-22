#pragma once

#include "chunk.h"
#include <vector>

namespace Minecraft
{
	class World
	{
	public:
		World(int sizeX, int sizeY, int sizeZ);
		void Update();
	private:
		std::vector<std::vector<std::vector<Ref<Chunk>>>> m_Chunks;
	};
}
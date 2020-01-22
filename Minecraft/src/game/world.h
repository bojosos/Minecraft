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
		inline vertex* GetChunkData() { return m_Chunks[0][0][0].GetRenderData(); }
	private:
		std::vector<std::vector<std::vector<Chunk>>> m_Chunks;
	};
}
#include "mcpch.h"
#include "world.h"

namespace Minecraft
{
	World::World(int sizeX, int sizeY, int sizeZ)
	{

		m_Chunks.resize(sizeX);
		for (int x = 0; x < sizeX; x++)
		{
			m_Chunks[x].resize(sizeY);
			for (int y = 0; y < sizeY; y++)
			{
				m_Chunks[x][y].resize(sizeZ);
				for (int z = 0; z < sizeZ; z++)
				{
					m_Chunks[x][y][z].SetPoisition({ x, y, z });
				}
			}
		}
	}
}
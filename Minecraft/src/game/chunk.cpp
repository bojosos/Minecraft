#include "mcpch.h"
#include "chunk.h"

#include "common/layer/testlayer.h"

namespace Minecraft
{

	Chunk::Chunk()
	{

		memset(m_Blocks, 3, sizeof(m_Blocks) / sizeof(uint8_t));
	}

	Chunk::Chunk(const glm::vec3& position) : m_Position(position)
	{
		memset(m_Blocks, 3, sizeof(m_Blocks) / sizeof(uint8_t));
	}

	void Chunk::Update()
	{
		if (!m_Changed)
			return;
	}

	vertex* Chunk::GetRenderData() const
	{
		vertex* res = new vertex[TOTAL_VERTICES];

		uint32_t i = 0;

		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			for (int y = 0; y < CHUNK_HEIGHT; y++)
			{
				for (int x = 0; x < CHUNK_SIZE; x++)
				{
					uint8_t type = m_Blocks[x][y][z];

					TestLayer::GetData(res, x, y, z, i);
				}
			}
		}
		return res;
	}
}
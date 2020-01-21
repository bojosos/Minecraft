#include "mcpch.h"
#include "chunk.h"

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

	byte4* Chunk::GetRenderData() const
	{
		byte4* res = new byte4[TOTAL_VERTICES];
		uint32_t i = 0;

		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			for (int y = 0; y < CHUNK_HEIGHT; y++)
			{
				for (int x = 0; x < CHUNK_SIZE; x++)
				{
					uint8_t type = m_Blocks[x][y][z];

					//neg x
					res[i++] = byte4(x, y, z, type);
					res[i++] = byte4(x, y, z + 1, type);
					res[i++] = byte4(x, y + 1, z, type);
					res[i++] = byte4(x, y + 1, z, type);
					res[i++] = byte4(x, y, z + 1, type);
					res[i++] = byte4(x, y + 1, z + 1, type);

					//pos x
					res[i++] = byte4(x + 1, y, z, type);
					res[i++] = byte4(x + 1, y + 1, z, type);
					res[i++] = byte4(x + 1, y, z + 1, type);
					res[i++] = byte4(x + 1, y + 1, z, type);
					res[i++] = byte4(x + 1, y + 1, z + 1, type);
					res[i++] = byte4(x + 1, y, z + 1, type);
					//neg y
					res[i++] = byte4(x, y, z, type);
					res[i++] = byte4(x + 1, y, z, type);
					res[i++] = byte4(x, y, z + 1, type);
					res[i++] = byte4(x + 1, y, z, type);
					res[i++] = byte4(x + 1, y, z + 1, type);
					res[i++] = byte4(x, y, z + 1, type);
					//pos y
					res[i++] = byte4(x, y + 1, z, type);
					res[i++] = byte4(x, y + 1, z + 1, type);
					res[i++] = byte4(x + 1, y + 1, z, type);
					res[i++] = byte4(x + 1, y + 1, z, type);
					res[i++] = byte4(x, y + 1, z + 1, type);
					res[i++] = byte4(x + 1, y + 1, z + 1, type);
					//neg z
					res[i++] = byte4(x, y, z, type);
					res[i++] = byte4(x, y + 1, z, type);
					res[i++] = byte4(x + 1, y, z, type);
					res[i++] = byte4(x, y + 1, z, type);
					res[i++] = byte4(x + 1, y + 1, z, type);
					res[i++] = byte4(x + 1, y, z, type);
					//pos z
					res[i++] = byte4(x, y, z + 1, type);
					res[i++] = byte4(x + 1, y, z + 1, type);
					res[i++] = byte4(x, y + 1, z + 1, type);
					res[i++] = byte4(x, y + 1, z + 1, type);
					res[i++] = byte4(x + 1, y, z + 1, type);
					res[i++] = byte4(x + 1, y + 1, z + 1, type);


				}
			}
		}
		return res;
	}
}
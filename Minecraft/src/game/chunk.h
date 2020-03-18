#pragma once

#include "engine/gl/vao.h"
#include <glm/glm.hpp>
#include "block.h"

namespace Minecraft
{
	class Chunk
	{
	public:
		Chunk(const glm::ivec3& position);
		Chunk() = delete;
		Chunk(Chunk& other) = delete;


		inline uint16_t GetBlock(const glm::ivec3& position)  const
		{
			return GetBlock(position.x, position.y, position.z);
		}

		inline uint16_t GetBlock(int x, int y, int z) const
		{
			return m_Blocks && m_Blocks[x][y][z];
		}
		inline void SetBlock(const glm::ivec3& position, uint8_t type)
		{
			SetBlock(position.x, position.y, position.z, type);
		}
		void SetBlock(int x, int y, int z, uint8_t type)
		{
			if (!m_Blocks)
			{
				if (type != 0)
				{
					m_Blocks = new uint16_t * *[CHUNK_SIZE];
					for (int x = 0; x < CHUNK_SIZE; x++)
					{
						m_Blocks[x] = new uint16_t * [CHUNK_SIZE];
						for (int y = 0; y < CHUNK_SIZE; y++)
						{
							m_Blocks[x][y] = new uint16_t[CHUNK_SIZE];
							for (int z = 0; z < CHUNK_SIZE; z++)
							{
								m_Blocks[x][y][z] = 0;
							}
						}
					}
					m_Blocks[x][y][z] = type;
					m_Changed = true;
				}
			}
			else {
				m_Blocks[x][y][z] = type;
				m_Changed = true;
			}

		}
		
		inline void SetPoisition(const glm::ivec3& position) { m_Position = position; }
		inline glm::ivec3 GetPosition() const { return m_Position; }
		inline glm::ivec3 GetAbsolutePosition() const { return m_Position * CHUNK_SIZE; }

		void Update(Vertex* res);
		Vertex* GetRenderData(Vertex* res);
		void Render();
	public:
		Ref<VertexBuffer> m_Vbo;
		Ref<VertexArray> m_Vao;

		uint32_t m_Elements = 0;
		bool m_Changed = true;

		glm::ivec3 m_Position;
		uint16_t*** m_Blocks = nullptr;
	};
}

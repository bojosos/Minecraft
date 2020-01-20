#pragma once

#include "engine/gl/vao.h"
#include <glm/glm.hpp>

#define CHUNK_SIZE 16
#define CHUNK_HEIGHT 16
#define TOTAL_VERTICES CHUNK_SIZE * CHUNK_SIZE * CHUNK_HEIGHT * 36

namespace Minecraft
{
	class Chunk
	{
	public:
		Chunk();
		Chunk(const glm::vec3& position);

		inline void SetPoisition(const glm::vec3& position) { m_Position = position; }

		inline uint8_t GetBlock(const glm::vec3& position)  const
		{
			return GetBlock((int)position.x, (int)position.y, (int)position.z);
		}

		inline uint8_t GetBlock(int x, int y, int z) const
		{
			return m_Blocks[x][y][z];
		}
		inline void SetBlock(const glm::vec3& position, uint8_t type)
		{
			SetBlock((int)position.x, (int)position.y, (int)position.z, type);
			m_Changed = true;
		}
		inline void SetBlock(int x, int y, int z, uint8_t type)
		{
			m_Blocks[x][y][z] = type;
			m_Changed = true;
		}
		inline glm::vec3 GetPosition() const { return m_Position; }
		
		void Update();
		byte4* GetRenderData() const;
	private:
		bool m_Changed = true;
		glm::vec3 m_Position;
		uint8_t m_Blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_HEIGHT];
	};
}

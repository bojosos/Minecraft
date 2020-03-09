#pragma once

#include "engine/gl/vao.h"
#include <glm/glm.hpp>
#include "block.h"

#define CHUNK_SIZE 16
#define TOTAL_VERTICES CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 36

namespace Minecraft
{
	class Chunk
	{
	public:
		Chunk(const glm::ivec3& position);
		Chunk() = delete;
		Chunk(Chunk& other) = delete;

		inline void SetPoisition(const glm::ivec3& position) { m_Position = position; }

		inline uint16_t GetBlock(const glm::ivec3& position)  const
		{
			return GetBlock(position.x, position.y, position.z);
		}

		inline uint16_t GetBlock
		(int x, int y, int z) const
		{
			return m_Blocks[x][y][z];
		}
		inline void SetBlock(const glm::ivec3& position, uint8_t type)
		{
			SetBlock(position.x, position.y, position.z, type);
		}
		void SetBlock(int x, int y, int z, uint8_t type)
		{
			m_Blocks[x][y][z] = type;
			m_Changed = true;
		}
		inline glm::ivec3 GetPosition() const { return m_Position; }

		void Update(vertex* res);
		inline glm::mat4& GetTransformationMatrix()
		{
			return m_Transform;
		}

		void BufferData(vertex* res);
		void Render();

		vertex* GetRenderData(vertex* res);
	public:
		glm::mat4 m_Transform;
		Ref<VertexBuffer> m_Vbo;
		Ref<VertexArray> m_Vao;

		uint32_t m_Elements = 0;
		changed m_Changed = true;

		glm::ivec3 m_Position;
		uint16_t m_Blocks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	};
}

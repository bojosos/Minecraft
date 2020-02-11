#include "mcpch.h"
#include "chunk.h"

#include "common/layer/testlayer.h"
#include <glad/glad.h>

namespace Minecraft
{

	Chunk::Chunk()
	{
		m_Position = glm::vec3(1.0f);
		memset(m_Blocks, 3, 4096);
		m_Transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x * CHUNK_SIZE, m_Position.y * CHUNK_SIZE, m_Position.z * CHUNK_SIZE
		));
	}

	Chunk::Chunk(const glm::vec3& position) : m_Position(position)
	{
		memset(m_Blocks, 3, 4096);
		m_Transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x * CHUNK_SIZE, m_Position.y * CHUNK_SIZE, m_Position.z * CHUNK_SIZE
		));
		m_Vao = CreateRef<VertexArray>();
	}

	void Chunk::Update(vertex* res)
	{
		if (!m_Changed)
			return;
		m_Changed = false;
		GetRenderData(res);
	}

	void Chunk::BufferData(vertex* res)
	{
		GetRenderData(res);
	}

	vertex* Chunk::GetRenderData(vertex* res) 
	{
		uint32_t i = 0;

		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				for (int x = 0; x < CHUNK_SIZE; x++)
				{
					uint8_t type = m_Blocks[x][y][z];

					TestLayer::GetData(res, x, y, z, i);
				}
			}
		}
		m_Elements = i;
		if (!m_Vbo)
		{
			m_Vbo = CreateRef<VertexBuffer>(res, TOTAL_VERTICES * 5);
			m_Vbo->SetLayout({
							 {ShaderDataType::Byte3, "a_Coordinates"},
							 {ShaderDataType::Byte2, "a_TexCoords"}
					 		 });
			m_Vao->AddVertexBuffer(m_Vbo);
		}
		return nullptr;
	}

	void Chunk::Render()
	{
		m_Vao->Bind();
		glDrawArrays(GL_TRIANGLES, 0, TOTAL_VERTICES);
	}
}
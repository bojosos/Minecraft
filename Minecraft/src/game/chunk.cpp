#include "mcpch.h"
#include "engine.h"

#include "chunk.h"
#include "world.h"
#include "game/blockloader.h"
#include <glad/glad.h>
#include <glm/gtc/noise.hpp>

namespace Minecraft
{

	Chunk::Chunk(const glm::vec3& position) : m_Position(position)
	{
		m_Transform = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position.x * CHUNK_SIZE, m_Position.y * CHUNK_SIZE, m_Position.z * CHUNK_SIZE));
		m_Vao = CreateRef<VertexArray>();
	}

	void Chunk::Update(vertex* res)
	{
		if (!m_Changed)
			return;
		m_Changed = false;
		GetRenderData(res);
		MC_INFO("Updating chunk at {0}, {1}, {2}", m_Position.x, m_Position.y, m_Position.z);
	}

	void Chunk::BufferData(vertex* res)
	{
		GetRenderData(res);
	}

	vertex* Chunk::GetRenderData(vertex* res) 
	{
		MC_INFO(m_Elements);
		uint32_t i = 0;
		m_Elements = 0;

		for (int z = 0; z < CHUNK_SIZE; z++)
		{
			for (int y = 0; y < CHUNK_SIZE; y++)
			{
				for (int x = 0; x < CHUNK_SIZE; x++)
				{
					uint16_t type = m_Blocks[x][y][z];
					if (type == 0)
						continue;

					if (World::GetOverworld().GetBlock(x - 1, y, z, this).IsTransparent())
					{
						BlockLoader::GetLeftVertexData(res, x, y, z, type, i);
					}

					if (World::GetOverworld().GetBlock(x + 1, y, z, this).IsTransparent())
					{
						BlockLoader::GetRightVertexData(res, x, y, z, type, i);
					}

					if (World::GetOverworld().GetBlock(x, y - 1, z, this).IsTransparent())
					{
						BlockLoader::GetDownVertexData(res, x, y, z, type, i);
					}

					if (World::GetOverworld().GetBlock(x, y + 1, z, this).IsTransparent())
					{
						BlockLoader::GetUpVertexData(res, x, y, z, type, i);
					}

					if (World::GetOverworld().GetBlock(x, y, z + 1, this).IsTransparent())
					{
						BlockLoader::GetBackVertexData(res, x, y, z, type, i);
					}

					if (World::GetOverworld().GetBlock(x, y, z - 1, this).IsTransparent())
					{
						BlockLoader::GetFrontVertexData(res, x, y, z, type, i);
					}
				}
			}
		}
		m_Elements = i;

		if (!m_Vbo)
		{
			m_Vbo = CreateRef<VertexBuffer>(res, m_Elements * 6);
			m_Vbo->SetLayout({
							 {ShaderDataType::Byte3, "a_Coordinates"},
							 {ShaderDataType::Byte2, "a_TexCoords"},
							 {ShaderDataType::Byte, "a_Tid"}
					 		 });
			m_Vao->AddVertexBuffer(m_Vbo);
		}
		else
		{
			m_Vbo->SetData(res, m_Elements * 6);
		}
		MC_INFO(m_Elements);
		return nullptr;
	}

	void Chunk::Render()
	{
		m_Vao->Bind();
		glDrawArrays(GL_TRIANGLES, 0, m_Elements);
	}
}
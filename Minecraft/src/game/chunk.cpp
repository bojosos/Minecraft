#include "mcpch.h"
#include "engine.h"

#include "chunk.h"
#include "world.h"
#include "game/blockloader.h"

#ifdef MC_WEB
#include <GLES3/gl32.h>
#else
#include <glad/glad.h>
#endif

#include <glm/gtc/noise.hpp>

namespace Minecraft
{

	Chunk::Chunk(const glm::ivec3& position) : m_Position(position)
	{
		m_Vao = VertexArray::Create();
	}

	void Chunk::Update(Vertex* res)
	{
		if (!m_Changed || !m_Blocks)
			return;
		m_Changed = false;
		GetRenderData(res);
	}

	Vertex* Chunk::GetRenderData(Vertex* res) 
	{
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

#ifndef MC_DRAW_ALL
					if (World::GetOverworld().GetBlock(x - 1, y, z, this).IsTransparent())
#endif
					{
						BlockLoader::GetLeftVertexData(res, x, y, z, type, i);
					}
#ifndef MC_DRAW_ALL
					if (World::GetOverworld().GetBlock(x + 1, y, z, this).IsTransparent())
					{
						BlockLoader::GetRightVertexData(res, x, y, z, type, i);
					}
#endif
#ifndef MC_DRAW_ALL
					if (World::GetOverworld().GetBlock(x, y - 1, z, this).IsTransparent())
					{
						BlockLoader::GetDownVertexData(res, x, y, z, type, i);
					}
#endif
#ifndef MC_DRAW_ALL
					if (World::GetOverworld().GetBlock(x, y + 1, z, this).IsTransparent())
#endif
					{
						BlockLoader::GetUpVertexData(res, x, y, z, type, i);
					}
#ifndef MC_DRAW_ALL
					if (World::GetOverworld().GetBlock(x, y, z + 1, this).IsTransparent())
#endif
					{
						BlockLoader::GetBackVertexData(res, x, y, z, type, i);
					}
#ifndef MC_DRAW_ALL
					if (World::GetOverworld().GetBlock(x, y, z - 1, this).IsTransparent())
#endif
					{
						BlockLoader::GetFrontVertexData(res, x, y, z, type, i);
					}
				}
			}
		}
		m_Elements = i;

		if (m_Elements)
		{
			if (!m_Vbo)
			{
				m_Vbo = VertexBuffer::Create(res, m_Elements * 6);
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
		}
		return nullptr;
	}

	void Chunk::Render()
	{
		if (m_Elements)
		{
			m_Vao->Bind();
			glDrawArrays(GL_TRIANGLES, 0, m_Elements);
		}
	}
}
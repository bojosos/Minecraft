#include "mcpch.h"
#include "blockloader.h"
#include "world.h"
#include "common/memory.h"
#ifdef MC_WEB
#include <GLFW/glfw3.h>
#else
#include <glad/glad.h>
#endif
#include "player.h"
//#include <glad/glad.h> // Not for here, Renderer please
#include "engine/gl/renderer/renderer.h" // For here

namespace Minecraft
{
	World* World::s_World;

	World::World()
	{
		s_World = this;

		CreateChunks();
		GenerateTerrain();

		m_Buffer = new Vertex[TOTAL_VERTICES / 3];

#ifndef MC_WEB
		m_Shader = Shader::Create("shaders/outline.glsl");
		m_Shader->RetrieveLocations({ "u_ViewMatrix", "u_ProjectionMatrix", "u_Position" });
		m_Vao = VertexArray::Create();
		float verts[18] = {
			0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		};

		m_Vbo = VertexBuffer::Create(verts, 24 * sizeof(float));
		m_Vbo->SetLayout({ {ShaderDataType::Float3, "a_Coords"} });
		m_Vao->AddVertexBuffer(m_Vbo);
#endif
	}
	void World::CreateChunks()
	{
		m_Chunks.resize(WORLD_SIZE);
		for (int x = 0; x < WORLD_SIZE; x++)
		{
			m_Chunks[x].resize(WORLD_SIZE);
			for (int y = 0; y < WORLD_SIZE; y++)
			{

				m_Chunks[x][y].resize(WORLD_SIZE);
				for (int z = 0; z < WORLD_SIZE; z++)
				{
					m_Chunks[x][y][z] = new Chunk(glm::vec3(x, y, z));
				}
			}
		}
	}

	void World::GenerateTerrain()
	{
 		int* heights = new int[CHUNK_SIZE * CHUNK_SIZE];
		NoiseOptions firstNoise;
		firstNoise.Amplitude = 105;
		firstNoise.Octaves = 6;
		firstNoise.Smoothness = 205.f;
		firstNoise.Roughness = 0.58f;
		firstNoise.Offset = 18;
		firstNoise.Seed = 0;
		firstNoise.NoiseFunc = NoiseFunc::PERLIN;

		NoiseOptions secondNoise;
		secondNoise.Amplitude = 20;
		secondNoise.Octaves = 4;
		secondNoise.Smoothness = 200;
		secondNoise.Roughness = 0.45f;
		secondNoise.Offset = 0;
		secondNoise.Seed = 0;
		secondNoise.NoiseFunc = NoiseFunc::PERLIN;

		for (int x = 0; x < WORLD_SIZE; x++)
		{
			for (int z = 0; z < WORLD_SIZE; z++)
			{
				m_Generator.CreateChunkHeightMap(firstNoise, secondNoise, x, z, heights);
				for (int y = 0; y < WORLD_SIZE; y++)
				{
					for (uint32_t xx = 0; xx < CHUNK_SIZE; xx++)
					{
						for (uint32_t zz = 0; zz < CHUNK_SIZE; zz++)
						{
							int height = heights[xx * CHUNK_SIZE + zz];
							for (uint32_t yy = 0; yy < CHUNK_SIZE; yy++)
							{
								int by = y * CHUNK_SIZE + yy;
								int bid = 0;
								if (by > height)
								{
									if (by < WATER_LEVEL)
									{
										bid = 0;// BlockLoader::GetBlockId("air");
									}
								}
								else if (by == height)
								{
									if (by < WATER_LEVEL + 3)
									{
										bid = 5;//BlockLoader::GetBlockId("sand");
									}
									else
									{
										// Tree, Cactus, Grass
										bid = 2;//BlockLoader::GetBlockId("grass");
									}
								}
								else if (by > height - 5) 
								{
									bid = 1;//BlockLoader::GetBlockId("dirt");
								}
								else
								{
									bid = 4;// BlockLoader::GetBlockId("stone");
								}
								m_Chunks[x][y][z]->SetBlock(xx, yy, zz, bid);
							}
						}
					}
				}
			}
		}
	}

	void World::AddPlayer(Player* player)
	{
		m_Players.push_back(player);
	}

	void World::Place(int32_t x, int32_t y, int32_t z, const glm::vec3& face)
	{

	}

	void World::Break(int32_t x, int32_t y, int32_t z)
	{

	}

	void World::Update(const Ref<Shader>& shader)
	{
		for (int i=0;i<m_Chunks.size();i++)
		{
			for (int j = 0; j < m_Chunks[i].size(); j++)
			{
				for (int k = 0; k < m_Chunks[i][j].size(); k++) {
					m_Chunks[i][j][k]->Update(m_Buffer);
				}
			}
		}

		shader->Bind();
		for (int i = 0; i < m_Chunks.size(); i++)
		{
			for (int j = 0; j < m_Chunks[i].size(); j++)
			{
				for (int k = 0; k < m_Chunks[i][j].size(); k++) {
					if (m_Chunks[i][j][k]->m_Blocks && m_Players.front()->IsChunkVisible(m_Chunks[i][j][k]->GetPosition()))
					{
						shader->SetFloat3("u_ChunkPosition", m_Chunks[i][j][k]->GetPosition());
						m_Chunks[i][j][k]->Render();
					}
				}
			}
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Block& World::GetBlock(int8_t x, int8_t y, int8_t z, Chunk* chunk)
	{
		if (x == -1 || y == -1 || z == -1 || x == CHUNK_SIZE || y == CHUNK_SIZE || z == CHUNK_SIZE)
		{
			return BlockLoader::GetBlock(0);
		}

		glm::ivec3 pos = chunk->GetPosition();
		return BlockLoader::GetBlock(m_Chunks[pos.x][pos.y][pos.z]->GetBlock(x, y, z));
	}

	Block& World::GetBlock(int32_t x, int32_t y, int32_t z)
	{
		int32_t cX = x / CHUNK_SIZE;
		int32_t cXx = abs(x % CHUNK_SIZE);
		int32_t cY = y / CHUNK_SIZE;
		int32_t cYy = abs(y % CHUNK_SIZE);
		int32_t cZ = z / CHUNK_SIZE;
		int32_t cZz = abs(z % CHUNK_SIZE);

		return BlockLoader::GetBlock(m_Chunks[cX][cY][cZ]->GetBlock(cXx, cYy, cZz));
	}

	void World::DrawOutline(int32_t x, int32_t y, int32_t z, const glm::vec3& face)
	{
#ifndef MC_WEB
		m_Shader->Bind();
		glm::mat4 mat = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

		m_Vao->Bind();
		m_Shader->SetMat4("u_Position", mat);
		m_Shader->SetMat4("u_ViewMatrix", m_Players.front()->GetViewMatrix());
		m_Shader->SetMat4("u_ProjectionMatrix", m_Players.front()->GetProjectionMatrix());
		glDrawArrays(GL_TRIANGLES, 0, 6);
#endif
	}

	void World::SetBlock(int32_t x, int32_t y, int32_t z, uint32_t id)
	{
		int32_t cX = x / CHUNK_SIZE;
		int32_t cXx = abs(x % CHUNK_SIZE);
		int32_t cY = y / CHUNK_SIZE;
		int32_t cYy = abs(y % CHUNK_SIZE);
		int32_t cZ = z / CHUNK_SIZE;
		int32_t cZz = abs(z % CHUNK_SIZE);
		m_Chunks[cX][cY][cZ]->SetBlock(cXx, cYy, cZz, id);
	}
}

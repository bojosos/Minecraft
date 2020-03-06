#include "mcpch.h"
#include "blockloader.h"
#include "world.h"
#include "engine/gl/renderer/renderer.h"
#include "common/memory.h"
#include <glm/gtc/noise.hpp>
#include <glad/glad.h>

namespace Minecraft
{
	float stoneBaseHeight = -24;
	float stoneBaseNoise = 0.05f;
	float stoneBaseNoiseHeight = 4;
	float stoneMountainHeight = 20;
	float stoneMountainFrequency = 0.08f;
	float stoneMinHeight = -12;
	float dirtBaseHeight = 20;
	float dirtNoise = 0.04f;
	float dirtNoiseHeight = 3;
	int stoneHeight = floor(stoneBaseHeight);

	World* World::s_World;

	World::World()
	{
		s_World = this;

		m_Chunks.resize(10);
		for (int x = 0; x < 10; x++)
		{
			m_Chunks[x].resize(10);
			for (int y = 0; y < 10; y++)
			{

				m_Chunks[x][y].resize(10);
				for (int z = 0; z < 10; z++)
				{
					float heights1[16][16];
					for (int i = 0; i < 16; i++)
						for (int j = 0; j < 16; j++)
							heights1[i][j] = glm::perlin(glm::vec2((x * stoneMountainFrequency + i), (z * stoneMountainFrequency + j))) * stoneMountainHeight;

					float heights2[16][16];
					for (int i = 0; i < 16; i++)
						for (int j = 0; j < 16; j++)
							heights2[i][j] = glm::perlin(glm::vec2((x * stoneBaseNoise + i), (z * stoneBaseNoise + j))) * stoneBaseNoiseHeight;

					float heights3[16][16];
					for (int i = 0; i < 16; i++)
						for (int j = 0; j < 16; j++)
							heights3[i][j] = glm::perlin(glm::vec2((x + i) * dirtNoise, (z + j) * dirtNoise)) * dirtNoiseHeight;

					m_Chunks[x][y][z] = new Chunk(glm::vec3(x, y, z));
					for (int xx = 0; xx < CHUNK_SIZE; xx++)
					{
						for (int zz = 0; zz < CHUNK_SIZE; zz++)
						{
							int cposy = CHUNK_SIZE * y;
							for (int yy = 0; yy < CHUNK_SIZE; yy++)
							{
								int stoneHeight = stoneBaseHeight;
								stoneHeight += heights1[xx][zz];
								if (stoneHeight < stoneMinHeight)
									stoneHeight = stoneMinHeight;
								stoneHeight += heights2[xx][zz];
								int dirtHeight = stoneHeight + dirtBaseHeight;
								dirtHeight += heights3[xx][zz];

								if (cposy + yy <= stoneHeight)
								{
									m_Chunks[x][y][z]->SetBlock(xx, yy, zz, BlockLoader::GetBlockId("stone"));
								}
								else
								if (cposy + yy <= dirtHeight) {
									m_Chunks[x][y][z]->SetBlock(xx, yy, zz, BlockLoader::GetBlockId("grass"));
								}
								else
								{
									m_Chunks[x][y][z]->SetBlock(xx, yy, zz, 0);
								}
								/*
								if (cposy + yy > heights[xx][zz])
								{
									m_Chunks[x][y][z]->SetBlock(xx, yy, zz, 0);
								}
								else
								{

									stoneHeight += GetNoise(heights[xx][zz] * stoneMountainFrequency, , floor(stoneMountainHeight));
									if (stoneHeight < stoneMinHeight)
										stoneHeight = floor(stoneMinHeight);
									stoneHeight += GetNoise(x, 0, z, stoneBaseNoise, floor(stoneBaseNoiseHeight));
									int dirtHeight = stoneHeight + floor(dirtBaseHeight);
									dirtHeight += GetNoise(x, 100, z, dirtNoise, floor(dirtNoiseHeight));
									if()
									m_Chunks[x][y][z]->SetBlock(xx,yy,zz, BlockLoader::GetBlockId("grass"));
									m_Chunks[x][y][z]->SetBlock(xx, yy, zz, BlockLoader::GetBlockId("stone"));
								}*/
							}
						}
					}
				}
			}
		}
		m_Shader = Shader::Create("res/shaders/outline.glsl");
		m_Shader->RetrieveLocations({ "u_ViewMatrix", "u_ProjectionMatrix", "u_Position" });
		m_Vao = VertexArray::Create();
		float verts[18] = {
			0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		};

		m_Vbo = VertexBuffer::Create(verts, 24 * sizeof(float));
		m_Vbo->SetLayout({ {ShaderDataType::Float3, "a_Coords"} });
		m_Vao->AddVertexBuffer(m_Vbo);
	}

	void World::Update(const Ref<Shader>& shader, const Ref<ViewFrustum>& frustum)
	{
		vertex* res = new vertex[TOTAL_VERTICES];
		for (int i=0;i<m_Chunks.size();i++)
		{
			for (int j = 0; j < m_Chunks[i].size(); j++)
			{
				for (int k = 0; k < m_Chunks[i][j].size(); k++) {
					m_Chunks[i][j][k]->Update(res);
				}
			}
		}

		delete[] res;

		shader->Bind();
		for (int i = 0; i < m_Chunks.size(); i++)
		{
			for (int j = 0; j < m_Chunks[i].size(); j++)
			{
				for (int k = 0; k < m_Chunks[i][j].size(); k++) {
					if (frustum->ChunkIsInFrustum(m_Chunks[i][j][k]->GetPosition()))
					{
						shader->SetMat4("u_Transform", m_Chunks[i][j][k]->GetTransformationMatrix());
						m_Chunks[i][j][k]->Render();
					}
				}
			}
		}
	}

	Block& World::GetBlock(int8_t x, int8_t y, int8_t z, Chunk* chunk)
	{
		if (x == -1 || y == -1 || z == -1 || x == CHUNK_SIZE || y == CHUNK_SIZE || z == CHUNK_SIZE)
		{
			return BlockLoader::GetBlock(0);
		}

		glm::vec3 pos = chunk->GetPosition();
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

	void World::DrawOutline(int32_t x, int32_t y, int32_t z, const glm::vec3& face, const Ref<Camera>& cam)
	{
		m_Shader->Bind();
		glm::mat4 mat(1.0f);
		mat = glm::translate(mat, glm::vec3(x, y, z));

		m_Vao->Bind();
		m_Shader->SetMat4("u_Position", mat);
		m_Shader->SetMat4("u_ViewMatrix", cam->GetViewMatrix());
		m_Shader->SetMat4("u_ProjectionMatrix", cam->GetProjectionMatrix());
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void World::SetBlock(int32_t x, int32_t y, int32_t z, uint32_t id)
	{
		MC_INFO("Wut2");
		int32_t cX = x / CHUNK_SIZE;
		int32_t cXx = abs(x % CHUNK_SIZE);
		int32_t cY = y / CHUNK_SIZE;
		int32_t cYy = abs(y % CHUNK_SIZE);
		int32_t cZ = z / CHUNK_SIZE;
		int32_t cZz = abs(z % CHUNK_SIZE);
		m_Chunks[cX][cY][cZ]->SetBlock(cXx, cYy, cZz, id);
		m_Chunks[cX][cY][cZ]->m_Changed = true;
		m_Chunks[cX][cY][cZ]->m_Blocks[cXx][cYy][cZz] = id;
		//vertex* test = new vertex[TOTAL_VERTICES];
		//m_Chunks[cX][cY][cZ]->GetRenderData(test);
		//m_Chunks[cX][cY][cZ]->Render();
		//delete[] test;
	}
}

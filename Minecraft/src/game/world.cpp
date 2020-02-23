#include "mcpch.h"
#include "blockloader.h"
#include "world.h"

#include "engine/gl/renderer.h"
#include <glad/glad.h>

namespace Minecraft
{

	World::World()
	{
		m_Chunks.resize(10);
		for (int x = 0; x < 10; x++)
		{
			m_Chunks[x].resize(10);
			for (int y = 0; y < 10; y++)
			{
				m_Chunks[x][y].resize(10);
				for (int z = 0; z < 10; z++)
				{
					m_Chunks[x][y][z] = new Chunk(glm::vec3(x, y, z));
				}
			}
		}
	}

	void World::Update(const Ref<Shader>& shader, const Ref<ViewFrustum>& frustum)
	{
		vertex* res = new vertex[TOTAL_VERTICES];
		for (auto ccc : m_Chunks)
		{
			for (auto cc : ccc)
			{
				for (auto c : cc) {
					c->Update(res);
				}
			}
		}
		delete[] res;

		shader->Bind();
		for (auto ccc : m_Chunks)
		{
			for (auto cc : ccc)
			{
				for (auto c : cc) {
					if (frustum->ChunkIsInFrustum(c->GetPosition()))
					{
						shader->SetMat4("u_Transform", c->GetTransformationMatrix());
						c->Render();
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
		/*
		if (x == -1)
		{
			glm::vec3 pos = chunk->GetPosition();
			return BlockLoader::GetBlock(m_Chunks[pos.x - 1][pos.y][pos.z]->GetBlock(CHUNK_SIZE - 1, y, z));
		}

		if (y == -1)
		{
			glm::vec3 pos = chunk->GetPosition();
			return BlockLoader::GetBlock(m_Chunks[pos.x][pos.y - 1][pos.z]->GetBlock(x, CHUNK_SIZE - 1, z));
		}

		if (z == -1)
		{
			glm::vec3 pos = chunk->GetPosition();
			return BlockLoader::GetBlock(m_Chunks[pos.x][pos.y][pos.z - 1]->GetBlock(x, y, CHUNK_SIZE - 1));
		}

		if (x == CHUNK_SIZE)
		{
			glm::vec3 pos = chunk->GetPosition();
			return BlockLoader::GetBlock(m_Chunks[pos.x + 1][pos.y][pos.z]->GetBlock(0, y, z));
		}

		if (y == CHUNK_SIZE)
		{
			glm::vec3 pos = chunk->GetPosition();
			return BlockLoader::GetBlock(m_Chunks[pos.x][pos.y + 1][pos.z]->GetBlock(x, 0, z));
		}

		if (z == CHUNK_SIZE)
		{
			glm::vec3 pos = chunk->GetPosition();
			return BlockLoader::GetBlock(m_Chunks[pos.x][pos.y][pos.z + 1]->GetBlock(x, y, 0));
		}
		*/
	}
}
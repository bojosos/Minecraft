#include "mcpch.h"
#include "world.h"

#include "engine/gl/renderer.h"
#include <glad/glad.h>

namespace Minecraft
{
	World::World(int sizeX, int sizeY, int sizeZ)
	{
		m_Chunks.resize(sizeX);
		for (int x = 0; x < sizeX; x++)
		{
			m_Chunks[x].resize(sizeY);
			for (int y = 0; y < sizeY; y++)
			{
				m_Chunks[x][y].resize(sizeZ);
				for (int z = 0; z < sizeZ; z++)
				{
					m_Chunks[x][y][z] = CreateRef<Chunk>(glm::vec3(x, y, z));
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
}
#pragma once

#include "engine.h"
#include "chunk.h"
#include "block.h"
#include "generator.h"

namespace Minecraft
{
	class Player;

	class World
	{
	public:
		World();

		void Update(const Ref<Shader>& shader);
		void AddPlayer(Player* player);

		Block& GetBlock(int8_t x, int8_t y, int8_t z, Chunk* chunk);
		Block& GetBlock(int32_t x, int32_t y, int32_t z);

		void SetBlock(int32_t x, int32_t y, int32_t z, uint32_t id);
		void Break(int32_t x, int32_t y, int32_t z);
		void Place(int32_t x, int32_t y, int32_t z, const glm::vec3& face);
		void DrawOutline(int32_t x, int32_t y, int32_t z, const glm::vec3& face);

		static inline World& GetOverworld()
		{
			return *s_World;
		}

	private:
		void CreateChunks();
		void GenerateTerrain();

	private:
		std::vector<Player*> m_Players;
		Vertex* m_Buffer;
		static World* s_World;
		WorldGenerator m_Generator;

		std::vector<std::vector<std::vector<Chunk*>>> m_Chunks;
		Ref<VertexArray> m_Vao;
		Ref<VertexBuffer> m_Vbo;
		Ref<Shader> m_Shader;
	};
}
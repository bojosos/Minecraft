#pragma once

#include "engine.h"
#include "chunk.h"
#include "block.h"

namespace Minecraft
{
	class World
	{
	public:
		World();

		void Update(const Ref<Shader>& shader, const Ref<ViewFrustum>& frustm);

		Block& GetBlock(int8_t x, int8_t y, int8_t z, Chunk* chunk);
		Block& GetBlock(int32_t x, int32_t y, int32_t z);

		void SetBlock(int32_t x, int32_t y, int32_t z, uint32_t id);
		void DrawOutline(int32_t x, int32_t y, int32_t z, const Ref<Camera>& cam);

		static World& GetOverworld()
		{
			static World instance;
			return instance;
		}
	private:
		std::vector<std::vector<std::vector<Chunk*>>> m_Chunks;
		Ref<VertexArray> m_Vao;
		Ref<VertexBuffer> m_Vbo;
		Ref<Shader> m_Shader;
	};
}
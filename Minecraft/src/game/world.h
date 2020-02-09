#pragma once

#include "chunk.h"
#include "engine/gl/shader.h"
#include "engine/gl/frustum.h"
#include <vector>

namespace Minecraft
{
	class World
	{
	public:
		World(int sizeX, int sizeY, int sizeZ);
		void Update(const Ref<Shader>& shader, const Ref<ViewFrustum>& frustm);
	private:
		std::vector<std::vector<std::vector<Ref<Chunk>>>> m_Chunks;
	};
}
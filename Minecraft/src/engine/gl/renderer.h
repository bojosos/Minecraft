#pragma once

#include "game/chunk.h"
#include <glm/glm.hpp>

namespace Minecraft
{
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void SetViewport(int x, int y, int width, int height);
		static void Clear();
		static void SetClearColor(const glm::vec4& color);

		static void Submit(const Ref<Chunk>& chunk);

	};
}
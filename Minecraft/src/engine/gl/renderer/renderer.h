#pragma once

#include "game/chunk.h"
#include "engine/ui/font.h"
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
		static void DrawString(const Ref<Font>& font, const std::string& text, const glm::vec3& position, const glm::vec4& color);

	private:
		static BufferLayout m_Layout;
	};
}
#pragma once

#include "engine/ui/ui.h"
#include <glm/glm.hpp>

namespace Minecraft
{
	class BatchRenderer2D
	{
	public:
		static void Init();
		static void Push(const glm::mat4& matrix, bool override);
		static void Pop();
		static void Submit(const Ref<UIElement>& element);
		static void Begin();
		static void End();
		static void Flush();
		static void DrawString(const Ref<Font>& font, const std::string& text, const glm::vec3& position, uint32_t color);
	};
}
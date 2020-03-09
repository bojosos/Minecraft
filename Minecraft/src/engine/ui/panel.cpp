#include "mcpch.h"
#include "panel.h"
#include "engine/gl/renderer/batchrenderer2d.h"

namespace Minecraft
{
	Panel::Panel(const glm::vec3& position) : UIElement(position, glm::vec2(0.0f), nullptr, 0xffffffff)
	{

	}

	Panel::Panel(const glm::vec3& position, const Ref<Texture>& texture) : UIElement(position, glm::vec2(0.0f), nullptr, 0xffffffff)
	{

	}

	void Panel::Submit(BatchRenderer2D* renderer)
	{
		renderer->Submit(this);
	}
}
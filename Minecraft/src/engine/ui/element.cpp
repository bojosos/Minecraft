#include "mcpch.h"
#include "element.h"
#include "engine/gl/renderer/batchrenderer2d.h"

namespace Minecraft
{

	UIElement::UIElement(const glm::vec3& pos, const glm::vec2& size, const Ref<Texture>& texture, uint32_t color) : m_Position(pos), m_Color(color), m_Size(size), m_Texture(texture)
	{

	}

	void UIElement::OnMousePressed(Event& e)
	{
		e.Handled = true;
	}
}

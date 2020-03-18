#include "mcpch.h"
#include "element.h"
#include "engine/gl/renderer/batchrenderer2d.h"

namespace Minecraft
{

	UIElement::UIElement(const Rectangle& bounds, const Ref<Texture>& texture, uint32_t color) : m_Bounds(bounds), m_Color(color), m_Texture(texture)
	{

	}

	void UIElement::OnMousePressed(Event& e)
	{
		e.Handled = true;
	}
}

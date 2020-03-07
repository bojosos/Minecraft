#include "mcpch.h"
#include "element.h"

namespace Minecraft
{

	UIElement::UIElement(const glm::vec3& pos) : m_Position(pos)
	{

	}

	void UIElement::OnMousePressed(Event& e)
	{
		e.Handled = true;
	}
}

#include "mcpch.h"
#include "panel.h"
#include "engine/gl/renderer/batchrenderer2d.h"

namespace Minecraft
{
	Panel::Panel(const Rectangle& bounds) : UIElement(bounds, nullptr, 0xffffffff)
	{

	}

	Panel::Panel(const Rectangle& bounds, const Ref<Texture>& texture) : UIElement(bounds, nullptr, 0xffffffff)
	{

	}

	void Panel::Submit(BatchRenderer2D* renderer)
	{
		renderer->FillRect(m_Bounds, m_Color);
	}
}
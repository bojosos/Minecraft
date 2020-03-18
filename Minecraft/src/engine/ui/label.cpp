#include "mcpch.h"
#include "label.h"
#include "engine/gl/texture.h"
#include "engine/gl/renderer/batchrenderer2d.h"

namespace Minecraft
{
	Label::Label(const std::string& text, const Ref<Font>& font, const Rectangle& bounds) : UIElement(bounds, nullptr, 0xffffffff), m_Text(text), m_Font(font)
	{
		m_Bounds.Width = FontManager::GetWidth(font, text);
		m_Bounds.Height = FontManager::GetHeight(font, text);
	}

	Label::Label(const std::string& text, const Ref<Font>& font, const Rectangle& bounds, uint32_t color) : UIElement(bounds, nullptr, color), m_Text(text), m_Font(font)
	{
		m_Bounds.Width = FontManager::GetWidth(font, text);
		m_Bounds.Height = FontManager::GetHeight(font, text);
	}

	void Label::OnMousePressed(Event& e)
	{

	}

	void Label::Submit(BatchRenderer2D* renderer)
	{
		renderer->DrawString(m_Text, m_Bounds.X, m_Bounds.Y, m_Font, m_Color);
	}

}
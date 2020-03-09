#include "mcpch.h"
#include "label.h"
#include "engine/gl/texture.h"
#include "engine/gl/renderer/batchrenderer2d.h"

namespace Minecraft
{
	Label::Label(const std::string& text, const Ref<Font>& font, const glm::vec3& pos) : UIElement(pos, glm::vec2(0.0f), nullptr, 0xffffffff), m_Text(text), m_Font(font)
	{

	}

	Label::Label(const std::string& text, const Ref<Font>& font, const glm::vec3& pos, uint32_t color) : UIElement(pos, glm::vec2(0.0f), nullptr, color), m_Text(text), m_Font(font)
	{

	}

	Label::Label(const std::string& text, const Ref<Font>& font, const glm::vec3& pos, const glm::vec3& size, uint32_t color) : UIElement(pos, size, nullptr, color), m_Text(text), m_Font(font)
	{

	}

	void Label::OnMousePressed(Event& e)
	{

	}

	void Label::Submit(BatchRenderer2D* renderer)
	{
		renderer->DrawString(m_Text, m_Position, m_Font, m_Color);
	}

}
#pragma once
#include "element.h"
#include "font.h"

namespace Minecraft
{
	class Label : public UIElement
	{
	public:
		Label(const std::string& text, const Ref<Font>& font, const Rectangle& bounds);
		Label(const std::string& text, const Ref<Font>& font, const Rectangle& bounds, uint32_t color);

		virtual void OnMousePressed(Event& e) override;

		const inline std::string& GetText() const { return m_Text; }
		inline void SetText(const std::string& text) { m_Text = text; }

		void Submit(BatchRenderer2D* renderer) override;

	private:
		std::string m_Text;
		Ref<Font> m_Font;
	};
}
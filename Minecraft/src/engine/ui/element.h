#pragma once
#include <vector>
#include "common/event/event.h"
#include "engine/gl/texture.h"
#include <glm/glm.hpp>

namespace Minecraft
{
	class BatchRenderer2D;

	class UIElement
	{
	public:
		virtual ~UIElement() { for (auto& el : m_Children) delete el; }

		virtual void SetColor(uint32_t color) { m_Color = color; }
		virtual void SetColor(const glm::vec4& color)
		{
			int r = (int)(color.x * 255.0f);
			int g = (int)(color.y * 255.0f);
			int b = (int)(color.z * 255.0f);
			int a = (int)(color.w * 255.0f);

			m_Color = a << 24 | b << 16 | g << 8 | r;
		}

		inline virtual const Rectangle GetBounds() { return m_Bounds; }
		inline virtual const uint32_t GetColor() const { return m_Color; }
		inline virtual const std::vector<glm::vec2>& GetUV() const { return m_UV; }

		virtual void OnMousePressed(Event& e) = 0;
		virtual void Submit(BatchRenderer2D* renderer) = 0;

	protected:
		UIElement(const Rectangle& bounds, const Ref<Texture>& texture, uint32_t color);
		UIElement() = delete;

		uint32_t m_Color;
		std::vector<glm::vec2> m_UV;
		Ref<Texture> m_Texture;
		Rectangle m_Bounds;

		bool m_Canceling = false;
		UIElement* m_Parent = nullptr;
		std::vector<UIElement*> m_Children;

		void SetUVDefaults()
		{
			m_UV.push_back(glm::vec2(0, 0));
			m_UV.push_back(glm::vec2(0, 1));
			m_UV.push_back(glm::vec2(1, 1));
			m_UV.push_back(glm::vec2(1, 0));
		}

	};
}

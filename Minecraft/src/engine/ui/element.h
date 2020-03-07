#pragma once
#include <vector>
#include "common/event/event.h"
#include "engine/gl/texture.h"
#include <glm/glm.hpp>

namespace Minecraft
{
	struct VertexData
	{
		glm::vec3 vertex;
		glm::vec2 uv;
		float tid;
		uint32_t color;
	};

	class UIElement
	{
	public:
		virtual ~UIElement() { for (auto& el : m_Children) delete el; }
		virtual void OnMousePressed(Event& e);

		void SetColor(uint32_t color) { m_Color = color; }
		void SetColor(const glm::vec4& color)
		{
			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;

			m_Color = a << 24 | b << 16 | g << 8 | r;
		}

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec2& GetSize() const { return m_Size; }
		inline const unsigned int GetColor() const { return m_Color; }
		inline const std::vector<glm::vec2>& GetUV() const { return m_UV; }

		inline const uint32_t GetTID() const { return m_Texture ? m_Texture->GetID() : 0; }

	protected:
		uint32_t m_Color;
		std::vector<glm::vec2> m_UV;
		Ref<Texture> m_Texture;

	protected:
		UIElement(const glm::vec3& pos);

		glm::vec3 m_Position;
		glm::vec2 m_Size;

		bool m_Canceling = false;
		UIElement* m_Parent = nullptr;
		std::vector<UIElement*> m_Children;

	private:
		void setUVDefaults()
		{
			m_UV.push_back(glm::vec2(0, 0));
			m_UV.push_back(glm::vec2(0, 1));
			m_UV.push_back(glm::vec2(1, 1));
			m_UV.push_back(glm::vec2(1, 0));
		}

	};
}
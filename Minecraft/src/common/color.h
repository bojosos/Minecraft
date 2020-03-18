#pragma once
#include <glm/glm.hpp>

namespace Minecraft
{
	class Color
	{
	public:
		Color(const glm::vec4& color);
		Color(const glm::vec3& color);
		Color(uint32_t color);

		inline glm::vec4 GetRGBA() const {
			uint8_t a = (m_Color & 0xff000000) >> 24;
			uint8_t r = (m_Color & 0x00ff0000) >> 16;
			uint8_t g = (m_Color & 0x0000ff00) >> 8;
			uint8_t b = (m_Color & 0x000000ff);

			return glm::vec4(r, g, b, a);
		}
		inline uint32_t GetColor() const { return m_Color; }

		operator uint32_t () const { return m_Color; }

	private:
		uint32_t m_Color;
	};
}
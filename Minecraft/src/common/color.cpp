#include "mcpch.h"
#include "color.h"

namespace Minecraft
{
	Color::Color(const glm::vec4& color)
	{
		int r = int(color.r * 255.0f);
		int g = int(color.g * 255.0f);
		int b = int(color.b * 255.0f);
		int a = int(color.a * 255.0f);

		m_Color = a << 24 | b << 16 | g << 8 | r;
	}

	Color::Color(const glm::vec3& color)
	{
		int r = int(color.r * 255.0f);
		int g = int(color.g * 255.0f);
		int b = int(color.b * 255.0f);
		int a = int(1.0f * 255.0f);

		m_Color = a << 24 | b << 16 | g << 8 | r;
	}

	Color::Color(uint32_t color) : m_Color(color)
	{

	}

}
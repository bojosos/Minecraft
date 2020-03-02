#pragma once
#include <vector>
#include "common/event/event.h"
#include <glm/glm.hpp>

namespace Minecraft
{
	class UIElement
	{
	public:
		virtual ~UIElement() { for (auto& el : m_Children) delete el; }
		virtual void OnMousePressed(Event& e) = 0;

	private:
		UIElement();
		glm::ivec2 m_Position;
		int32_t m_Width, m_Height;

		bool m_Canceling = false;
		UIElement* m_Parent = nullptr;
		std::vector<UIElement*> m_Children;

	};
}
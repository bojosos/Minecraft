#include "mcpch.h"
#include "uilayer.h"
#include "common/event/mouseevent.h"

namespace Minecraft
{
	UILayer::UILayer(const std::string& name) : Layer(name)
	{

	}

	void UILayer::OnAttach()
	{

	}

	void UILayer::OnDetach()
	{

	}

	void UILayer::OnEvent(Event& e)
	{
		//EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<MouseButtonPressedEvent>(MC_BIND_EVENT_FN(m_Root->OnMousePressed));
	}

	void UILayer::OnUpdate(Timestep time)
	{

	}
}
#pragma once

#include "common/timestep.h"
#include "common/event/event.h"
#include "common/common.h"

namespace Minecraft
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_Name; }
	private:
		std::string m_Name;
	};
}
#pragma once

#include "layer.h"

namespace Minecraft
{
	class TestLayer : public Layer
	{
	public:
		TestLayer(const std::string& name);
		virtual ~TestLayer() = default;
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& e) override;

	};
}
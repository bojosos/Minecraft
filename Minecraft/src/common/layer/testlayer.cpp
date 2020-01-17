#include "mcpch.h"
#include "engine/input/input.h"
#include "testlayer.h"

namespace Minecraft
{
	TestLayer::TestLayer(const std::string& name) : Layer(name) { }

	void TestLayer::OnAttach()
	{

	}

	void TestLayer::OnDetach()
	{

	}

	void TestLayer::OnEvent(Event& event)
	{

	}

	void TestLayer::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(KeyCode::Space))
		{
			MC_INFO("Space pressed, timestep is: {0}", ts.GetSeconds());
		}
	}
}
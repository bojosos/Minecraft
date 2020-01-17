#include <iostream>

#include "mcpch.h"
#include "common/layer/testlayer.h"
#include "engine.h"

// Not for here
#include <glad/glad.h>

class Test : public Minecraft::Application
{
public:
	Test()
	{
		PushLayer(new Minecraft::TestLayer("Test"));
	}

	void OnUpdate(Minecraft::Timestep ts)
	{
	}

	~Test()
	{

	}
};

int main(int argc, char** argv)
{
	Minecraft::Log::Init();

	auto app = new Test();
	app->Run();
	delete app;
}
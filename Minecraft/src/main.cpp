#include <iostream>

#include "mcpch.h"
#include "common/layer/testlayer.h"
#include "engine/application.h"

class Test : public Minecraft::Application
{
public:
	Test()
	{
		PushLayer(new Minecraft::TestLayer("Test"));
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
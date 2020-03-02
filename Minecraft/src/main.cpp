#include "mcpch.h"
#include "common/layer/testlayer.h"
#include "common/layer/uilayer.h"
#include "engine.h"

class Test : public Minecraft::Application
{
public:
	Test(int argc, char** argv)
	{
		PushLayer(new Minecraft::TestLayer("Test"));
		PushOverlay(new Minecraft::UILayer("UI"));
		Minecraft::CommandLineArgs::Create(argc, argv);
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

	auto app = new Test(argc, argv);
	app->Run();
	delete app;
}
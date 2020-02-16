#include "mcpch.h"
#include "testlayer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define SOL_ALL_SAFETIES_ON 1
#define SOL_PRINT_ERRORS 1
#include "engine/lua/sol.hpp"

namespace Minecraft
{
	std::vector<Block> TestLayer::s_Blocks = std::vector<Block>();

	void TestLayer::AddBlock(const std::string& shortname, const std::string& longname, bool solid, const sol::table& sides, bool transparent)
	{
		MC_ASSERT(sides.size() == 12, "Each block must have 12 sides!");
		MC_INFO("Adding Block: {0}", longname);
		s_Blocks.push_back(Block(shortname, longname, solid, sides, transparent));
	}

	void TestLayer::AddTexture(const std::string& filepath)
	{
		m_Textures.push_back(Texture::Create(filepath));
	}

	TestLayer::TestLayer(const std::string& name) : Layer(name)
	{

		sol::state lua;
		lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::io);
		lua.set_function("Block", &TestLayer::AddBlock, this);
		lua.set_function("Texture", &TestLayer::AddTexture, this);



		//lua.script("Block(\"air\", \"Air\", false, { 3, 0, 3, 0, 2, 0, 0, 0, 3, 0, 3, 0 }, true)");
		auto a = lua.script_file("lua/blocks.lua");

		//lua.set_function("test", Test);
		//lua.script("test(\"aaaa\", 5)");

		m_Camera = CreateRef<Camera>(glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f));
		m_Camera->Focus();

		m_VertexArray = VertexArray::Create();
		
		//s_Blocks.push_back(GrassBlock());
		m_World = CreateRef<World>(10, 10, 10);

		//BufferData();

		m_Shader = m_ShaderLibrary.Load("res/shaders/chunkshader.glsl");
		std::vector<std::string> locations = { "u_ViewMatrix", "u_ProjectionMatrix", "u_Transform" };
		m_Shader->RetrieveLocations(locations);
		//m_Texture = Texture::Create("res/textures/blocks.jpg");
		m_Frustum = CreateRef<ViewFrustum>();

		Renderer::Init();
	}

	void TestLayer::OnAttach()
	{
	}

	void TestLayer::OnDetach()
	{

	}

	void TestLayer::OnEvent(Event& event)
	{

	}

	void TestLayer::GetData(vertex* data , uint8_t x, uint8_t y, uint8_t z, uint32_t& i)
	{
		s_Blocks[0].GetBackVertexData(data, x, y, z, i);
		s_Blocks[0].GetFrontVertexData(data, x, y, z, i);
		s_Blocks[0].GetTopVertexData(data, x, y, z, i);
		s_Blocks[0].GetBottomVertexData(data, x, y, z, i);
		s_Blocks[0].GetLeftVertexData(data, x, y, z, i);
		s_Blocks[0].GetRightVertexData(data, x, y, z, i);
	}
	
	void TestLayer::OnUpdate(Timestep ts)
	{
		Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Renderer::Clear();

		m_Camera->Update();
		m_Frustum->Update(m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix());

		m_Shader->Bind();
		
		m_Shader->SetMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
		m_Shader->SetMat4("u_ProjectionMatrix", m_Camera->GetProjectionMatrix());
		
		m_Texture->Bind(0);
		m_World->Update(m_Shader, m_Frustum);
		once = false;
	}
}

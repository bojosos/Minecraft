#include "mcpch.h"
#include "testlayer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Minecraft
{
	std::vector<Block> TestLayer::s_Blocks = std::vector<Block>();

	TestLayer::TestLayer(const std::string& name) : Layer(name)
	{
		m_Camera = CreateRef<Camera>(glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f));
		m_Camera->Focus();

		m_VertexArray = VertexArray::Create();
		
		s_Blocks.push_back(GrassBlock());
		m_World = CreateRef<World>(10, 10, 10);

		//BufferData();

		m_Shader = m_ShaderLibrary.Load("res/shaders/chunkshader.glsl");
		std::vector<std::string> locations = { "u_ViewMatrix", "u_ProjectionMatrix", "u_Transform" };
		m_Shader->RetrieveLocations(locations);
		m_Texture = Texture::Create("res/textures/blocks.jpg");
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

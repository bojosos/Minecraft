#include "mcpch.h"
#include "testlayer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "game/blockloader.h"

namespace Minecraft
{

	TestLayer::TestLayer(const std::string& name) : Layer(name)
	{
		m_Camera = CreateRef<Camera>(glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f));
		m_Camera->Focus();

		m_VertexArray = VertexArray::Create();
		m_World = CreateRef<World>(10, 10, 10);
		m_Shader = m_ShaderLibrary.Load("res/shaders/chunkshader.glsl");
		
		std::vector<std::string> locations = { "u_ViewMatrix", "u_ProjectionMatrix", "u_Transform", "u_Textures" };
		m_Shader->RetrieveLocations(locations);

		BlockLoader::LoadDefaultBlocks("lua/blocks.lua", m_Shader);
		
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
	
	void TestLayer::OnUpdate(Timestep ts)
	{
		Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Renderer::Clear();

		m_Camera->Update();
		m_Frustum->Update(m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix());

		m_Shader->Bind();
		
		m_Shader->SetMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
		m_Shader->SetMat4("u_ProjectionMatrix", m_Camera->GetProjectionMatrix());

		m_World->Update(m_Shader, m_Frustum);
	}
}

#include "mcpch.h"
#include "testlayer.h"
#include "game/blockloader.h"
#include "engine/physics.h"
#include "common/scripting.h"
#include "engine/lua/luaapi.h"
#include "game/infolog.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Minecraft
{

	TestLayer::TestLayer(const std::string& name) : Layer(name)
	{
		InfoLog::Init();
		Random::Init();
		ScriptingEngine::Init();
		LuaApi::LuaDataApiInit();
		ScriptingEngine::ExecuteFile("lua/world/blocks.lua");

		m_Camera = CreateRef<Camera>(glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f));
		m_Camera->SetSpeed(0.08f);
		m_Camera->Focus();

		m_VertexArray = VertexArray::Create();
		m_World = CreateRef<World>();
		m_Shader = m_ShaderLibrary.Load("res/shaders/chunkshader.glsl");
		
		std::vector<std::string> locations = { "u_ViewMatrix", "u_ProjectionMatrix", "u_Transform", "u_Textures" };
		m_Shader->RetrieveLocations(locations);

		BlockLoader::InitTextures(m_Shader);
		//BlockLoader::LoadDefaultBlocks("lua/blocks.lua", m_Shader);
		
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
		//MC_INFO(ts);
		InfoLog::Update(ts);
		Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Renderer::Clear();

		m_Camera->Update();
		m_Frustum->Update(m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix());

		m_Shader->Bind();
		
		m_Shader->SetMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
		m_Shader->SetMat4("u_ProjectionMatrix", m_Camera->GetProjectionMatrix());

		if (Input::IsMouseButtonPressed(MouseCode::ButtonLeft))
		{
			Physics::Raycast(m_Camera->GetPosition(), m_Camera->GetForwardDirection(m_Camera->GetRotation()), 4, true, m_Camera);
		}

		if (Input::IsMouseButtonPressed(MouseCode::ButtonRight))
		{
			Physics::Raycast(m_Camera->GetPosition(), m_Camera->GetForwardDirection(m_Camera->GetRotation()), 4, false, m_Camera);
		}
		m_World->Update(m_Shader, m_Frustum);

	}

}

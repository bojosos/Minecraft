#include "mcpch.h"
#include "testlayer.h"
#include "game/blockloader.h"
#include "game/infolog.h"

#include "engine/lua/luaapi.h"
#include "engine/physics.h"
#include "engine/ui/font.h"
#include "engine/gl/renderer/renderer.h"

#include "common/scripting.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Minecraft
{

	TestLayer::TestLayer(const std::string& name) : Layer(name)
	{
		InfoLog::Init(1.0f);
		Random::Init();
		//ScriptingEngine::Init();
		//LuaApi::LuaDataApiInit();
		//ScriptingEngine::ExecuteFile("lua/world/blocks.lua");

		/*
		m_Camera = CreateRef<Camera>(glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f));
		m_Camera->SetSpeed(0.08f);
		m_Camera->Focus();
		*/
		m_VertexArray = VertexArray::Create();
		//m_World = CreateRef<World>();

		//m_Shader = m_ShaderLibrary.Load("res/shaders/chunkshader.glsl");
		m_Shader = m_ShaderLibrary.Load("res/shaders/uishader.glsl");
		
		std::vector<std::string> locations = { "u_ViewMatrix", "u_ProjectionMatrix", "u_ModelMatrix", "u_Textures" };
		m_Shader->RetrieveLocations(locations);

		BlockLoader::InitTextures(m_Shader);
	
		m_Frustum = CreateRef<ViewFrustum>();
		int vals[10] = { 0,1,2,3,4,5,6,7,8,9 };
		//m_Shader->SetIntV("u_Textures", 10, vals);

		FontManager::Add(CreateRef<Font>("arial", "res/fonts/roboto-thin.ttf", 64));
		Renderer::Init();
		
		m_Camera = CreateRef<Camera>(glm::ortho(-1000.0f, 1000.0f, -1000.0f, 1000.0f));
		m_Renderer = new BatchRenderer2D();
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
		InfoLog::Update(ts);
		
		Renderer::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Renderer::Clear();
		
		m_Renderer->begin();
		m_Shader->Bind();
		m_Shader->SetMat4("u_ViewMatrix", glm::mat4(1.0f));
		m_Shader->SetMat4("u_ModelMatrix", glm::mat4(1.0f));//m_Camera->GetViewMatrix());
		m_Shader->SetMat4("u_ProjectionMatrix", glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f));//m_Camera->GetProjectionMatrix());
		
		m_Renderer->drawString("test", glm::vec3(0.0f, 0.0f, 0.0f), FontManager::Get("arial"), 0xff000000);
		
		m_Renderer->end();
		m_Renderer->flush();
		//m_Camera->Update();
		//m_Frustum->Update(m_Camera->GetProjectionMatrix() * m_Camera->GetViewMatrix());

		//m_Shader->Bind();
		
		//m_Shader->SetMat4("u_ViewMatrix", m_Camera->GetViewMatrix());
		//m_Shader->SetMat4("u_ProjectionMatrix", m_Camera->GetProjectionMatrix());
		/*
		if (Input::IsMouseButtonPressed(MouseCode::ButtonLeft))
		{
			Physics::Raycast(m_Camera->GetPosition(), m_Camera->GetForwardDirection(m_Camera->GetRotation()), 4, true, m_Camera);
		}

		if (Input::IsMouseButtonPressed(MouseCode::ButtonRight))
		{
			Physics::Raycast(m_Camera->GetPosition(), m_Camera->GetForwardDirection(m_Camera->GetRotation()), 4, false, m_Camera);
		}
		m_World->Update(m_Shader, m_Frustum);*/

	}

}

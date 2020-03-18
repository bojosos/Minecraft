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
		InfoLog::Init();
		Random::Init();
		ScriptingEngine::Init();
		LuaApi::LuaDataApiInit();
#ifdef MC_WEB
		ScriptingEngine::ExecuteFile("Minecraft/lua/world/blocks.lua"); // fix these when building
#else
		ScriptingEngine::ExecuteFile("lua/world/blocks.lua");
#endif

		m_World = CreateRef<World>();

#ifdef MC_WEB
		m_Shader = m_ShaderLibrary.Load("shaders/chunkshader-web.glsl");
#else
		m_Shader = m_ShaderLibrary.Load("shaders/chunkshader.glsl");
#endif
		m_Shader->Bind();
		std::vector<std::string> locations = { "u_ViewMatrix", "u_ProjectionMatrix", "u_ChunkPosition", "u_Textures"};
		m_Shader->RetrieveLocations(locations);

		BlockLoader::InitTextures(m_Shader);

		Renderer::Init();
		m_Player = new Player({ 0.0f,0.0f,0.0f });
		m_World->AddPlayer(m_Player);
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

		m_Player->OnUpdate(ts);
		BlockLoader::BindTextures();
		m_Shader->Bind();
		
		m_Shader->SetMat4("u_ViewMatrix", m_Player->GetViewMatrix());
		m_Shader->SetMat4("u_ProjectionMatrix", m_Player->GetProjectionMatrix());
		
		if (Input::IsMouseButtonPressed(MouseCode::ButtonLeft))
		{
			Physics::Raycast(m_Player->GetPosition(), m_Player->GetForwardDirection(), PLAYER_REACH, true); // callback or smth
		}

		if (Input::IsMouseButtonPressed(MouseCode::ButtonRight))
		{
			Physics::Raycast(m_Player->GetPosition(), m_Player->GetForwardDirection(), PLAYER_REACH, false); // callback or smth
		}
		m_World->Update(m_Shader);

	}

}

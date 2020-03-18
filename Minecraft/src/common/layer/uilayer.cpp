#include "mcpch.h"
#include "uilayer.h"
#include <glm/gtc/matrix_transform.hpp>
#include "common/event/mouseevent.h"
#include "game/infolog.h"

namespace Minecraft
{
	UILayer::UILayer(const std::string& name) : Layer(name)
	{
#ifdef MC_WEB
		m_Shader = m_ShaderLibrary.Load("shaders/uishader-web.glsl");
#else
		m_Shader = m_ShaderLibrary.Load("shaders/uishader.glsl");
#endif
		m_Shader->Bind();
		m_Shader->RetrieveLocations({ "u_ModelMatrix", "u_ViewMatrix", "u_ProjectionMatrix", "u_Textures" });
		int vals[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		m_Shader->SetIntV("u_Textures", 10, vals);
		m_Renderer = new BatchRenderer2D();
		FontManager::Add(CreateRef<Font>("roboto", "fonts/roboto-thin.ttf", 32));
		m_Identity = glm::mat4(1.0f);
		m_Orthographic = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f);

		Label* fpsLabel = new Label("test", FontManager::Get("roboto", 32), Rectangle(10.0f, 10.0f));
		Label* test1 = new Label("test", FontManager::Get("default", 32), Rectangle(10.0f, 20.0f + fpsLabel->GetBounds().Height));
		Label* test2 = new Label("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSUVWXYZ", FontManager::Get("default", 32), Rectangle(10.0f, 30.0f + fpsLabel->GetBounds().Height + test1->GetBounds().Height));

		m_Labels.push_back(test1);
		m_Labels.push_back(test2);
		m_Labels.push_back(fpsLabel);
	}

	void UILayer::OnAttach()
	{

	}

	void UILayer::OnDetach()
	{

	}

	void UILayer::OnEvent(Event& e)
	{
		//EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<MouseButtonPressedEvent>(MC_BIND_EVENT_FN(m_Root->OnMousePressed));
	}

	void UILayer::OnUpdate(Timestep time)
	{
		m_Renderer->Begin();
		m_Shader->Bind();

		m_Shader->SetMat4("u_ModelMatrix", m_Identity);
		m_Shader->SetMat4("u_ViewMatrix", m_Identity);
		m_Shader->SetMat4("u_ProjectionMatrix", m_Orthographic);

		m_Labels.back()->SetText(std::to_string(InfoLog::GetFps()));

		for (Label* label : m_Labels)
		{
			label->Submit(m_Renderer);
		}

		m_Renderer->End();
		m_Renderer->Flush();
	}
}
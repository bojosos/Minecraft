#include "mcpch.h"
#include "application.h"

#include "common/log.h"
#include "common/common.h"
#include "common/timestep.h"
#include "engine/gl/renderer/renderer.h"
#include "engine/ui/font.h"

#ifdef MC_WEB
#include <emscripten/emscripten.h>
#endif

namespace Minecraft
{

	static void DispatchMain(void* fp)
	{
		std::function<void()>* func = (std::function<void()>*)fp;
		(*func)();
	}

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		MC_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create();

		Renderer::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

		m_Window->SetEventCallback(MC_BIND_EVENT_FN(Application::OnEvent));
		FontManager::Add(CreateRef<Font>("default", DEFAULT_FONT_PATH, 16));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(MC_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(MC_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			(*it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		//Application::Get().GetWindow().SetVSync(false);
#ifdef MC_WEB
		std::function<void()> loop = [&]() 
		{
#else
		while (m_Running)
		{
#endif
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(timestep);
			}

			m_Window->OnUpdate();
#ifdef MC_WEB
		};
		emscripten_set_main_loop_arg(DispatchMain, &loop, 0, 1);
#else
		}
#endif
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::SetViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}
}
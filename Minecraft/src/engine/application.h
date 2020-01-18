#pragma once

#include "common/common.h"
#include "common/event/applicationevent.h"
#include "common/layer/layerstack.h"
#include "engine/window/window.h"
#include <glm/glm.hpp>

namespace Minecraft
{
	class Application
	{
	public:
		Application();
		~Application();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		void Run();

		inline glm::vec2 GetWindowSize() { return { m_Window->GetWidth(), m_Window->GetHeight() }; }
		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }


	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};
}
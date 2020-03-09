#pragma once
#include "layer.h"
#include "engine/gl/renderer/batchrenderer2d.h"
#include "engine/gl/shader.h"
#include "engine/ui/ui.h"

namespace Minecraft
{
	class UILayer : public Layer
	{
	public:
		UILayer(const std::string& name);
		virtual ~UILayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event & e) override;

	private:
		std::vector<Label*> m_Labels;
		ShaderLibrary m_ShaderLibrary;
		glm::mat4 m_Orthographic;
		glm::mat4 m_Identity;
		Ref<Shader> m_Shader;
		Ref<UIElement> m_Root;
		BatchRenderer2D* m_Renderer;
	};
}
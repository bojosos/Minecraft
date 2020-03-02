#pragma once
#include "layer.h"
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
		Ref<UIElement> m_Root;

		/*
		ShaderLibrary m_ShaderLibrary;

		Ref<ViewFrustum> m_Frustum;
		Ref<World> m_World;
		Ref<Camera> m_Camera;
		Ref<Shader> m_Shader;
		Ref<VertexArray> m_VertexArray;
		Ref<VertexArray> m_SquareVA;
		std::vector<Ref<Texture>> m_Textures;*/
	};
}
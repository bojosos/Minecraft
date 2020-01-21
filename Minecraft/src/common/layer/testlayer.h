#pragma once

#include "engine.h"
#include "game/world.h"

namespace Minecraft
{
	class TestLayer : public Layer
	{
	public:
		TestLayer(const std::string& name);
		virtual ~TestLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnEvent(Event& e) override;
	private:
		ShaderLibrary m_ShaderLibrary;

		Ref<World> m_World;
		Ref<Camera> m_Camera;
		Ref<Shader> m_Shader;
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_FlatColorShader;
		Ref<VertexArray> m_SquareVA;
		Ref<Texture> m_Texture;
	};
}

#pragma once

#include "engine.h"

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
		Minecraft::ShaderLibrary m_ShaderLibrary;
		Minecraft::Ref<Minecraft::Shader> m_Shader;
		Minecraft::Ref<Minecraft::VertexArray> m_VertexArray;
		Minecraft::Ref<Minecraft::Shader> m_FlatColorShader;
		Minecraft::Ref<Minecraft::VertexArray> m_SquareVA;

		glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
	};
}
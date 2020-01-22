#pragma once

#include "engine.h"
#include "game/world.h"
#include "game/block.h"

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

		void BufferData();

		static void GetData(vertex* data, uint8_t x, uint8_t y, uint8_t z, uint32_t& i);

	private:
		static std::vector<Block> s_Blocks;

	private:
		ShaderLibrary m_ShaderLibrary;
		BufferLayout m_Layout;

		Ref<World> m_World;
		Ref<Camera> m_Camera;
		Ref<Shader> m_Shader;
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_FlatColorShader;
		Ref<VertexArray> m_SquareVA;
		Ref<Texture> m_Texture;
	};
}

#pragma once

#include "engine.h"
#include "game/world.h"
#include "game/block.h"
#include "game/player.h"

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

		Ref<ViewFrustum> m_Frustum;
		Ref<World> m_World;
		Player* m_Player;
		Ref<Shader> m_Shader;
	};
}

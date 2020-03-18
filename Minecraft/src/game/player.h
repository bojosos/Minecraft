#pragma once
#include <glm/glm.hpp>
#include "engine.h"

namespace Minecraft
{
	class Player
	{
	public:
		Player(const glm::vec3& position);

		void OnUpdate(Timestep ts);
		bool IsChunkVisible(const glm::vec3& chunkPosition);

		inline const glm::vec3& GetPosition() const { return m_Camera->GetPosition(); }
		inline const glm::vec3& GetRotation() const { return m_Camera->GetRotation(); }
		inline const glm::mat4& GetViewMatrix() const { return m_Camera->GetViewMatrix(); }
		inline const glm::mat4& GetProjectionMatrix() const { return m_Camera->GetProjectionMatrix(); }
		inline const glm::vec3& GetForwardDirection() const { return m_Camera->GetForwardDirection(); }

	private:
		float m_Health;
		float m_Saturation;
		Ref<Camera> m_Camera;

	};
}

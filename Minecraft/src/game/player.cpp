#include "mcpch.h"
#include "player.h"

namespace Minecraft
{
	Player::Player(const glm::vec3& position)
	{
		m_Camera = CreateRef<Camera>(glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f));
		m_Camera->SetPosition(position);
		m_Camera->SetSpeed(0.08f);
		m_Camera->Focus();
		m_Health = m_Saturation = 0;
	}

	bool Player::IsChunkVisible(const glm::vec3& chunkPosition)
	{
		return m_Camera->GetFrustum()->ChunkIsInFrustum(chunkPosition);
	}

	void Player::OnUpdate(Timestep ts)
	{
		m_Camera->Update(ts);
		//float x = m_Camera->GetPosition.x;
	}
}
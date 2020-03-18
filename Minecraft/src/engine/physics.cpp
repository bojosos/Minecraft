#include "mcpch.h"
#include "physics.h"
#include "common/math.h"
#include "game/world.h"

namespace Minecraft
{
	void Physics::Raycast(const glm::vec3& location, const glm::vec3& dir, float length, bool button)
	{
		glm::vec3 direction = glm::normalize(dir);

		float x = floor(location.x);
		float y = floor(location.y);
		float z = floor(location.z);

		float dx = direction.x;
		float dy = direction.y;
		float dz = direction.z;

		float stepX = Math::Signum(dx);
		float stepY = Math::Signum(dy);
		float stepZ = Math::Signum(dz);

		float tMaxX = Math::Intbound(location.x, dx);
		float tMaxY = Math::Intbound(location.y, dy);
		float tMaxZ = Math::Intbound(location.z, dz);

		float tDeltaX = stepX / dx;
		float tDeltaY = stepY / dy;
		float tDeltaZ = stepZ / dz;

		length /= sqrt(dx * dx + dy * dy + dz * dz);

		glm::vec3 face(0.0f);
		MC_ASSERT(dx != 0.0f || dy != 0.0f || dz != 0.0f, "Raycast has no direction!");

		while ((stepX > 0.0f ? x < 160.0f : x >= 0.0f) && (stepY > 0.0f ? y < 160.0f : y >= 0.0f) && (stepZ > 0.0f ? z < 160.0f : z >= 0.0f)) {
			
			if (!(x < 0.0f || y < 0.0f || z < 0.0f || x >= 160.0f || y >= 160.0f || z >= 160.0f))
				if (World::GetOverworld().GetBlock((int)x, (int)y, (int)z).IsSolid())
				{
					if (button) {
						MC_INFO("Breaking {0} at {1}, {2}, {3}", x, y, z, World::GetOverworld().GetBlock((int)x, (int)y, (int)z).m_Longname);
						World::GetOverworld().SetBlock((int)x, (int)y, (int)z, 0);
						break;
					}
					else
					{
						MC_INFO("Placing over {0} at {1}, {2}, {3}", x, y, z, World::GetOverworld().GetBlock((int)x, (int)y, (int)z).m_Longname);
						World::GetOverworld().SetBlock((int)x, (int)y + 1, (int)z, 2);
					}

					World::GetOverworld().DrawOutline((int)x, (int)y, (int)z, face);
					break;
				}

			if (tMaxX < tMaxY)
			{
				if (tMaxX < tMaxZ)
				{
					if (tMaxX > length) break;
					x += stepX;
					tMaxX += tDeltaX;

					face.x = -stepX;
					face.y = 0;
					face.z = 0;
				}
				else
				{
					if (tMaxZ > length) break;
					x += stepZ;
					tMaxZ += tDeltaZ;

					face.x = 0;
					face.y = 0;
					face.z = -stepZ;;
				}
			}
			else
			{
				if (tMaxY < tMaxZ)
				{
					if (tMaxY > length) break;
					y += stepY;
					tMaxY += tDeltaY;

					face.x = 0;
					face.y = -stepY;
					face.z = 0;
				}
				else
				{
					if (tMaxZ > length) break;
					z += stepZ;
					tMaxZ += tDeltaZ;

					face.x = 0;
					face.y = 0;
					face.z = -stepZ;
				}
			}
		}
	}
}
#include "mcpch.h"
#include "physics.h"
#include "common/math.h"
#include "game/world.h"
#include <glad/glad.h>

namespace Minecraft
{
	void Physics::Raycast(const glm::vec3& location, const glm::vec3& direction, uint32_t length, bool button, const Ref<Camera>& cam)
	{
		int x = floor(location.x);
		int y = floor(location.y);
		int z = floor(location.z);

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

		glm::vec3 face(0.0f);
		MC_ASSERT(dx != 0 || dy != 0 || dz != 0, "Raycast has no direction!");

		while ((stepX > 0 ? x < 160 : x >= 0) && (stepY > 0 ? y < 160 : y >= 0) && (stepZ > 0 ? z < 160 : z >= 0)) {
			
			if (!(x < 0 || y < 0 || z < 0 || x >= 160 || y >= 160 || z >= 160))
				//if (callback(x, y, z, blocks[x * wy * wz + y * wz + z], face)
				//	)
				if (World::GetOverworld().GetBlock(x, y, z).IsSolid()) 
				{
					if (button) {
						MC_INFO("Breaking {0} at {1}, {2}, {3}", x, y, z, World::GetOverworld().GetBlock(x, y, z).m_Longname);
						World::GetOverworld().SetBlock(x, y, z, 0);
						break;
					}
					else
					{
						MC_INFO("Placing over {0} at {1}, {2}, {3}", x, y, z, World::GetOverworld().GetBlock(x, y, z).m_Longname);
						World::GetOverworld().SetBlock(x, y + 1, z, 2);
					}
					//World::GetOverworld().DrawOutline((int)face.x, (int)face.y, (int)face.z, cam);
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
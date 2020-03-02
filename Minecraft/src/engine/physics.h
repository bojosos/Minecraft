#pragma once

#include "common/common.h"
#include "engine/camera.h"
#include <glm/glm.hpp>

namespace Minecraft
{

	class Physics
	{
	public:
		static void Raycast(const glm::vec3& location, const glm::vec3& direction, uint32_t length, bool button, const Ref<Camera>& cam);
	private:

	};
	
}
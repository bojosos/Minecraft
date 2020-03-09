#pragma once

#include "element.h"
#include "engine/gl/texture.h"
#include <glm/glm.hpp>

namespace Minecraft
{
	class Panel : public UIElement
	{
	public:
		Panel(const glm::vec3& position);
		Panel(const glm::vec3& position, const Ref<Texture>& texture);

		virtual void Submit(BatchRenderer2D* renderer) override;
	};
}
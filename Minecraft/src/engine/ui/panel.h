#pragma once

#include "element.h"
#include "engine/gl/texture.h"
#include <glm/glm.hpp>

namespace Minecraft
{
	class Panel : public UIElement
	{
	public:
		Panel(const Rectangle& bounds);
		Panel(const Rectangle& bounds, const Ref<Texture>& texture);

		virtual void Submit(BatchRenderer2D* renderer) override;
	};
}
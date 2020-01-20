#pragma once

#include "common/common.h"
#include "engine/gl/vao.h"

namespace Minecraft
{
	class Mesh
	{
	public:
		Mesh(const Ref<VertexArray>& vao);
		~Mesh();

		static Ref<Mesh> Create(const Ref<VertexArray>& vao);

	private:
		Ref<VertexArray> m_VertexArray;
	};
}
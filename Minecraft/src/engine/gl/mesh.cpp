#include "mcpch.h"
#include "mesh.h"

namespace Minecraft
{
	Mesh::Mesh(const Ref<VertexArray>& vao) : m_VertexArray(vao)
	{

	}

	Mesh::~Mesh()
	{

	}

	Ref<Mesh> Mesh::Create(const Ref<VertexArray>& vao)
	{
		return CreateRef<Mesh>(vao);
	}
}
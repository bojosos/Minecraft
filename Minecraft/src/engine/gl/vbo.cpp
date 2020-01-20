#include "mcpch.h"
#include "vbo.h"

#include <glad/glad.h>

namespace Minecraft
{
	Ref<VertexBuffer> VertexBuffer::Create(float* verts, uint32_t size)
	{
		return CreateRef<VertexBuffer>(verts, size);
	}

	Ref<VertexBuffer> VertexBuffer::Create(byte4* verts, uint32_t size) 
	{
		return CreateRef<VertexBuffer>(verts, size);
	}

	VertexBuffer::VertexBuffer(float* verts, uint32_t size) : m_Count(size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
	}

	VertexBuffer::VertexBuffer(byte4* verts, uint32_t size) : m_Count(size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

#include "mcpch.h"
#include "vbo.h"

#include <glad/glad.h>

namespace Minecraft
{
	Ref<VertexBuffer> VertexBuffer::Create(float* verts, uint32_t size)
	{
		return CreateRef<VertexBuffer>(verts, size);
	}

	Ref<VertexBuffer> VertexBuffer::Create(vertex* verts, uint32_t size) 
	{
		return CreateRef<VertexBuffer>(verts, size);
	}

	VertexBuffer::VertexBuffer(float* verts, uint32_t size) : m_Count(size)
	{
		glCreateBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
	}

	void VertexBuffer::SetData(vertex* verts, uint32_t size)
	{
		//glBufferSubData(GL_ARRAY_BUFFER, 0, size, verts);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glUnmapNamedBuffer(m_RendererID);
		glNamedBufferData(m_RendererID, size, verts, GL_STATIC_DRAW);
	}

	VertexBuffer::VertexBuffer(vertex* verts, uint32_t size) : m_Count(size)
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

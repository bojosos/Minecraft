#include "mcpch.h"
#include "vbo.h"

#ifdef MC_WEB
#include <GLES3/gl32.h>
#else
#include <glad/glad.h>
#endif

namespace Minecraft
{
	Ref<VertexBuffer> VertexBuffer::Create(float* verts, uint32_t size)
	{
		return CreateRef<VertexBuffer>(verts, size);
	}

	Ref<VertexBuffer> VertexBuffer::Create(Vertex* verts, uint32_t size) 
	{
		return CreateRef<VertexBuffer>(verts, size);
	}

	Ref<VertexBuffer> VertexBuffer::CreateDynamic(void* data, uint32_t size)
	{
		return CreateRef<VertexBuffer>(data, size, true);
	}

	VertexBuffer::VertexBuffer(float* verts, uint32_t size) : m_Count(size)
	{
#ifdef MC_WEB
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
#else
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, verts, GL_STATIC_DRAW);
#endif
	}

	void VertexBuffer::SetData(Vertex* verts, uint32_t size)
	{		
#ifdef MC_WEB
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
#else
		glNamedBufferData(m_RendererID, size, verts, GL_STATIC_DRAW);
#endif
	}

	VertexBuffer::VertexBuffer(Vertex* verts, uint32_t size) : m_Count(size)
	{
#ifdef MC_WEB
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW);
#else
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, verts, GL_STATIC_DRAW);
#endif
	}

	VertexBuffer::VertexBuffer(void* data, uint32_t size, bool dynamic) : m_Count(size)
	{
#ifdef MC_WEB
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
#else
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
#endif	
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

	void* VertexBuffer::MapBuffer(uint32_t target, uint32_t type)
	{
#ifndef MC_WEB
		return glMapBuffer(target, type);
#endif
	}

	void VertexBuffer::Unmap()
	{
#ifndef MC_WEB
		glUnmapBuffer(GL_ARRAY_BUFFER);
#endif
	}
}

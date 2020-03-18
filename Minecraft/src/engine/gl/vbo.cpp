#include "mcpch.h"
#include "vbo.h"

#ifdef MC_WEB
#include <GLES3/gl32.h>
#else
#include <glad/glad.h>
#endif

namespace Minecraft
{

	static uint32_t BufferUsageToOpenGLBufferUsage(BufferUsage usage)
	{
		switch (usage)
		{
		case(BufferUsage::STATIC_DRAW): return GL_STATIC_DRAW;
		case(BufferUsage::DYNAMIC_DRAW): return GL_DYNAMIC_DRAW;
		}
		MC_ASSERT(false, "Drawing mode not support");
		return GL_NONE;
	}
	
	Ref<VertexBuffer> VertexBuffer::Create(const void* data, uint32_t size, BufferUsage usage)
	{
		return CreateRef<VertexBuffer>(data, size, usage);
	}

	VertexBuffer::VertexBuffer(const void* data, uint32_t size, BufferUsage usage) : m_Size(size), m_Usage(usage)
	{
#ifdef MC_WEB
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, data, BufferUsageToOpenGLBufferUsage(m_Usage));
#else
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, data, BufferUsageToOpenGLBufferUsage(m_Usage));
#endif	
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void VertexBuffer::SetData(const void* verts, uint32_t size)
	{
#ifdef MC_WEB
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, verts, BufferUsageToOpenGLBufferUsage(m_Usage));
#else
		glNamedBufferData(m_RendererID, size, verts, BufferUsageToOpenGLBufferUsage(m_Usage));
#endif
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void* VertexBuffer::GetPointer(uint32_t size)
	{
		Bind();
#ifndef MC_WEB
		return glMapBufferRange(GL_ARRAY_BUFFER, 0, size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);                                                                            
#else
		return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
#endif
	}

	void VertexBuffer::FreePointer()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
}

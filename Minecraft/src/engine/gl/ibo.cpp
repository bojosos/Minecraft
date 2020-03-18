#include "mcpch.h"
#include "ibo.h"

#ifdef MC_WEB
#include <GLES3/gl32.h>
#else
#include <glad/glad.h>
#endif

namespace Minecraft
{
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		return CreateRef<IndexBuffer>(indices, size);
	}

	IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
	{
#ifdef MC_WEB
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
#else
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
#endif
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

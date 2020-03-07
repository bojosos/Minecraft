#pragma once

#include <glad/glad.h>
#include "buffer.h"
#include "common/types.h"

namespace Minecraft
{
	class VertexBuffer
	{
	public:
		VertexBuffer(float* verts, uint32_t size);
		VertexBuffer(vertex* verts, uint32_t size);
		VertexBuffer(void* data, uint32_t size, bool dynamic = false);

		~VertexBuffer();

		void Bind();
		void Unbind();
		void* MapBuffer(GLenum target, GLenum type);
		void Unmap();

		const BufferLayout& GetLayout() const { return m_Layout; };
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
		void SetData(vertex* verts, uint32_t size);

		inline int GetCount() { return m_Count; }

		static Ref<VertexBuffer> Create(float* verts, uint32_t size);
		static Ref<VertexBuffer> Create(vertex* verts, uint32_t size);
		static Ref<VertexBuffer> CreateDynamic(void* verts, uint32_t size);
	private:
		uint32_t m_RendererID, m_Count;
		BufferLayout m_Layout;
	private:
	};
}
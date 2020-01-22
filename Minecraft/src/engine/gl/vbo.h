#pragma once

#include "buffer.h"

namespace Minecraft
{
	class VertexBuffer
	{
	public:
		VertexBuffer(float* verts, uint32_t size);
		VertexBuffer(vertex* verts, uint32_t size);

		~VertexBuffer();

		void Bind();
		void Unbind();

		const BufferLayout& GetLayout() const { return m_Layout; };
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

		static Ref<VertexBuffer> Create(float* verts, uint32_t size);
		static Ref<VertexBuffer> Create(vertex* verts, uint32_t size);
	private:
		uint32_t m_RendererID, m_Count;
		BufferLayout m_Layout;
	private:
	};
}
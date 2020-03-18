#pragma once

#include "buffer.h"
#include "common/types.h"

namespace Minecraft
{
	enum class BufferUsage
	{
		STATIC_DRAW,
		DYNAMIC_DRAW
	};

	class VertexBuffer
	{
	public:
		VertexBuffer(const void* data, uint32_t size, BufferUsage usage);
		~VertexBuffer();

		void Bind();
		void Unbind();

		const BufferLayout& GetLayout() const { return m_Layout; };
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
		void SetData(const void* verts, uint32_t size);

		void* GetPointer(uint32_t size);
		void FreePointer();

		static Ref<VertexBuffer> Create(const void* verts, uint32_t size, BufferUsage usage = BufferUsage::DYNAMIC_DRAW);
	private:
		BufferUsage m_Usage;
		uint32_t m_RendererID, m_Size;
		BufferLayout m_Layout;
	};
}
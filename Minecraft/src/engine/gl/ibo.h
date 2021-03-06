#pragma once

#include "common/common.h"

namespace Minecraft
{
	class IndexBuffer
	{
	public:
		IndexBuffer(uint32_t* indices, uint32_t size);
		~IndexBuffer();

		void Bind();
		void Unbind();

		uint32_t GetCount() { return m_Count; }

		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t size);
	private:
		IndexBuffer() = delete;
		uint32_t m_RendererID, m_Count;

	};
}

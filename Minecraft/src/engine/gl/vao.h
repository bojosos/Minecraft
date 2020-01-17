#pragma once

#include "vbo.h"
#include "ibo.h"

namespace Minecraft
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void Bind() const;
		void Unbind() const;
		
		void AddVertexBuffer(const Ref<VertexBuffer>& vbo);
		void SetIndexBuffer(const Ref<IndexBuffer>& ibo);
		inline const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; };
		inline const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };

		static Ref<VertexArray> Create();
	private:
		uint32_t m_RendererID, m_VertexBufferIndex=0;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}
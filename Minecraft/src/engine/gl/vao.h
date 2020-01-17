#pragma once

#include "vbo.h"
#include "ibo.h"

namespace Minecraft
{
	class VertexArray
	{
	public:
		~VertexArray();
		void Bind();
		void Unbind();
		
		void AddVertexBuffer(const Ref<VertexBuffer>& vbo);
		void SetIndexBuffer(const Ref< IndexBuffer>& ibo);
		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const;
		const Ref<IndexBuffer>& GetIndexBuffer() const;

		static Ref<VertexArray> Create();
	private:
		VertexArray();
	};
}
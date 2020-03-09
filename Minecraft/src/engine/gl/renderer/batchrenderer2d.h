#pragma once

#include <cstddef>

#include "engine/ui/ui.h"
#include "engine/gl/ibo.h"

namespace Minecraft
{

	class BatchRenderer2D
	{
	private:
		//TODO: Use my buffers, textures

		GLuint m_VAO;
		GLuint m_VBO;
		IndexBuffer* m_IBO;
		GLsizei m_IndexCount = 0;
		VertexData* m_Buffer;

		std::vector<GLuint> m_TextureSlots;
	public:
		BatchRenderer2D();
		~BatchRenderer2D();
		void Clear();
		void SetClearColor(const glm::vec4& color);
		void Begin();
		void Submit(const UIElement* renderable);
		void DrawString(const std::string& text, const glm::vec3& position, const Ref<Font>& font, uint32_t color);
		void End();
		void Flush();
	private:
		void Init();
	};
}
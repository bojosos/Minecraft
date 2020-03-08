#pragma once

#include <cstddef>

#include "engine/ui/ui.h"
#include "engine/gl/ibo.h"

namespace Minecraft
{

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX		1
#define SHADER_TID_INDEX	2
#define SHADER_COLOR_INDEX	3

	class BatchRenderer2D
	{
	private:
		GLuint m_VAO;
		GLuint m_VBO;
		IndexBuffer* m_IBO;
		GLsizei m_IndexCount = 0;
		VertexData* m_Buffer;

		std::vector<GLuint> m_TextureSlots;
	public:
		BatchRenderer2D();
		~BatchRenderer2D();
		void begin();
		void submit(const UIElement* renderable);
		void drawString(const std::string& text, const glm::vec3& position, const Ref<Font>& font, unsigned int color);
		void end();
		void flush();
	private:
		void init();
	};
}
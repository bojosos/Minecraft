#pragma once

#include "engine/ui/ui.h"
#include "engine/gl/vao.h"

#ifdef MC_WEB
#include <glfw/glfw3.h>
#else
#include <glad/glad.h>
#endif

namespace Minecraft
{
	struct VertexData
	{
		glm::vec3 vertex;
		glm::vec2 uv;
		float tid;
		uint32_t color;
	};

	class BatchRenderer2D
	{
	private:
		Ref<VertexArray> m_Vao;
		Ref<VertexBuffer> m_Vbo;
		Ref<IndexBuffer> m_Ibo;
		GLsizei m_IndexCount = 0;
		VertexData* m_Buffer;

		std::vector<Ref<Texture>> m_TextureSlots;
#ifdef MC_DEBUG
#endif
	public:
		BatchRenderer2D();
		~BatchRenderer2D();
		void Clear();
		void SetClearColor(const glm::vec4& color);
		void Begin();

		float FindTexture(const Ref<Texture>& texture);
		
		void FillRect(const Rectangle& bounds, uint32_t color);
		void FillRect(const Rectangle& bounds, const Ref<Texture>& texture, uint32_t color);

		void DrawString(const std::string& text, float x, float y, const Ref<Font>& font, uint32_t color);
		void End();
		void Flush();
	private:
		void Init();
	};
}
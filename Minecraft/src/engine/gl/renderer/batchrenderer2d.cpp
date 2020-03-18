#include "mcpch.h"
#include "batchrenderer2d.h"

namespace Minecraft
{
	BatchRenderer2D::BatchRenderer2D()
	{
		Init();
	}

	BatchRenderer2D::~BatchRenderer2D()
	{
		glDeleteBuffers(1, &m_VBO);
	}

	void BatchRenderer2D::Init()
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			indices[i] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		m_IBO = IndexBuffer::Create(indices, RENDERER_INDICES_SIZE);

		glBindVertexArray(0);
	}

	void BatchRenderer2D::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void BatchRenderer2D::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void BatchRenderer2D::Begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
#ifdef MC_WEB
		m_Buffer = (VertexData*)glMapBufferRange(GL_ARRAY_BUFFER, 0, RENDERER_MAX_SPRITES * 4, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
#else
		m_Buffer = (VertexData*)glMapBufferRange(GL_ARRAY_BUFFER, 0, RENDERER_MAX_SPRITES * 4, GL_MAP_WRITE_BIT);
#endif
	}

	float BatchRenderer2D::FindTexture(const Ref<Texture>& texture)
	{
		float ts = 0.0f;
		bool found = false;
		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i] == texture)
			{
				ts = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (m_TextureSlots.size() >= 32)
			{
				End();
				Flush();
				Begin();
			}
			m_TextureSlots.push_back(texture);
			ts = (float)(m_TextureSlots.size());
		}
		return ts;
	}

	void BatchRenderer2D::FillRect(const Rectangle& bounds, uint32_t color)
	{
		float ts = 0;

		m_Buffer->vertex = glm::vec3(bounds.X, bounds.Y, 1.0f);
		m_Buffer->uv = glm::vec2(0.0f, 0.0f);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(bounds.X, bounds.Y + bounds.Height, 1.0f);
		m_Buffer->uv = glm::vec2(0.0f, 1.0f);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(bounds.X + bounds.Width, bounds.Y + bounds.Height, 1.0f);
		m_Buffer->uv = glm::vec2(1.0f, 1.0f);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(bounds.X + bounds.Width, bounds.Y, 1.0f);
		m_Buffer->uv = glm::vec2(1.0f, 0.0f);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void BatchRenderer2D::FillRect(const Rectangle& bounds, const Ref<Texture>& texture, const uint32_t color)
	{
		float ts = FindTexture(texture);

		m_Buffer->vertex = glm::vec3(bounds.X, bounds.Y, 1.0f);
		m_Buffer->uv = glm::vec2(0.0f, 0.0f);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(bounds.X, bounds.Y + bounds.Height, 1.0f);
		m_Buffer->uv = glm::vec2(0.0f, 1.0f);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(bounds.X + bounds.Width, bounds.Y + bounds.Height, 1.0f);
		m_Buffer->uv = glm::vec2(1.0f, 1.0f);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(bounds.X + bounds.Width, bounds.Y, 1.0f);
		m_Buffer->uv = glm::vec2(1.0f, 0.0f);
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void BatchRenderer2D::DrawString(const std::string& text, float x, float y, const Ref<Font>& font, uint32_t color)
	{
		float ts = FindTexture(font->GetTexture());

		texture_font_t* ftFont = font->GetFTGLFont();

		for (uint32_t i = 0; i < text.length(); i++)
		{
			char c = text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(ftFont, &c);
		
			if (glyph)
			{

				if (i > 0)
				{
					float kerning = texture_glyph_get_kerning(glyph, &text[i - 1]);
					x += kerning;
				}

				float x0 = x + glyph->offset_x;
				float y0 = y + glyph->offset_y;
				float x1 = x0 + glyph->width;
				float y1 = y0 - glyph->height;

				float u0 = glyph->s0;
				float v0 = glyph->t0;
				float u1 = glyph->s1;
				float v1 = glyph->t1;

				m_Buffer->vertex = glm::vec3(x0, y0, 0);
				m_Buffer->uv = glm::vec2(u0, v0);
				m_Buffer->tid = ts;
				m_Buffer->color = color;
				m_Buffer++;

				m_Buffer->vertex = glm::vec3(x0, y1, 0);
				m_Buffer->uv = glm::vec2(u0, v1);
				m_Buffer->tid = ts;
				m_Buffer->color = color;
				m_Buffer++;

				m_Buffer->vertex = glm::vec3(x1, y1, 0);
				m_Buffer->uv = glm::vec2(u1, v1);
				m_Buffer->tid = ts;
				m_Buffer->color = color;
				m_Buffer++;

				m_Buffer->vertex = glm::vec3(x1, y0, 0);
				m_Buffer->uv = glm::vec2(u1, v0);
				m_Buffer->tid = ts;
				m_Buffer->color = color;
				m_Buffer++;

				m_IndexCount += 6;

				x += glyph->advance_x;
			}

		}
	}

	void BatchRenderer2D::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	void BatchRenderer2D::Flush()
	{
		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			m_TextureSlots[i]->Bind(i);
		}
		m_TextureSlots.clear();

		glBindVertexArray(m_VAO);
		m_IBO->Bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);

		m_IBO->Unbind();
		glBindVertexArray(0);

		m_IndexCount = 0;
	}
}
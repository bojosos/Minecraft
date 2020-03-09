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
		delete m_IBO;
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
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::uv)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::tid)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));

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

		m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

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
		m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void BatchRenderer2D::Submit(const UIElement* renderable)
	{
		const glm::vec3& position = renderable->GetPosition();
		const glm::vec2& size = renderable->GetSize();
		const unsigned int color = renderable->GetColor();
		const std::vector<glm::vec2>& uv = renderable->GetUV();
		const GLuint tid = renderable->GetTID();

		float ts = 0.0f;
		if (tid > 0)
		{
			bool found = false;
			for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == tid)
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
				m_TextureSlots.push_back(tid);
				ts = (float)(m_TextureSlots.size());
			}
		}

		m_Buffer->vertex = position;
		m_Buffer->uv = uv[0];
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x, position.y + size.y, position.z);
		m_Buffer->uv = uv[1];
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y + size.y, position.z);
		m_Buffer->uv = uv[2];
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_Buffer->vertex = glm::vec3(position.x + size.x, position.y, position.z);
		m_Buffer->uv = uv[3];
		m_Buffer->tid = ts;
		m_Buffer->color = color;
		m_Buffer++;

		m_IndexCount += 6;
	}

	void BatchRenderer2D::DrawString(const std::string& text, const glm::vec3& position, const Ref<Font>& font, uint32_t color)
	{
		float ts = 0.0f;
		bool found = false;
		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i] == font->GetTexture()->GetID())
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
			m_TextureSlots.push_back(font->GetTexture()->GetID());
			ts = (float)(m_TextureSlots.size());
		}

		float scaleX = 1; // 1280.0f / 32.0f;
		float scaleY = 1; // 720.0f / 18.0f;

		float x = position.x;

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
					x += kerning / scaleX;
				}

				float x0 = x + glyph->offset_x / scaleX;
				float y0 = position.y + glyph->offset_y / scaleY;
				float x1 = x0 + glyph->width / scaleX;
				float y1 = y0 - glyph->height / scaleY;

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

				x += glyph->advance_x / scaleX;
			}

		}
	}

	void BatchRenderer2D::End()
	{
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer2D::Flush()
	{
		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
		}

		glBindVertexArray(m_VAO);
		m_IBO->Bind();

		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

		m_IBO->Unbind();
		glBindVertexArray(0);

		m_IndexCount = 0;
	}
}
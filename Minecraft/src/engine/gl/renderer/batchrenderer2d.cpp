#include "mcpch.h"
#include "batchrenderer2d.h"
#include "engine/gl/texture.h"
#include "engine/gl/shader.h"
#include "engine/gl/vao.h"
#include <glm/gtc/matrix_transform.hpp>

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

	struct Renderer2DStorage
	{
		std::vector<glm::mat4> TransformationStack;
		const glm::mat4* TransformationBack;

		Ref<VertexArray> Vao;
		Ref<VertexBuffer> Vbo;

		std::vector<uint32_t> TextureSlots;
		VertexData* Buffer;
		uint32_t IndexCount;
	};

	static Scope<Renderer2DStorage> s_Data;

	void BatchRenderer2D::Init()
	{
		s_Data = CreateScope<Renderer2DStorage>();

		s_Data->TransformationStack.push_back(glm::mat4(1.0f));
		s_Data->TransformationBack = &(s_Data->TransformationStack.back());

		s_Data->Vao = VertexArray::Create();
		s_Data->Vbo = VertexBuffer::CreateDynamic(NULL, RENDERER_BUFFER_SIZE);

		s_Data->Vbo->SetLayout({
			{ ShaderDataType::Float3, "a_Coords" },
			{ ShaderDataType::Float2, "a_Uv" },
			{ ShaderDataType::Float, "a_Tid"},
			{ ShaderDataType::UByte4, "a_Color", true}
		});
		s_Data->Vbo->Unbind();

		GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

		int offset = 0;
		for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		Ref<IndexBuffer> ibo = IndexBuffer::Create(indices, RENDERER_INDICES_SIZE);

		s_Data->Vao->SetIndexBuffer(ibo);
		s_Data->Vao->Unbind();
	}

	void BatchRenderer2D::Begin()
	{
		s_Data->Vbo->Bind();
		s_Data->Buffer = (VertexData*)(s_Data->Vbo->MapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	}

	void BatchRenderer2D::Submit(const Ref<UIElement>& element)
	{
		const glm::vec3& pos = element->GetPosition();
		const glm::vec2& size = element->GetSize();
		const uint32_t color = element->GetColor();
		const std::vector<glm::vec2>& uv = element->GetUV();
		const GLuint tid = element->GetTID();

		float ts = 0.0f;
		if (tid > 0)
		{
			bool found = false;
			for (int i = 0; i < s_Data->TextureSlots.size(); i++)
			{
				if (s_Data->TextureSlots[i] == tid)
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (s_Data->TextureSlots.size() >= 32)
				{
					End();
					Flush();
					Begin();
				}
				s_Data->TextureSlots.push_back(tid);
				ts = (float)(s_Data->TextureSlots.size());
			}
		}

		s_Data->Buffer->vertex = *(s_Data->TransformationBack) * glm::vec4(pos, 1.0f);
		s_Data->Buffer->uv = uv[0];
		s_Data->Buffer->tid = ts;
		s_Data->Buffer->color = color;
		s_Data->Buffer++;

		s_Data->Buffer->vertex = *(s_Data->TransformationBack) * glm::vec4(pos.x, pos.y + size.y, pos.z, 1.0f);
		s_Data->Buffer->uv = uv[1];
		s_Data->Buffer->tid = ts;
		s_Data->Buffer->color = color;
		s_Data->Buffer++;

		s_Data->Buffer->vertex = *(s_Data->TransformationBack) * glm::vec4(pos.x + size.x, pos.y + size.y, pos.z, 1.0f);
		s_Data->Buffer->uv = uv[2];
		s_Data->Buffer->tid = ts;
		s_Data->Buffer->color = color;
		s_Data->Buffer++;

		s_Data->Buffer->vertex = *(s_Data->TransformationBack) * glm::vec4(pos.x + size.x, pos.y, pos.z, 1.0f);
		s_Data->Buffer->uv = uv[3];
		s_Data->Buffer->tid = ts;
		s_Data->Buffer->color = color;
		s_Data->Buffer++;

		s_Data->IndexCount += 6;
	}

	void BatchRenderer2D::Push(const glm::mat4& matrix, bool override = false)
	{
		if (override)
			s_Data->TransformationStack.push_back(matrix);
		else
			s_Data->TransformationStack.push_back(s_Data->TransformationStack.back() * matrix);

		s_Data->TransformationBack = &(s_Data->TransformationStack.back());
	}

	void BatchRenderer2D::Pop()
	{
		if (s_Data->TransformationStack.size() > 1)
		{
			s_Data->TransformationStack.pop_back();
		}

		s_Data->TransformationBack = &(s_Data->TransformationStack.back());
	}

	void BatchRenderer2D::DrawString(const Ref<Font>& font, const std::string& text, const glm::vec3& position, uint32_t color)
	{
		float ts = 0.0f;
		bool found = false;
		for (int i = 0; i < s_Data->TextureSlots.size(); i++)
		{
			if (s_Data->TextureSlots[i] == font->GetId())
			{
				ts = (float)(i + 1);
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (s_Data->TextureSlots.size() >= 32)
			{
				End();
				Flush();
				Begin();
			}

			s_Data->TextureSlots.push_back(font->GetId());
			ts = (float)(s_Data->TextureSlots.size());
		}
		
		float x = position.x;
		
		ftgl::texture_font_t* ftFont = font->GetFTGLFont();

		for (int i = 0; i < text.length(); i++)
		{
			char c = text.at(i);
			ftgl::texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);

			if (glyph != NULL)
			{
				if (i > 0)
				{
					float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
					x += kerning;
				}

				float x0 = x + glyph->offset_x;
				float y0 = position.y + glyph->offset_y;
				float x1 = x0 + glyph->width;
				float y1 = y0 - glyph->height;

				float u0 = glyph->s0;
				float v0 = glyph->t0;
				float u1 = glyph->s1;
				float v1 = glyph->t1;

				s_Data->Buffer->vertex = *(s_Data->TransformationBack) * glm::vec4(x0, y0, 0.0f, 1.0f);
				s_Data->Buffer->uv = glm::vec2(u0, v0);
				s_Data->Buffer->tid = ts;
				s_Data->Buffer->color = color;
				s_Data->Buffer++;

				s_Data->Buffer->vertex = *(s_Data->TransformationBack) * glm::vec4(x0, y1, 0.0f, 1.0f);
				s_Data->Buffer->uv = glm::vec2(u0, v1);
				s_Data->Buffer->tid = ts;
				s_Data->Buffer->color = color;
				s_Data->Buffer++;
				
				s_Data->Buffer->vertex = *(s_Data->TransformationBack) * glm::vec4(x1, y1, 0.0f, 1.0f);
				s_Data->Buffer->uv = glm::vec2(u1, v1);
				s_Data->Buffer->tid = ts;
				s_Data->Buffer->color = color;
				s_Data->Buffer++;
				
				s_Data->Buffer->vertex = *(s_Data->TransformationBack) * glm::vec4(x1, y0, 0.0f, 1.0f);
				s_Data->Buffer->uv = glm::vec2(u1, v0);
				s_Data->Buffer->tid = ts;
				s_Data->Buffer->color = color;
				s_Data->Buffer++;

				s_Data->IndexCount += 6;

				x += glyph->advance_x;
			}
		}
	}

	void BatchRenderer2D::End()
	{
		s_Data->Vbo->Unmap();
		s_Data->Vbo->Unbind();
	}

	void BatchRenderer2D::Flush()
	{
		for (int i = 0; i < s_Data->TextureSlots.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, s_Data->TextureSlots[i]);
		}

		s_Data->Vao->Bind();

		glDrawElements(GL_TRIANGLES, s_Data->IndexCount, GL_UNSIGNED_INT, NULL);

		s_Data->Vao->Unbind();
		s_Data->IndexCount = 0;
	}
}
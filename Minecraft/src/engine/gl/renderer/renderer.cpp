#include <mcpch.h>

#include "renderer.h"
#include <glad/glad.h>

namespace Minecraft
{

	void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id, unsigned severity, int length, const char* message, const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         MC_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       MC_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          MC_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: MC_TRACE(message); return;
		}
	}

	void Renderer::Init()
	{
		glEnable(GL_BLEND);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LESS);

#ifdef MC_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif
	}

	BufferLayout Renderer::m_Layout =
	{
		{ ShaderDataType::Byte3, "a_Coordinates" },
		{ ShaderDataType::Byte2, "a_TexCoords" },
		{ ShaderDataType::Byte, "a_Tid"}
	};

	void Renderer::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void Renderer::Shutdown()
	{

	}

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::Submit(const Ref<Chunk>& chunk)
	{
	
	}

	void Renderer::DrawString(const Ref<Font>& font, const std::string& text, const glm::vec3& position, const glm::vec4& color)
	{

		/*
		float ts = 0.0f;
		bool found = false;
		for (int i = 0; i < m_TextureSlots.size(); i++)
		{
			if (m_TextureSlots[i] == font->GetId())
			{
				ts = (float)(i + 1);
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
		}
		*/
	}
}
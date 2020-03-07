#include <mcpch.h>

#include "renderer.h"
#include "batchrenderer2d.h"
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
		BatchRenderer2D::Init();
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

	void Renderer::DrawString2D(const Ref<Font>& font, const std::string& text, const glm::vec3& position, const glm::vec4& color)
	{
		int r = color.x * 255.0f;
		int g = color.y * 255.0f;
		int b = color.z * 255.0f;
		int a = color.w * 255.0f;

		uint32_t col = a << 24 | b << 16 | g << 8 | r;
		BatchRenderer2D::DrawString(font, text, position, col);
	}
}
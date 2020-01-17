#include "mcpch.h"
#include "testlayer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Minecraft
{
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam);

	TestLayer::TestLayer(const std::string& name) : Layer(name) 
	{ 
		m_VertexArray = Minecraft::VertexArray::Create();
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Minecraft::Ref<Minecraft::VertexBuffer> vbo = Minecraft::VertexBuffer::Create(vertices, sizeof(vertices));
		Minecraft::BufferLayout layout =
		{
			{Minecraft::ShaderDataType::Float3, "a_Position"},
			{Minecraft::ShaderDataType::Float4, "a_Color"}
		};
		vbo->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vbo);

		uint32_t indices[3] = { 0,1,2 };

		Minecraft::Ref<Minecraft::IndexBuffer> ibo = Minecraft::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

		m_VertexArray->SetIndexBuffer(ibo);
		m_SquareVA = Minecraft::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Minecraft::Ref<Minecraft::VertexBuffer> squareVB = Minecraft::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Minecraft::ShaderDataType::Float3, "a_Position" },
			{ Minecraft::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Minecraft::Ref<Minecraft::IndexBuffer> squareIB = Minecraft::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIB);

		m_FlatColorShader = m_ShaderLibrary.Load("res/shaders/flatcolor.glsl");
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, 1280, 720);

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);

		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	}

	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* message,
		const void* userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         MC_CRITICAL(message); return;
		case GL_DEBUG_SEVERITY_MEDIUM:       MC_ERROR(message); return;
		case GL_DEBUG_SEVERITY_LOW:          MC_WARN(message); return;
		case GL_DEBUG_SEVERITY_NOTIFICATION: MC_TRACE(message); return;
		}

		MC_ASSERT(false, "Unknown severity level!");
	}

	void TestLayer::OnAttach()
	{
	}

	void TestLayer::OnDetach()
	{

	}

	void TestLayer::OnEvent(Event& event)
	{

	}

	void TestLayer::OnUpdate(Timestep ts)
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_FlatColorShader->Bind();
		m_VertexArray->Bind();
		//glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		//m_FlatColorShader->SetFloat4("u_Color", glm::vec4({ 1.0f,1.0f,1.0f, 1.0f }));

		//for (int y = 0; y < 20; y++)
		//{
			//for (int x = 0; x < 20; x++)
			//{
				//glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				//glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				//m_FlatColorShader->SetMat4("u_Transform", transform);
	//	MC_INFO(m_VertexArray->GetIndexBuffer()->GetCount());
		glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

				//Minecraft::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			//}
		//}
		
	}
}
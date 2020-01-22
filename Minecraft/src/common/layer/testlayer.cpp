#include "mcpch.h"
#include "testlayer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Minecraft
{
	std::vector<Block> TestLayer::s_Blocks = std::vector<Block>();

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

	TestLayer::TestLayer(const std::string& name) : Layer(name)
	{
		m_Camera = CreateRef<Camera>(glm::perspective(glm::radians(60.0f), 16.0f / 9.0f, 0.1f, 1000.0f));

		m_VertexArray = VertexArray::Create();
		/*
		float frontFace[4 * 9] = {
			0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f / 16.0f * 3, 1 - 1.0f / 16.0f,
			1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f / 16.0f * 4, 1 - 1.0f / 16.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f / 16.0f * 4, 1 - 0.0f,
			0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f / 16.0f * 3, 1 - 0.0f
		};

		uint32_t indices[6] = {
			0,1,3,
			1,2,3
		};

		Ref<VertexBuffer> vbo = VertexBuffer::Create(frontFace, sizeof(frontFace));
		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TextureCoordinates"}
		};
		vbo->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vbo);
		Ref<IndexBuffer> ibo = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(ibo);
		*/
		s_Blocks.push_back(GrassBlock());
		m_World = CreateRef<World>(1, 1, 1);

		m_Layout =
		{
			{ ShaderDataType::Byte3, "a_Coordinates" },
			{ ShaderDataType::Byte2, "a_TexCoords" }
		};

		BufferData();

		m_FlatColorShader = m_ShaderLibrary.Load("res/shaders/chunkshader.glsl");
		m_Texture = Texture::Create("res/textures/blocks.jpg");
		glEnable(GL_BLEND);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);

#ifdef MC_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthFunc(GL_LESS);
		glViewport(0, 0, 1280, 720); // set on resize
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

	void TestLayer::GetData(vertex* data, uint8_t x, uint8_t y, uint8_t z, uint32_t& i)
	{
		s_Blocks[0].GetBackVertexData(data, x, y, z, i);
		s_Blocks[0].GetFrontVertexData(data, x, y, z, i);
		s_Blocks[0].GetTopVertexData(data, x, y, z, i);
		s_Blocks[0].GetBottomVertexData(data, x, y, z, i);
		s_Blocks[0].GetLeftVertexData(data, x, y, z, i);
		s_Blocks[0].GetRightVertexData(data, x, y, z, i);
	}

	void TestLayer::BufferData()
	{
		vertex* data = m_World->GetChunkData();
		Ref<VertexBuffer> vbo = VertexBuffer::Create(data, sizeof(*data) * TOTAL_VERTICES);
		vbo->SetLayout(m_Layout);
		m_VertexArray->SetVertexBuffer(0, vbo);
		delete data;
	}

	void TestLayer::OnUpdate(Timestep ts)
	{

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_Camera->Update();


		if (Input::IsKeyPressed(KeyCode::LeftControl) && Input::IsKeyPressed(KeyCode::R))
		{
			m_FlatColorShader->Reload();
			BufferData();
		}

		m_FlatColorShader->Bind();
		m_FlatColorShader->SetMat4("u_ViewMatrix", (m_Camera->GetViewMatrix()));
		m_FlatColorShader->SetMat4("u_ProjectionMatrix", m_Camera->GetProjectionMatrix());
		m_FlatColorShader->SetFloat4("u_Color", glm::vec4({ 1.0f,1.0f,1.0f, 1.0f }));
		m_FlatColorShader->SetMat4("u_Transform", glm::mat4(1.0f));

		m_Texture->Bind(0);
		m_VertexArray->Bind();

		//glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
		//glDrawElements(GL_TRIANGLES, TOTAL_VERTICES, GL_UNSIGNED_BYTE, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, TOTAL_VERTICES);
	}
}
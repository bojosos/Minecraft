#pragma once

#include "common/common.h"
#include "engine/gl/vao.h"
#include "engine/gl/shader.h"

namespace Minecraft
{
	class Mesh
	{
	public:
		Mesh(const Ref<VertexArray>& vao, const Ref<Shader>& shader);
		~Mesh();

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		static Ref<Mesh> Create(const Ref<VertexArray>& vao, const Ref<Shader>& shader);

	private:
		Ref<VertexArray> m_VertexArray;
		Ref<Shader> m_Shader;
	};
}
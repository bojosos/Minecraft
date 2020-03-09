#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Minecraft
{
	class Shader
	{
	public:
		Shader(const std::string& name, const std::string& vertSrc, const std::string& fragSrc);
		Shader(const std::string& filepath);
		void Reload();

		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& name, int value);
		void SetIntV(const std::string& name, uint32_t count, int* ptr);
		void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		void SetMat4(const std::string& name, const glm::mat4& value);

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntV(const std::string& name, int count, int* ptr);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2& value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3& value);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& value);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

		uint32_t GetUniformLocation(const std::string& name);
		void RetrieveLocations(const std::vector<std::string>& uniforms);
		
		const std::string& GetName() { return m_Name; };

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertSrc, const std::string& fragSrc);

	private:
		void Load(const std::string& path);
		void Compile(const std::unordered_map<uint32_t, std::string>& shaderSources);

	private:
		std::string m_Filepath;
		std::string m_Name;
		uint32_t m_RendererID;
		std::unordered_map<std::string, GLint> m_UniformLocations;
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;

	private:
		std::string m_Name;
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}

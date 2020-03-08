#pragma once

#include "common/common.h"
#include <glad/glad.h>

namespace Minecraft
{

	struct TextureParameters 
	{
		TextureParameters() = default;
	};

	class Texture
	{
	public:
		Texture(uint32_t width, uint32_t height);
		Texture(const std::string& filepath);
		~Texture();

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		void Bind(uint32_t slot) const;
		void SetData(void* data, uint32_t size);
		void SetData(void* data);

		inline uint32_t GetID() { return m_RendererID; }

		static Ref<Texture> Create(uint32_t width, uint32_t height);
		static Ref<Texture> Create(const std::string& filepath);

	private:
		GLenum m_InternalFormat, m_DataFormat;
		uint32_t m_RendererID;
		std::string m_FilePath;
		uint32_t m_Width, m_Height;
	};
}
#include "mcpch.h"
#include "texture.h"

#ifdef MC_WEB
#include <GLFW/glfw3.h>
#else
#include <glad/glad.h>
#endif

#include "stb_image.h"

namespace Minecraft
{
	static GLenum TextureChannelToOpenGLChannel(TextureChannel channel)
	{
		switch (channel)
		{
		case Minecraft::TextureChannel::CHANNEL_RED:                return GL_RED;
		case Minecraft::TextureChannel::CHANNEL_RG:                 return GL_RG;
		case Minecraft::TextureChannel::CHANNEL_RGB:                return GL_RGB;
		case Minecraft::TextureChannel::CHANNEL_RGBA:               return GL_RGBA;
		case Minecraft::TextureChannel::CHANNEL_DEPTH_COMPONENT:    return GL_DEPTH_COMPONENT;
#ifndef MC_WEB
		case Minecraft::TextureChannel::CHANNEL_BGR:                return GL_BGR;
		case Minecraft::TextureChannel::CHANNEL_BGRA:               return GL_BGRA;
		case Minecraft::TextureChannel::CHANNEL_STENCIL_INDEX:      return GL_STENCIL_INDEX;
#endif
		}
		MC_ASSERT(false, "Unknown TextureChannel!");
		return GL_NONE;
	}

	static GLenum TextureFormatToOpenGLFormat(TextureFormat format)
	{
		switch (format)
		{
		case Minecraft::TextureFormat::RGB:     return GL_RGB;
		case Minecraft::TextureFormat::RGBA:    return GL_RGBA;
		}
		MC_ASSERT(false, "Unknown TextureFormat!");
		return GL_NONE;
	}

	static GLenum TextureFormatToOpenGLInternalFormat(TextureFormat format)
	{
		switch (format)
		{
		case Minecraft::TextureFormat::RGB:     return GL_RGB8;
		case Minecraft::TextureFormat::RGBA:    return GL_RGBA8;
		}
		MC_ASSERT(false, "Unknown TextureFormat!");
		return GL_NONE;
	}

	static GLenum TextureFilterToOpenGLFilter(TextureFilter filter)
	{
		switch (filter)
		{
		case Minecraft::TextureFilter::LINEAR:  return GL_LINEAR;
		case Minecraft::TextureFilter::NEAREST: return GL_NEAREST;
		}
		MC_ASSERT(false, "Unknown TextureFilter!");
		return GL_NONE;
	}

	static GLenum TextureWrapToOpenGLWrap(TextureWrap wrap)
	{
		switch (wrap)
		{
		case Minecraft::TextureWrap::REPEAT:             return GL_REPEAT;
		case Minecraft::TextureWrap::MIRRORED_REPEAT:    return GL_MIRRORED_REPEAT;
		case Minecraft::TextureWrap::CLAMP_TO_EDGE:      return GL_CLAMP_TO_EDGE;
#ifndef MC_WEB
		case Minecraft::TextureWrap::CLAMP_TO_BORDER:    return GL_CLAMP_TO_BORDER;
#endif
		}
		MC_ASSERT(false, "Unknown TextureWrap!");
		return GL_NONE;
	}

#ifndef MC_WEB
	static GLenum TextureSwizzleToOpenGLSwizzle(SwizzleType swizzle)
	{
		switch (swizzle)
		{
		case Minecraft::SwizzleType::SWIZZLE_RGBA:  return GL_TEXTURE_SWIZZLE_RGBA;
		case Minecraft::SwizzleType::SWIZZLE_R:     return GL_TEXTURE_SWIZZLE_R;
		case Minecraft::SwizzleType::SWIZZLE_G:     return GL_TEXTURE_SWIZZLE_G;
		case Minecraft::SwizzleType::SWIZZLE_B:     return GL_TEXTURE_SWIZZLE_B;
		case Minecraft::SwizzleType::SWIZZLE_A:     return GL_TEXTURE_SWIZZLE_A;
		}
		MC_ASSERT(false, "Unknown TextureSwizzle!");
		return GL_NONE;
	}
#endif

	static GLint TextureSwizzleColorToOpenGLSwizzleColor(SwizzleChannel color)
	{
		switch (color)
		{
		case Minecraft::SwizzleChannel::RED:     return GL_RED;
		case Minecraft::SwizzleChannel::GREEN:   return GL_GREEN;
		case Minecraft::SwizzleChannel::BLUE:    return GL_BLUE;
		case Minecraft::SwizzleChannel::ALPHA:   return GL_ALPHA;
		case Minecraft::SwizzleChannel::ONE:     return GL_ONE;
		case Minecraft::SwizzleChannel::ZERO:    return GL_ZERO;
		}
		MC_ASSERT(false, "Unknown TextureSwizzleColor!");
		return GL_NONE;
	}

	Ref<Texture> Texture::Create(uint32_t width, uint32_t height, const TextureParameters& parameters)
	{
		return CreateRef<Texture>(width, height, parameters);
	}

	Ref<Texture> Texture::Create(const std::string& filepath, const TextureParameters& parameters)
	{
		return CreateRef<Texture>(filepath, parameters);
	}

	Texture::Texture(uint32_t width, uint32_t height, const TextureParameters& parameters) : m_Width(width), m_Height(height), m_Parameters(parameters)
	{
#ifdef MC_WEB
		glGenTextures(1, &m_RendererID);
#else
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
#endif

#ifdef MC_WEB
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexStorage2D(GL_TEXTURE_2D, 1, TextureFormatToOpenGLInternalFormat(m_Parameters.Format), m_Width, m_Height);
#else
		glTextureStorage2D(m_RendererID, 1, TextureFormatToOpenGLInternalFormat(m_Parameters.Format), m_Width, m_Height);
#endif

#ifdef MC_WEB
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterToOpenGLFilter(m_Parameters.Filter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterToOpenGLFilter(m_Parameters.Filter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToOpenGLWrap(m_Parameters.Wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToOpenGLWrap(m_Parameters.Wrap));
#else
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, TextureFilterToOpenGLFilter(m_Parameters.Filter));
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, TextureFilterToOpenGLFilter(m_Parameters.Filter));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, TextureWrapToOpenGLWrap(m_Parameters.Wrap));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, TextureWrapToOpenGLWrap(m_Parameters.Wrap));
		if (m_Parameters.Swizzle.Type != SwizzleType::NONE)
		{
			if (m_Parameters.Swizzle.Type == SwizzleType::SWIZZLE_RGBA)
			{

				GLint tmp[4];
				for (int i = 0; i < 4; i++)
				{
					tmp[i] = TextureSwizzleColorToOpenGLSwizzleColor(m_Parameters.Swizzle.Swizzle[i]);
				}

				glTextureParameteriv(m_RendererID, TextureSwizzleToOpenGLSwizzle(m_Parameters.Swizzle.Type), tmp);
			}
			else
			{
				glTextureParameteri(m_RendererID, TextureSwizzleToOpenGLSwizzle(m_Parameters.Swizzle.Type), TextureSwizzleColorToOpenGLSwizzleColor(m_Parameters.Swizzle.Swizzle[0]));
			}
		}
#endif

	}

	Texture::Texture(const std::string& path, const TextureParameters& parameters) : m_FilePath(path), m_Parameters(parameters)
	{
		std::string filepath = DIRECTORY_PREFIX + path;
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		MC_ASSERT(data, "Failed to load texture!");
		m_Width = width;
		m_Height = height;

		if (channels == 4)
		{
			m_Parameters.Format = TextureFormat::RGBA;
		}
		else if (channels == 3)
		{
			m_Parameters.Format = TextureFormat::RGB;
		}
#ifdef MC_WEB
		glGenTextures(1, &m_RendererID);
#else
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
#endif

#ifdef MC_WEB
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexImage2D(GL_TEXTURE_2D, 0, TextureFormatToOpenGLFormat(m_Parameters.Format), width, height, 0, TextureFormatToOpenGLFormat(m_Parameters.Format), GL_UNSIGNED_BYTE, data);
#else
		glTextureStorage2D(m_RendererID, 1, TextureFormatToOpenGLInternalFormat(m_Parameters.Format), m_Width, m_Height);
#endif
#ifdef MC_WEB
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterToOpenGLFilter(m_Parameters.Filter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterToOpenGLFilter(m_Parameters.Filter));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToOpenGLWrap(m_Parameters.Wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToOpenGLWrap(m_Parameters.Wrap));
#else
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, TextureFilterToOpenGLFilter(m_Parameters.Filter));
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, TextureFilterToOpenGLFilter(m_Parameters.Filter));

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, TextureWrapToOpenGLWrap(m_Parameters.Wrap));
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, TextureWrapToOpenGLWrap(m_Parameters.Wrap));
#endif
#ifndef MC_WEB
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, TextureFormatToOpenGLFormat(m_Parameters.Format), GL_UNSIGNED_BYTE, data);
#endif

		MC_INFO("Loaded texture {0}, {1}x{2}x{3}.", m_FilePath, m_Width, m_Height, channels);
		stbi_image_free(data);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void Texture::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_Parameters.Format == TextureFormat::RGBA ? 4 : 3;
		MC_ASSERT(size == m_Width * m_Height * bpp, "Data must be an entire texture!");
#ifdef MC_WEB
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, TextureFormatToOpenGLFormat(m_Parameters.Format), GL_UNSIGNED_BYTE, data);
#else
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, TextureFormatToOpenGLFormat(m_Parameters.Format), GL_UNSIGNED_BYTE, data);
#endif
	}

	void Texture::SetData(void* data, TextureChannel channel)
	{
#ifdef MC_WEB
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, TextureChannelToOpenGLChannel(channel), GL_UNSIGNED_BYTE, data);
#else
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, TextureChannelToOpenGLChannel(channel), GL_UNSIGNED_BYTE, data);
#endif
	}

	void Texture::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}
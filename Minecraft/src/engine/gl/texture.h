#pragma once

#include "common/common.h"

namespace Minecraft
{

	enum class TextureChannel
	{
		NONE,
		CHANNEL_RED, 
		CHANNEL_RG,
		CHANNEL_RGB, 
		CHANNEL_BGR,
		CHANNEL_RGBA, 
		CHANNEL_BGRA, 
		CHANNEL_DEPTH_COMPONENT, 
		CHANNEL_STENCIL_INDEX
	};

	enum class TextureWrap
	{
		NONE = 0,
		REPEAT,
		MIRRORED_REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER
	};

	enum class TextureFilter
	{
		NONE = 0,
		LINEAR,
		NEAREST
	};

	enum class TextureFormat
	{
		NONE = 0,
		RGB,
		RGBA
	};

	enum class SwizzleType
	{
		NONE = 0,
		SWIZZLE_RGBA,
		SWIZZLE_R,
		SWIZZLE_G,
		SWIZZLE_B,
		SWIZZLE_A
	};

	enum class SwizzleChannel
	{
		NONE = 0,
		RED,
		GREEN,
		BLUE,
		ALPHA,
		ONE,
		ZERO
	};

	struct TextureSwizzle
	{
		SwizzleType Type;
		SwizzleChannel Swizzle[4];

		TextureSwizzle()
		{
			Type = SwizzleType::NONE;
			Swizzle[0] = SwizzleChannel::NONE;
		}

		TextureSwizzle(SwizzleType type, SwizzleChannel swizzle) : Type(type)
		{
			MC_ASSERT(type != SwizzleType::SWIZZLE_RGBA, "A SWIZZLE_RGBA requires 4 parameters!");
			Swizzle[0] = swizzle;
		}

		TextureSwizzle(SwizzleType type, SwizzleChannel ar[4]) : Type(type)
		{
			MC_ASSERT(type == SwizzleType::SWIZZLE_RGBA, "A four parameter TEXTURE_SWIZZLE has to be RGBA!");
			Swizzle[0] = ar[0];
			Swizzle[1] = ar[1];
			Swizzle[2] = ar[2];
			Swizzle[3] = ar[3];
		}

	};


	struct TextureParameters 
	{
		TextureParameters()
		{
			Format = TextureFormat::RGBA;
			Filter = TextureFilter::NEAREST;
			Wrap = TextureWrap::REPEAT;
		}

		TextureParameters(TextureFormat format, TextureFilter filter, TextureWrap wrap, TextureSwizzle swizzle = {}) : Format(format), Filter(filter), Wrap(wrap), Swizzle(swizzle)
		{

		}

		TextureFormat Format;
		TextureFilter Filter;
		TextureWrap Wrap;
		TextureSwizzle Swizzle;
	};

	class Texture
	{
	public:
		Texture(uint32_t width, uint32_t height, const TextureParameters& parameters);
		Texture(const std::string& filepath, const TextureParameters& parameters);
		~Texture();

		inline uint32_t GetWidth() const { return m_Width; }
		inline uint32_t GetHeight() const { return m_Height; }

		void Bind(uint32_t slot) const;
		void SetData(void* data, uint32_t size);
		void SetData(void* data, TextureChannel channel = TextureChannel::CHANNEL_RGBA);

		static Ref<Texture> Create(uint32_t width, uint32_t height, const TextureParameters& parameters = {});
		static Ref<Texture> Create(const std::string& filepath, const TextureParameters& parameters = {});

		bool operator==(const Ref<Texture>& other)
		{
			return (other->m_RendererID == m_RendererID);
		}

	private:
		TextureParameters m_Parameters;
		uint32_t m_RendererID;
		std::string m_FilePath;
		uint32_t m_Width, m_Height;
	};
}

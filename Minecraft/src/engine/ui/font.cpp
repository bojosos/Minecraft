#include "mcpch.h"
#include "font.h"

namespace Minecraft
{

	Font::Font(const std::string& name, const std::string& filepath, float size) : m_Name(name), m_Filepath(filepath), m_Size(size)
	{
		m_Atlas = ftgl::texture_atlas_new(512, 512, 1);
		m_Font = ftgl::texture_font_new_from_file(m_Atlas, m_Size, m_Filepath.c_str());

		SwizzleChannel channels[4] = { SwizzleChannel::ONE, SwizzleChannel::ONE, SwizzleChannel::ONE, SwizzleChannel::RED };
		TextureSwizzle swizzle = { SwizzleType::SWIZZLE_RGBA, channels};
		TextureParameters params = { TextureFormat::RGBA, TextureFilter::LINEAR, TextureWrap::REPEAT, swizzle};

		m_Texture = Texture::Create(512, 512, params);
		m_Texture->SetData(m_Atlas->data, TextureChannel::CHANNEL_RED);
	}

	Ref<Texture> Font::GetTexture()
	{
		//TODO: May not be necessary
		m_Texture->SetData(m_Atlas->data, TextureChannel::CHANNEL_RED);
		return m_Texture;
	}

	std::vector<Ref<Font>> FontManager::s_Fonts;

	void FontManager::Add(const Ref<Font>& font)
	{
		s_Fonts.push_back(font);
	}

	Ref<Font> FontManager::Get(const std::string& name)
	{
		for (Ref<Font>& font : s_Fonts)
		{
			if (font->GetName() == name)
			{
				return font;
			}
		}
		MC_ERROR("Unrecognized font, using fallback font {0}!", s_Fonts[0]->GetName());
		return s_Fonts[0];
	}

	Ref<Font> FontManager::Get(const std::string& name, float size)
	{
		for (Ref<Font>& font : s_Fonts)
		{
			if (font->GetName() == name)
			{
				if (font->GetSize() == size)
				{
					return font;
				}
				else
				{
					s_Fonts.push_back(CreateRef<Font>(name, font->GetFilepath(), size));
					return s_Fonts.back();
				}
			}
		}
		MC_ERROR("Unrecognized font, using fallback font {0}!", s_Fonts[0]->GetName());
		if (s_Fonts[0]->GetSize() == size)
		{
			return s_Fonts[0];
		}
		else
		{
			s_Fonts.push_back(CreateRef<Font>(name, DEFAULT_FONT_PATH, size));
		}

		return s_Fonts[0];
	}

}
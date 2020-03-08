#include "mcpch.h"
#include "font.h"

namespace Minecraft
{

	Font::Font(const std::string& name, const std::string& filepath, uint32_t size) : m_Name(name), m_Filepath(filepath), m_Size(size)
	{
		m_Atlas = ftgl::texture_atlas_new(512, 512, 1);
		m_Font = ftgl::texture_font_new_from_file(m_Atlas, m_Size, m_Filepath.c_str());

		m_Texture = Texture::Create(512, 512);
		m_Atlas->id = m_Texture->GetID();
		m_Texture->SetData(m_Atlas->data);
	}

	Ref<Texture> Font::GetTexture()
	{
		m_Texture->SetData(m_Atlas->data);
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
		MC_ASSERT(false, "Font " + name + " not found!");
	}

	Ref<Font> FontManager::Get(const std::string& name, uint32_t size)
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
		MC_ASSERT(false, "Font " + name + " not found!");
	}

}
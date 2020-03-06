#pragma once
#include <freetype-gl.h>

namespace Minecraft
{
	class Font
	{
	public:
		Font(const std::string& filepath, const std::string& name, uint32_t size);

		inline const std::string& GetName() const
		{
			return m_Name;
		}

		inline const uint32_t GetSize() const
		{
			return m_Size;
		}

		inline const uint32_t GetId() const
		{
			return m_Atlas->id;
		}

		inline const std::string& GetFilepath() const
		{
			return m_Filepath;
		}

		inline ftgl::texture_font_t* GetFTGLFont() const
		{
			return m_Font;
		}

		inline ftgl::texture_atlas_t* GetFTGLAtlas() const
		{
			return m_Atlas;
		}

	private:
		ftgl::texture_atlas_t* m_Atlas;
		ftgl::texture_font_t* m_Font;
		uint32_t m_Size;
		std::string m_Name, m_Filepath;
	};

	class FontManager
	{
	public:
		static void Add(const Ref<Font>& font);
		static Ref<Font> Get(const std::string& name);
		static Ref<Font> Get(const std::string& name, uint32_t size);

	private:
		static std::vector<Ref<Font>> s_Fonts;
		FontManager();
	};
}
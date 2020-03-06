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

		inline ftgl::texture_font_t* GetFTGLFont() const
		{
			return m_Font;
		}

	private:
		ftgl::texture_atlas_t* m_Atlas;
		ftgl::texture_font_t* m_Font;
		uint32_t m_Size;
		std::string m_Name, m_Filepath;
	};
}
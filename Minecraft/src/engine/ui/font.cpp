#include "mcpch.h"
#include "font.h"

namespace Minecraft
{

	Font::Font(const std::string& name, const std::string& filepath, uint32_t size) : m_Name(name), m_Filepath(filepath), m_Size(size)
	{
		m_Atlas = ftgl::texture_atlas_new(512, 512, 2);
		m_Font = ftgl::texture_font_new_from_file(m_Atlas, m_Size, m_Filepath.c_str());
	}
}
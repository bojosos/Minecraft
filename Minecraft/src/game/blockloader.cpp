#include "mcpch.h"
#include "blockloader.h"
#include <sol.hpp>

namespace Minecraft
{

	void BlockLoader::IInitTextures(const Ref<Shader>& shader)
	{
#ifdef MC_WEB
		shader->SetInt("u_Texture_1", 1);
		shader->SetInt("u_Texture_0", 0);
		shader->SetInt("u_Texture_2", 2);
		shader->SetInt("u_Texture_3", 3);
		shader->SetInt("u_Texture_4", 4);
		shader->SetInt("u_Texture_5", 5);
		shader->SetInt("u_Texture_6", 6);
		shader->SetInt("u_Texture_7", 7);
#else
		MC_ASSERT(m_Textures.size() <= 8, "Only 8 textures supported at a time");
		int* samplers = new int[m_Textures.size()];

		for (int i = 0; i < m_Textures.size(); i++)
		{
			samplers[i] = i;
		}
		shader->SetIntV("u_Textures", m_Textures.size(), samplers);
#endif
	}

	void BlockLoader::IBindTextures()
	{
		for (int i = 0; i < m_Textures.size(); i++)
		{
			m_Textures[i]->Bind(i);
		}
	}

	uint8_t BlockLoader::IAddTexture(const std::string& filepath)
	{
		m_Textures.push_back(Texture::Create(filepath));
		return m_CurrentTexture++;
	}

	void BlockLoader::IGetData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint16_t type, uint32_t& i)
	{
		m_Blocks[type].GetBackVertexData(res, x, y, z, i);
		m_Blocks[type].GetFrontVertexData(res, x, y, z, i);
		m_Blocks[type].GetUpVertexData(res, x, y, z, i);
		m_Blocks[type].GetDownVertexData(res, x, y, z, i);
		m_Blocks[type].GetLeftVertexData(res, x, y, z, i);
		m_Blocks[type].GetRightVertexData(res, x, y, z, i);
	}
}
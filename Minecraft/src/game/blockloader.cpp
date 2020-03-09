#include "mcpch.h"
#include "blockloader.h"
#include <sol.hpp>

namespace Minecraft
{

	BlockLoader::BlockLoader() { }

	void BlockLoader::IInitTextures(const Ref<Shader>& shader)
	{
		int* samplers = new int[m_Textures.size()];

		for (int i = 0; i < m_Textures.size(); i++)
		{
			m_Textures[i]->Bind(i);
			samplers[i] = i;
		}
		shader->SetIntV("u_Textures", m_Textures.size(), samplers);
	}

	void BlockLoader::ISomething()
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

	void BlockLoader::IGetData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint16_t type, uint32_t& i)
	{
		m_Blocks[type].GetBackVertexData(res, x, y, z, i);
		m_Blocks[type].GetFrontVertexData(res, x, y, z, i);
		m_Blocks[type].GetUpVertexData(res, x, y, z, i);
		m_Blocks[type].GetDownVertexData(res, x, y, z, i);
		m_Blocks[type].GetLeftVertexData(res, x, y, z, i);
		m_Blocks[type].GetRightVertexData(res, x, y, z, i);
	}
}
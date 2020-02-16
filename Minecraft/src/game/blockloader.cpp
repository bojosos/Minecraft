#include "mcpch.h"
#include "blockloader.h"
#define SOL_ALL_SAFETIES_ON 1
#define SOL_PRINT_ERRORS 1
#include <sol.hpp>

namespace Minecraft
{

	BlockLoader::BlockLoader() { }

	void BlockLoader::ILoadDefaultBlocks(const std::string& filepath)
	{
		sol::state lua;
		lua.open_libraries(sol::lib::base, sol::lib::coroutine, sol::lib::string, sol::lib::io);
		lua.set_function("Block", &BlockLoader::AddBlock, this);
		lua.set_function("Texture", &BlockLoader::AddTexture, this);

		auto a = lua.script_file(filepath);
	}

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

	void BlockLoader::AddBlock(const std::string& shortname, const std::string& longname, bool solid, const sol::table& sides, bool transparent)
	{
		MC_ASSERT(sides.size() == 12, "Each block must have 12 sides!");
		MC_INFO("Adding Block: {0}", longname);
		m_Blocks.push_back(Block(shortname, longname, solid, sides, transparent, m_CurrentTexture));
	}

	void BlockLoader::AddTexture(const std::string& filepath)
	{
		m_Textures.push_back(Texture::Create(filepath));
		m_CurrentTexture++;
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
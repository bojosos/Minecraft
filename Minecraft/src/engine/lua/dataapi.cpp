#include "mcpch.h"
#include "luaapi.h"
#include "game/blockloader.h"
#include "common/scripting.h"

namespace Minecraft
{
	enum class MeshType
	{
		Block,
		Cross,
		None
	};

	void LuaApi::AddEnums()
	{
		auto meshType = ScriptingEngine::AddTable("MeshType");
		meshType["Block"] = MeshType::Block;
		meshType["Cross"] = MeshType::Cross;
		meshType["None"] = MeshType::None;
	}

	void LuaApi::AddBlockApi(sol::table& table)
	{
		table["AddBlock"] = [&](const sol::table& blockData)
		{
			Block block(blockData["shortname"].get<std::string>(), blockData["longname"].get<std::string>(), blockData["sides"], blockData["solid"].get<bool>(), blockData["transparent"].get<bool>(), blockData["tid"].get<uint8_t>());

			BlockLoader::AddBlock(block);
		};

		table["AddTexture"] = [&](const std::string& filepath)
		{
			return BlockLoader::AddTexture(filepath);
		};
	}

	void LuaApi::LuaDataApiInit()
	{
		auto data = ScriptingEngine::AddTable("blocks");
		AddBlockApi(data);
		data["SetNoise"] = [&](const sol::table& table)
		{

		};
	}

}

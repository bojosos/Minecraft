#pragma once

#include "engine.h"
#include "game/block.h"

namespace Minecraft
{
	class BlockLoader
	{
	public:
		inline static void LoadDefaultBlocks(const std::string& filepath, const Ref<Shader>& shader)
		{
			Get().ILoadDefaultBlocks(filepath);
			Get().IInitTextures(shader);
		}

		inline static void GetData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint16_t type, uint32_t& i)
		{
			Get().IGetData(res, x, y ,z, type, i);
		}

	private:
		static BlockLoader& Get()
		{
			static BlockLoader instance;
			return instance;
		}

		void ILoadDefaultBlocks(const std::string& filepath);
		void IInitTextures(const Ref<Shader>& shader);

		void IGetData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint16_t type, uint32_t& i);
		void AddBlock(const std::string& shortname, const std::string& longname, bool solid, const sol::table& sides, bool transparent);
		void AddTexture(const std::string& filepath);

	private:
		std::vector<Block> m_Blocks;
		std::vector<Ref<Texture>> m_Textures;
		uint8_t m_CurrentTexture = -1;
		BlockLoader();
	};
}
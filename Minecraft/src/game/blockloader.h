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

		inline static Block& GetBlock(uint16_t type)
		{
			return Get().m_Blocks[type];
		}

		inline static void GetLeftVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint16_t type, uint32_t& i)
		{
			Get().m_Blocks[type].GetLeftVertexData(res, x, y, z, i);
		}

		inline static void GetRightVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint16_t type, uint32_t& i)
		{
			Get().m_Blocks[type].GetRightVertexData(res, x, y, z, i);
		}

		inline static void GetFrontVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint16_t type, uint32_t& i)
		{
			Get().m_Blocks[type].GetFrontVertexData(res, x, y, z, i);
		}

		inline static void GetBackVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint16_t type, uint32_t& i)
		{
			Get().m_Blocks[type].GetBackVertexData(res, x, y, z, i);
		}

		inline static void GetUpVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint16_t type, uint32_t& i)
		{
			Get().m_Blocks[type].GetUpVertexData(res, x, y, z, i);
		}

		inline static void GetDownVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint16_t type, uint32_t& i)
		{
			Get().m_Blocks[type].GetDownVertexData(res, x, y, z, i);
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
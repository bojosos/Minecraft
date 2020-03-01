#pragma once

#include "engine.h"
#include "game/block.h"

namespace Minecraft
{
	class BlockLoader
	{
	public:

		inline static Block& GetBlock(uint16_t type)
		{
			return Get().m_Blocks[type];
		}

		inline static uint32_t GetBlockId(const std::string& name)
		{
			for (uint16_t i = 0; i < Get().m_Blocks.size(); i++)
			{
				if (name == Get().m_Blocks[i].m_Shortname)
				{
					return i;
				}
			}
			return 0;
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

		inline static int GetBlockCount() { return Get().m_Blocks.size(); }
		static inline void AddBlock(Block& block)
		{
			Get().m_Blocks.push_back(block); 
			MC_INFO("Adding Block: {0}", block.m_Longname);
		}
		static inline uint8_t AddTexture(const std::string& filepath)
		{
			return Get().IAddTexture(filepath);
		}

		static inline void InitTextures(const Ref<Shader>& shader)
		{
			Get().IInitTextures(shader);
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

		uint8_t IAddTexture(const std::string& filepath);

	private:
		std::vector<Block> m_Blocks;
		std::vector<Ref<Texture>> m_Textures;
		uint8_t m_CurrentTexture = -1;
		BlockLoader();
	};
}
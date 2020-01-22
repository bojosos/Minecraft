#pragma once

#include "common/types.h"

namespace Minecraft
{
	class Block
	{
	public:
		Block() { }

		virtual inline void GetLeftVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const
		{
			res[i++] = vertex(x, y, z, m_Data.negxU, m_Data.negxV);
			res[i++] = vertex(x, y, z + 1, m_Data.negxU + 1, m_Data.negxV);
			res[i++] = vertex(x, y + 1, z, m_Data.negxU, m_Data.negxV + 1);
			res[i++] = vertex(x, y + 1, z, m_Data.negxU, m_Data.negxV + 1);
			res[i++] = vertex(x, y, z + 1, m_Data.negxU + 1, m_Data.negxV);
			res[i++] = vertex(x, y + 1, z + 1, m_Data.negxU + 1, m_Data.negxV + 1);
		}

		virtual inline void GetRightVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const
		{
			res[i++] = vertex(x + 1, y, z, m_Data.posxU, m_Data.posxV);
			res[i++] = vertex(x + 1, y + 1, z, m_Data.posxU, m_Data.posxV + 1);
			res[i++] = vertex(x + 1, y, z + 1, m_Data.posxU + 1, m_Data.posxV);
			res[i++] = vertex(x + 1, y + 1, z, m_Data.posxU, m_Data.posxV + 1);
			res[i++] = vertex(x + 1, y + 1, z + 1, m_Data.posxU + 1, m_Data.posxV + 1);
			res[i++] = vertex(x + 1, y, z + 1, m_Data.posxU + 1, m_Data.posxV);
		}

		virtual inline void GetTopVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const
		{
			res[i++] = vertex(x, y + 1, z, m_Data.posyU, m_Data.posyV);
			res[i++] = vertex(x, y + 1, z + 1, m_Data.posyU, m_Data.posyV + 1);
			res[i++] = vertex(x + 1, y + 1, z, m_Data.posyU + 1, m_Data.posyV);
			res[i++] = vertex(x + 1, y + 1, z, m_Data.posyU + 1, m_Data.posyV);
			res[i++] = vertex(x, y + 1, z + 1, m_Data.posyU, m_Data.posyV + 1);
			res[i++] = vertex(x + 1, y + 1, z + 1, m_Data.posyU + 1, m_Data.posyV + 1);
		}

		virtual inline void GetBottomVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const
		{
			res[i++] = vertex(x, y, z, m_Data.negyU, m_Data.negyV);
			res[i++] = vertex(x + 1, y, z, m_Data.negyU + 1, m_Data.negyV);
			res[i++] = vertex(x, y, z + 1, m_Data.negyU, m_Data.negyV + 1);
			res[i++] = vertex(x + 1, y, z, m_Data.negyU + 1, m_Data.negyV);
			res[i++] = vertex(x + 1, y, z + 1, m_Data.negyU + 1, m_Data.negyV + 1);
			res[i++] = vertex(x, y, z + 1, m_Data.negyU, m_Data.negyV + 1);
		}

		virtual inline void GetBackVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const
		{
			res[i++] = vertex(x, y, z + 1, m_Data.poszU, m_Data.poszV);
			res[i++] = vertex(x + 1, y, z + 1, m_Data.poszU + 1, m_Data.poszV);
			res[i++] = vertex(x, y + 1, z + 1, m_Data.poszU, m_Data.poszV + 1);
			res[i++] = vertex(x, y + 1, z + 1, m_Data.poszU, m_Data.poszV + 1);
			res[i++] = vertex(x + 1, y, z + 1, m_Data.poszU + 1, m_Data.poszV);
			res[i++] = vertex(x + 1, y + 1, z + 1, m_Data.poszU + 1, m_Data.poszV + 1);
		}

		virtual inline void GetFrontVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const
		{
			res[i++] = vertex(x, y, z, m_Data.negzU, m_Data.negzV);
			res[i++] = vertex(x, y + 1, z, m_Data.negzU, m_Data.negzV + 1);
			res[i++] = vertex(x + 1, y, z, m_Data.negzU + 1, m_Data.negzV);
			res[i++] = vertex(x, y + 1, z, m_Data.negzU, m_Data.negzV + 1);
			res[i++] = vertex(x + 1, y + 1, z, m_Data.negzU + 1, m_Data.negzV + 1);
			res[i++] = vertex(x + 1, y, z, m_Data.negzU + 1, m_Data.negzV);
		}

	public:
		TextureData m_Data = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	};
	
	class GrassBlock : public Block
	{
	public:
		GrassBlock() : Block() 
		{
			m_Data = { 3,0,3,0,2,0,0,0,3,0,3,0 }; 
			//m_Data = { 0,3,0,3,0,2,0,0,0,3,0,3 };
		}
	};
}
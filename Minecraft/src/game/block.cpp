#include "mcpch.h"
#include "block.h"
#include <sol.hpp>

namespace Minecraft
{

	Block::Block(const std::string& shortname, const std::string& longname, const sol::table& sides, bool solid, bool transparent, uint8_t tid) : m_Shortname(shortname), m_Longname(longname), m_Solid(solid), m_Transparent(transparent), m_Data(sides), m_Tid(tid)
	{

	}

	void Block::GetLeftVertexData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const
	{
		res[i++] = Vertex(x, y, z, m_Data.negxU, m_Data.negxV + 1, m_Tid);
		res[i++] = Vertex(x, y, z + 1, m_Data.negxU + 1, m_Data.negxV + 1, m_Tid);
		res[i++] = Vertex(x, y + 1, z, m_Data.negxU, m_Data.negxV, m_Tid);
		res[i++] = Vertex(x, y + 1, z, m_Data.negxU, m_Data.negxV, m_Tid);
		res[i++] = Vertex(x, y, z + 1, m_Data.negxU + 1, m_Data.negxV + 1, m_Tid);
		res[i++] = Vertex(x, y + 1, z + 1, m_Data.negxU + 1, m_Data.negxV, m_Tid);
	}

	void Block::GetRightVertexData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const
	{
		res[i++] = Vertex(x + 1, y, z, m_Data.posxU, m_Data.posxV + 1, m_Tid);
		res[i++] = Vertex(x + 1, y + 1, z, m_Data.posxU, m_Data.posxV, m_Tid);
		res[i++] = Vertex(x + 1, y, z + 1, m_Data.posxU + 1, m_Data.posxV + 1, m_Tid);
		res[i++] = Vertex(x + 1, y + 1, z, m_Data.posxU, m_Data.posxV, m_Tid);
		res[i++] = Vertex(x + 1, y + 1, z + 1, m_Data.posxU + 1, m_Data.posxV, m_Tid);
		res[i++] = Vertex(x + 1, y, z + 1, m_Data.posxU + 1, m_Data.posxV + 1, m_Tid);
	}

	void Block::GetUpVertexData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const
	{
		res[i++] = Vertex(x, y + 1, z, m_Data.posyU, m_Data.posyV, m_Tid);
		res[i++] = Vertex(x, y + 1, z + 1, m_Data.posyU, m_Data.posyV + 1, m_Tid);
		res[i++] = Vertex(x + 1, y + 1, z, m_Data.posyU + 1, m_Data.posyV, m_Tid);
		res[i++] = Vertex(x + 1, y + 1, z, m_Data.posyU + 1, m_Data.posyV, m_Tid);
		res[i++] = Vertex(x, y + 1, z + 1, m_Data.posyU, m_Data.posyV + 1, m_Tid);
		res[i++] = Vertex(x + 1, y + 1, z + 1, m_Data.posyU + 1, m_Data.posyV + 1, m_Tid);
	}

	void Block::GetDownVertexData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const
	{
		res[i++] = Vertex(x, y, z, m_Data.negyU, m_Data.negyV, m_Tid);
		res[i++] = Vertex(x + 1, y, z, m_Data.negyU + 1, m_Data.negyV, m_Tid);
		res[i++] = Vertex(x, y, z + 1, m_Data.negyU, m_Data.negyV + 1, m_Tid);
		res[i++] = Vertex(x + 1, y, z, m_Data.negyU + 1, m_Data.negyV, m_Tid);
		res[i++] = Vertex(x + 1, y, z + 1, m_Data.negyU + 1, m_Data.negyV + 1, m_Tid);
		res[i++] = Vertex(x, y, z + 1, m_Data.negyU, m_Data.negyV + 1, m_Tid);
	}

	void Block::GetBackVertexData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const
	{
		res[i++] = Vertex(x, y, z + 1, m_Data.poszU, m_Data.poszV + 1, m_Tid);
		res[i++] = Vertex(x + 1, y, z + 1, m_Data.poszU + 1, m_Data.poszV + 1, m_Tid);
		res[i++] = Vertex(x, y + 1, z + 1, m_Data.poszU, m_Data.poszV, m_Tid);
		res[i++] = Vertex(x, y + 1, z + 1, m_Data.poszU, m_Data.poszV, m_Tid);
		res[i++] = Vertex(x + 1, y, z + 1, m_Data.poszU + 1, m_Data.poszV + 1, m_Tid);
		res[i++] = Vertex(x + 1, y + 1, z + 1, m_Data.poszU + 1, m_Data.poszV, m_Tid);
	}

	void Block::GetFrontVertexData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const
	{
		res[i++] = Vertex(x, y, z, m_Data.negzU, m_Data.negzV + 1, m_Tid);
		res[i++] = Vertex(x, y + 1, z, m_Data.negzU, m_Data.negzV, m_Tid);
		res[i++] = Vertex(x + 1, y, z, m_Data.negzU + 1, m_Data.negzV + 1, m_Tid);
		res[i++] = Vertex(x, y + 1, z, m_Data.negzU, m_Data.negzV, m_Tid);
		res[i++] = Vertex(x + 1, y + 1, z, m_Data.negzU + 1, m_Data.negzV, m_Tid);
		res[i++] = Vertex(x + 1, y, z, m_Data.negzU + 1, m_Data.negzV + 1, m_Tid);
	}

}
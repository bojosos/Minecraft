#pragma once

#include "common/types.h"

namespace Minecraft
{
	class Block
	{
	public:
		Block(const std::string& shortname, const std::string& longname, bool solid, const sol::table& sides, bool transparent, uint8_t tid);

		void GetFrontVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const;
		void GetBackVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const;
		void GetLeftVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const;
		void GetRightVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const;
		void GetUpVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const;
		void GetDownVertexData(vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const;
	
	public:
		TextureData m_Data;
		uint8_t m_Tid;
		bool m_Transparent;
		bool m_Solid;
		std::string m_Shortname, m_Longname;
	};
}
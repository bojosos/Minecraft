#pragma once

namespace Minecraft
{
	class Block
	{
	public:
		Block(const std::string& shortname, const std::string& longname, const sol::table& sides, bool solid, bool transparent, uint8_t tid);

		void GetFrontVertexData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const;
		void GetBackVertexData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const;
		void GetLeftVertexData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const;
		void GetRightVertexData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const;
		void GetUpVertexData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const;
		void GetDownVertexData(Vertex* res, uint8_t x, uint8_t y, uint8_t z, uint32_t& i) const;
	
		inline bool IsTransparent() const
		{
			return m_Transparent;
		}

		inline uint8_t GetTid() const
		{
			return m_Tid;
		}

		inline bool IsSolid() const
		{
			return m_Solid;
		}

	public:
		std::string m_Shortname, m_Longname;

	private:
		TextureData m_Data;
		uint8_t m_Tid;
		bool m_Transparent;
		bool m_Solid;
	};
}
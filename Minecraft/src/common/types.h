#pragma once

#include "common.h"
#include "engine/lua/sol.hpp"

namespace Minecraft
{
	struct TextureData
	{
		uint8_t negxU, negxV, posxU, posxV, negyU, negyV, posyU, posyV, negzU, negzV, poszU, poszV;

		TextureData(const sol::table& sides)
		{
			negxU = sides[0];
			negxV = sides[1];
			posxU = sides[2];
			posxV = sides[3];
			negyU = sides[4];
			negyV = sides[5];
			posyU = sides[6];
			posyV = sides[7];
			negzU = sides[8];
			negzV = sides[9];
			poszU = sides[10];
			poszV = sides[11];
		}
	};
}
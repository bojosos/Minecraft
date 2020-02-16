#pragma once

#include "common.h"
#include <sol.hpp>

namespace Minecraft
{
	struct TextureData
	{
		uint8_t negxU, negxV, posxU, posxV, negyU, negyV, posyU, posyV, negzU, negzV, poszU, poszV;

		TextureData(const sol::table& sides)
		{
			negxU = sides[1];
			negxV = sides[2];
			posxU = sides[3];
			posxV = sides[4];
			negyU = sides[5];
			negyV = sides[6];
			posyU = sides[7];
			posyV = sides[8];
			negzU = sides[9];
			negzV = sides[10];
			poszU = sides[11];
			poszV = sides[12];
		}
	};
}
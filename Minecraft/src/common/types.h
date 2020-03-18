#pragma once

#include "common.h"
#include <sol.hpp>

namespace Minecraft
{
	struct Vertex {
		uint8_t x, y, z, u, v, tid;

		Vertex() : x(0), y(0), z(0), u(0), v(0), tid(0) { }
		Vertex(uint8_t x, uint8_t y, uint8_t z, uint8_t u, uint8_t v, uint8_t tid) : x(x), y(y), z(z), u(u), v(v), tid(tid) { }
	};

	struct Rectangle
	{
		float X, Y, Width, Height;
		Rectangle() : X(0), Y(0), Width(0), Height(0) { }
		Rectangle(float x, float y) : X(x), Y(y), Width(0), Height(0) { }
		Rectangle(float x, float y, float width, float height) : X(x), Y(y), Width(width), Height(height) { }
	};

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
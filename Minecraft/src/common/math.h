#pragma once

namespace Minecraft
{
	class Math
	{
	public:
		static float Intbound(float s, float ds);
		static int Signum(float x);
		static float Mod(int value, int modulus);

	};
}
#pragma once

namespace Minecraft
{
	class Math
	{
	public:
		static float Intbound(float s, float ds);
		static float Signum(float x);
		static float Mod(float value, int modulus);

	};
}
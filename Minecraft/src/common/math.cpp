#include "mcpch.h"
#include "math.h"

namespace Minecraft
{
	float Math::Intbound(float s, float ds)
	{
		if (ds < 0)
		{
			return Intbound(-s, -ds);
		}
		else
		{
			s = Mod(s, 1);
			return(1 - s) / ds;
		}
	}

	int Math::Signum(float x)
	{
		return x > 0 ? 1 : x < 0 ? -1 : 0;
	}

	float Math::Mod(float value, int modulus)
	{
		return fmod((float)fmod(value, modulus) + modulus, modulus);
	}
}
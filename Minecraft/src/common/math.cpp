#include "mcpch.h"
#include "math.h"

namespace Minecraft
{
	float Math::Intbound(float s, float ds)
	{
		if (ds < 0.0f)
		{
			return Intbound(-s, -ds);
		}
		else
		{
			s = Mod(s, 1.0f);
			return(1.0f - s) / (float)ds;
		}
	}

	float Math::Signum(float x)
	{
		return x > 0.0f ? 1.0f : x < 0.0f ? -1.0f : 0.0f;
	}

	float Math::Mod(float value, int modulus)
	{
		return (float)fmod((float)fmod(value, modulus) + modulus, modulus);
	}
}
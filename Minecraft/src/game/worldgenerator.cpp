#include "mcpch.h"
#include "generator.h"
#include "game/chunk.h"

namespace Minecraft
{

	WorldGenerator::WorldGenerator() 
	{
	
	}

	void WorldGenerator::CreateChunkHeightMap(const NoiseOptions& firstNoise, const NoiseOptions& secondNoise, int32_t xc, int32_t zc, int* res)
	{
		xc *= CHUNK_SIZE;
		zc *= CHUNK_SIZE;

		for (int x = 0; x < CHUNK_SIZE; x++)
		{
			int xx = x * CHUNK_SIZE;
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				float noise1 = Noise::Noise2D(firstNoise, (float)x + xc, (float)z + zc);
				float noise2 = Noise::Noise2D(secondNoise, (float)x + xc, (float)z + zc);
				glm::vec2 coord = (glm::vec2(xc + x, zc + z) - 160.0f / 2.0f) / 160.0f * 2.0f;
				float island = (Noise::Round(coord)) * 1.25;
				float result = noise1 * noise2;
				res[xx + z] = (result * firstNoise.Amplitude + firstNoise.Offset) * island - 5;
			}
		}
	}

}
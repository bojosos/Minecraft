#pragma once
#include "common/noise.h"

namespace Minecraft
{
	class Chunk;

	class TerrainGenerator
	{
	public:
		virtual inline void SetOptions(const NoiseOptions& ops) {
			m_Options = ops;
		}

		virtual void CreateChunkHeightMap(const NoiseOptions& firstNoise, const NoiseOptions& secondNoise,int32_t x, int32_t z, int* res) = 0;

	protected:
		TerrainGenerator() { }
		
		NoiseOptions m_Options;
	};

	class WorldGenerator : public TerrainGenerator
	{
	public:
		WorldGenerator();
		virtual void CreateChunkHeightMap(const NoiseOptions& firstNoise, const NoiseOptions& secondNoise, int32_t x, int32_t z, int* res) override;
	};
}
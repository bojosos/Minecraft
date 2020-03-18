#pragma once

namespace Minecraft
{

	// ------------- PATHS -------------
#ifdef MC_WEB
	#define DIRECTORY_PREFIX "Minecraft/res/"
#else
	#define DIRECTORY_PREFIX "res/"
#endif

#define DEFAULT_FONT_PATH "fonts/roboto-thin.ttf"

	// ------------- BATCH RENDERER -------------
#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX		1
#define SHADER_TID_INDEX	2
#define SHADER_COLOR_INDEX	3

	// ------------- PLAYER -------------
#define PLAYER_REACH 4

	// ------------- WORLD -------------
#define WATER_LEVEL 20
#define WORLD_SIZE 3
#define CHUNK_SIZE 16
#define TOTAL_VERTICES CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 36

}
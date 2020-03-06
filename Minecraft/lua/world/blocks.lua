-- game.blocks
--			  .AddTexutre(filepath) - Loads a texture file and returns the id of the loaded texture, to be used when adding new blocks
--			  .AddBlock({shortname(mostly not seen in gameplay), longname(in inventory), solid(can walk through), transparent(does it have trasparency? e.g. leaves, glass), tid(it has to be the id of the loaded texture)} - Adds a new block with the given parameters, all params are required

local btex1 = game.blocks.AddTexture("res/textures/blocks.jpg")
local btex = game.blocks.AddTexture("res/textures/blocks.jpg")

game.blocks.AddBlock({
	shortname = "air",
	longname = "Air",
	solid = false,
	transparent = true,
	sides = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	tid = btex,
})

game.blocks.AddBlock({
	shortname = "grass",
	longname = "Grass Block",
	solid = true,
	transparent =  false,
	sides = { 3, 0, 3, 0, 2, 0, 0, 0, 3, 0, 3, 0 },
	tid = btex,
})

game.blocks.AddBlock({
	shortname = "cobblestone",
	longname = "Cobblestone Block",
	solid = true,
	transparent = false,
	sides = { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 },
	tid = btex,
})

game.blocks.AddBlock({
	shortname = "stone",
	longname = "Stone Block",
	solid = true,
	transparent = false,
	sides = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	tid = btex,
})
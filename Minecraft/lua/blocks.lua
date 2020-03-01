--Texture(path) selects the texture to use for this section of blocks--
--Block(string short name(commands, singleword), string long name(inventory), bool solid, array {sides}(texture coords for each of the sides), bool transparent)

---Texture("res/textures/blocks.jpg")
---Block("air", "Air", false, { 3, 0, 3, 0, 2, 0, 0, 0, 3, 0, 3, 0 }, true)
---Block("grass", "Grass Block", true, { 3, 0, 3, 0, 2, 0, 0, 0, 3, 0, 3, 0 }, false)
---Block("stone", "Stone Block", true, { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, false)
---Block("cobblestone", "Cobblestone Block", true, { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 }, false)
---Block("oaklog", "Oak Log", true, { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 }, false)

local btex = game.blocks.AddTexture("res/textures/blocks.jpg")
local test1 = game.blocks.AddTexture("res/textures/blocks.jpg")
local test2 = game.blocks.AddTexture("res/textures/blocks.jpg")

game.blocks.AddBlock({
	shortname = "air",
	longname = "Air",
	solid = false,
	transparent = true,
	sides = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	tid = test1,
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
	tid = test2,
})

game.blocks.AddBlock({
	shortname = "stone",
	longname = "Stone Block",
	solid = true,
	transparent = false,
	sides = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 },
	tid = test1,
})
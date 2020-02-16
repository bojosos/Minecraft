--Texture(path) selects the texture to use for this Block--
--Block(string short name(commands, singleword), string long name(inventory), bool solid, array {sides}(texture coords for each of the sides), bool transparent)
Texture("res/textures/blocks.jpg")
Block("air", "Air", false, { 3, 0, 3, 0, 2, 0, 0, 0, 3, 0, 3, 0 }, true)
Block("grass", "Grass Block", true, { 3, 0, 3, 0, 2, 0, 0, 0, 3, 0, 3, 0 }, false)
Block("stone", "Stone Block", true, { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0}, false)
Block("cobblestone", "Cobblestone Block", true, { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 }, false)
Block("oaklog", "Oak Log", true, { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 }, false)
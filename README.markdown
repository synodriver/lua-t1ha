# lua-t1ha
```lua
local t1ha = require("t1ha")
local seed_x = 0
local seed_y = 1
print(t1ha.hash("dadadaad", seed_x))
print(t1ha.hash("dadadaad", seed_x))
print(t1ha.hash("dadadaa2d", seed_x))
print(t1ha.hash("dadadaa2d", seed_x))
print(t1ha.hash("dadadaa2d", seed_y))
print(t1ha.hash128("dadadaa2d", seed_x))
print(t1ha.hash128("dadadaa2d", seed_x))
print(t1ha.hash128("dadadaa2d", seed_y))
print(t1ha.hash128("dadadaa2d", seed_y))

local hasher = t1ha.newhasher(seed_x,seed_y)
hasher:update("assddd")
print(hasher:final())
local hasher2 = t1ha.newhasher(seed_x,seed_y)
hasher2:update("assddd")
print(hasher2:final())
```
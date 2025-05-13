-- Map generation script
-- util/mapgen.h uses this script to generate the maps
-- 2025 DJaySky

local log = Engine.log
local log_path = log.get_path()

-- Takes a space with a width and height, then
-- splits it into two smaller spaces, randomly
-- choosing a direction to split in (horizontal
-- or vertical).
local function split(node)
	local rand = math.random()
	local dir = math.random()

	-- clamp rand
	if rand < .3 then rand = .3 end
	if rand > .7 then rand = .7 end

	-- vertical
	if dir > .5 then
		local col = math.floor(rand * node.w)

		node.a = {
			w = col,
			h = node.h
		}

		node.b = {
			w = node.w - col,
			h = node.h
		}
	-- horizontal
	else
		local row = math.floor(rand * node.h)

		node.a = {
			w = node.w,
			h = row
		}

		node.b = {
			w = node.w,
			h = node.h - row
		}
	end
end

-- Generates the entire dungeon using
-- Binary Space Partitioning.
local function gen_level()
	log.pwrite(log_path, "[Lua] [Map] Generating Layer 1 with size ("..map_w..","..map_h..")\n")

	local out = {}

	for y = 1, map_h do
		out[y] = {}
		for x = 1, map_w do
			if(
				x == 1 or
				x == map_w or
				y == 1 or
				y == map_h
			) then
				out[y][x] = 1
			else
				out[y][x] = 0
			end
		end
	end

	local root = {
		w = map_w,
		h = map_h
	}

	split(root)

	return out
end

return gen_level()

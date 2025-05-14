-- Map generation script
-- util/mapgen.h uses this script to generate the maps
-- 2025 DJaySky

local log = Engine.log
local log_path = log.get_path()

local rooms = {}
local tunnels = {}

-- Takes a space with a width and height, then recursively 
-- splits it into two smaller spaces, randomly choosing a
-- direction to split in (horizontal or vertical).
local function split(node)
	local rand = math.random()
	local dir = math.random()

	local min_w = 6
	local min_h = 6

	-- clamp rand
	if rand < .3 then rand = .3 end
	if rand > .7 then rand = .7 end

	-- vertical
	if dir > .5 then
		local col = math.floor(rand * node.w)

		node.a = {
			x = node.x,
			y = node.y,
			w = col,
			h = node.h
		}

		node.b = {
			x = node.x + col,
			y = node.y,
			w = node.w - col,
			h = node.h
		}

		if node.a.w > min_w and node.a.h > min_h then
			split(node.a)
		end

		if node.b.w > min_w and node.a.h > min_h then
			split(node.b)
		end
	-- horizontal
	else
		local row = math.floor(rand * node.h)

		node.a = {
			x = node.x,
			y = node.y,
			w = node.w,
			h = row
		}

		node.b = {
			x = node.x,
			y = node.y + row,
			w = node.w,
			h = node.h - row
		}

		if node.a.w > min_w and node.a.h > min_h then
			split(node.a)
		end

		if node.b.w > min_w and node.a.h > min_h then
			split(node.b)
		end
	end
end

-- Loops through a BSP tree, recursively creating
-- rooms based on leaf nodes. Modifies the
-- `rooms` table.
local function create_rooms(node)
	local gen_rooms = true

	if node.a then
		create_rooms(node.a)
		gen_rooms = false
	end

	if node.b then
		create_rooms(node.b)
		gen_rooms = false
	end
	
	if gen_rooms then
		-- generate the room based on node
		local rand = math.random()

		if rand < .5 then rand = .5 end

		local room = {}

		room.w = math.floor(node.w * rand)
		room.h = math.floor(node.h * rand)

		room.x = math.random(node.x, node.x + node.w - room.w)
		room.y = math.random(node.y, node.y + node.h - room.h)

		room.center_x = math.floor(room.w/2)
		room.center_y = math.floor(room.h/2)

		table.insert(rooms, room)
	end
end

-- Loops through the `rooms` table, creating
-- tunnels connecting each room to the
-- previous room in the table.
local function create_tunnels()
end

-- Generates the entire dungeon using Binary Space 
-- Partitioning.
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
		x = 0,
		y = 0,
		w = map_w,
		h = map_h
	}

	log.pwrite(log_path, "[Lua] [Map] Creating binary splits\n")
	split(root)

	log.pwrite(log_path, "[Lua] [Map] Creating rooms\n")
	create_rooms(root)

	log.pwrite(log_path, "[Lua] [Map] Creating tunnels")
	create_tunnels()
	
	log.pwrite(log_path, "[Lua] [Map] Inserting rooms into map\n")
	for _, room in ipairs(rooms) do
		for x = room.x, room.x + room.w do
			out[room.y+1][x] = 1
			out[room.y+room.h][x] = 1
		end

		for y = room.y+1, room.y + room.h do
			out[y][room.x+1] = 1
			out[y][room.x+room.w] = 1
		end
	end

	log.pwrite(log_path, "[Lua] [Map] Inserting tunnels into map\n")
	-- loop through `tunnels` and place tiles in `out`
	-- make sure to create openings in the existing rooms

	return out
end

return gen_level()

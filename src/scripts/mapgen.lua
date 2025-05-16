-- Map generation script
-- util/mapgen.h uses this script to generate the maps
-- 2025 DJaySky

local log = Engine.log
local log_path = log.get_path()

local rooms = {}

-- Takes a space with a width and height, then recursively 
-- splits it into two smaller spaces, randomly choosing a
-- direction to split in (horizontal or vertical).
local function split(node)
	local rand = math.random()
	local dir = math.random()

	local min_w = 10
	local min_h = 10

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

		if rand < .6 then rand = .6 end

		local room = {}

		room.w = math.floor(node.w * rand)
		room.h = math.floor(node.h * rand)

		room.x = math.random(node.x, node.x + node.w - room.w)
		room.y = math.random(node.y, node.y + node.h - room.h)

		room.center_x = room.x + math.floor(room.w/2)
		room.center_y = room.y + math.floor(room.h/2)

		node.room = room
		table.insert(rooms, room)
	end
end

-- Loops through the BSP tree, connecting each
-- sister node to each other with a tunnel,
-- storing each tunnel in the `tunnels` table.
local function create_tunnels(node, map)
	if node.a and node.b and node.a.room and node.b.room then
		-- connect node.a and node.b based on their centers
		local x1, y1 = node.a.room.center_x, node.a.room.center_y
		local x2, y2 = node.b.room.center_x, node.b.room.center_y

		local tunnel = {}

		if math.random() < .5 then
			for x = math.min(x1, x2), math.max(x1, x2) do
				map[y1][x] = 0
			end

			for y = math.min(y1, y2), math.max(y1, y2) do
				map[y][x2] = 0
			end
		else
			for y = math.min(y1, y2), math.max(y1, y2) do
				map[y][x1] = 0
			end

			for x = math.min(x1, x2), math.max(x1, x2) do
				map[y2][x] = 0
			end
		end
	else
		create_tunnels(node.a, map)
	end
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

	log.pwrite(log_path, "[Lua] [Map] Creating and inserting tunnels")
	create_tunnels(root, out)
	
	log.pwrite(log_path, "[Lua] [Map] Inserting rooms into map\n")
	-- change this to fill the empty spaces with 0s
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

	-- set player position to spawn in the last room
	local room_x = rooms[#rooms].center_x
	local room_y = rooms[#rooms].center_y
	Engine.player.set_x(room_x)
	Engine.player.set_y(room_y)

	return out
end

return gen_level()

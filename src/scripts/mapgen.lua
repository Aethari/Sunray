-- Map generation script
-- util/mapgen.h uses this script to generate the maps
-- 2025 Aethari

local log = Engine.log
local log_path = log.get_path()

local rooms = {}

-- Takes a space with a width and height, then recursively 
-- splits it into two smaller spaces, randomly choosing a
-- direction to split in (horizontal or vertical).
local function split(node)
	local rand = math.random()
	local dir = math.random()

	local min_w = 8
	local min_h = 8

	-- clamp rand
	if rand < .3 then rand = .3 end
	if rand > .7 then rand = .7 end

	-- vertical
	if dir > .5 then
		local col = math.floor(rand * node.w)
		if col < min_w then col = min_w end
		if node.w - col < min_w then col = node.w - min_w end

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

		if node.b.w > min_w and node.b.h > min_h then
			split(node.b)
		end
	-- horizontal
	else
		local row = math.floor(rand * node.h)
		if row < min_h then row = min_h end
		if node.h - row < min_h then col = node.h - min_h end

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

		if node.b.w > min_w and node.b.h > min_h then
			split(node.b)
		end
	end
end

-- Loops through a BSP tree, recursively creating
-- rooms based on leaf nodes. Modifies the
-- `rooms` table.
local function create_rooms(node)
	local gen_rooms = true

	-- if statements check for leaf nodes
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

		if rand < .4 then rand = .4 end
		if rand > .6 then rand = .6 end

		local room = {}

		room.w = math.floor(node.w * rand)
		room.h = math.floor(node.h * rand)
		
		-- fit room in node - -2 is to make sure the room 
		-- isn't as large as node
		if room.w > node.w-2 then room.w = node.w-2 end
		if room.h > node.h-2 then room.h = node.h-2 end

		if room.w < 3 then room.w = 3 end
		if room.h < 3 then room.w = 3 end

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
	if not node then return end

	if node.a and node.b and node.a.room and node.b.room then
		-- connect node.a and node.b based on their centers
		local x1, y1 = node.a.room.center_x, node.a.room.center_y
		local x2, y2 = node.b.room.center_x, node.b.room.center_y

		-- for the drawing loops of the second tunnels, we
		-- need a way to 

		-- horizontal then vertical
		if math.random() < .5 then
			for x = math.min(x1, x2), math.max(x1, x2) do
				if x < map_w-1 and x > 0 then map[y1][x] = 0 end
			end

			for y = math.min(y1, y2), math.max(y1, y2) do
				if y < map_h-1 and y > 0 then map[y][x2] = 0 end
			end
		-- vertical then horizontal
		else
			for y = math.min(y1, y2), math.max(y1, y2) do
				if y < map_h-1 and y > 0 then map[y][x1] = 0 end
			end

			for x = math.min(x1, x2), math.max(x1, x2) do
				if x < map_w-1 and x > 0 then map[y2][x] = 0 end
			end
		end
	end
	
	if node.a then create_tunnels(node.a, map) end
	if node.b then create_tunnels(node.b, map) end
end

-- Generates the entire dungeon using Binary Space 
-- Partitioning.
local function gen_level()
	log.pwrite(log_path, "[Lua] [Map] Generating Layer 1 with size ("..map_w..","..map_h..")\n")
	local out = {}
	rooms = {}

	for y = 1, map_h do
		out[y] = {}
		for x = 1, map_w do
			out[y][x] = 1
		end
	end

	local root = {
		x = 1,
		y = 1,
		w = map_w,
		h = map_h
	}

	log.pwrite(log_path, "[Lua] [Map] Creating binary splits\n")
	split(root)

	log.pwrite(log_path, "[Lua] [Map] Creating rooms\n")
	create_rooms(root)

	log.pwrite(log_path, "[Lua] [Map] Inserting rooms into map\n")
	-- change this to fill the empty spaces with 0s
	for _, room in ipairs(rooms) do	
		for y = room.y, room.y + room.h do
			for x = room.x, room.x + room.w do
				if 
					x < map_w-1 and
					x > 0 and
					y < map_h-1 and
					y > 0
				then
					out[y][x] = 0
				end
			end
		end
	end

	log.pwrite(log_path, "[Lua] [Map] Creating and inserting tunnels\n")
	create_tunnels(root, out)

	local room_x = rooms[#rooms].center_x
	local room_y = rooms[#rooms].center_y

	log.pwrite(log_path, "[Lua] [Map] Setting player spawn to ("..room_x..","..room_y..")\n")
	Engine.player.set_x(room_x)
	Engine.player.set_y(room_y)

	return out
end

return gen_level()

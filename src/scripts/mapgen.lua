-- Map generation script
-- util/mapgen.h uses this script to generate the maps
-- 2025 Aethari

local log = Engine.log
local log_path = log.get_path()

-- == Tunnel Generation ========================================
local function gen_tunnel_up(map, x, y)
	local dist = math.random(5, 10)
	if y - dist > 1 then
		local y2 = y - dist
		for i = y, y2 do map[i][x] = 0 end
		return y2
	else
		return nil
	end
end

local function gen_tunnel_down(map, x, y)
	local dist = math.random(5, 10)
	if y + dist < map_h then
		local y2 = y + dist
		for i = y, y2 do map[i][x] = 0 end
		return y2
	else
		return nil
	end
end

local function gen_tunnel_left(map, x, y)
	local dist = math.random(5, 10)
	if x - dist > 1 then
		local x2 = x - dist
		for i = x, x2 do map[y][i] = 0 end
		return x2
	else
		return nil
	end
end

local function gen_tunnel_right(map, x, y)
	local dist = math.random(5, 10)
	if x + dist < map_w then
		local x2 = x + dist
		for i = x, x2 do map[y][i] = 0 end
		return x2
	else
		return nil
	end
end

-- == "Main" Generation ========================================

-- Generates either a room or a tunnel, starting from 
-- one position and moving to a new, randomly generated
-- one.
--
-- Parameters:
-- * map - The map to carve spaces into
-- * x,y - The point to start at
-- * last_dir - The direction that the previous tunnel was generated in
local function gen_space(map, x, y, last_dir)
	if x == 2 and y == 2 then
		local dir = math.random()

		if dir < .5 then
			local x2 = gen_tunnel_right(map, x, y)
			Engine.player.set_angle(0)
			gen_space(map, x2, y, "right")
		else
			local y2 = gen_tunnel_down(map, x, y)
			Engine.player.set_angle(-4.71239)
			gen_space(map, x, y2, "down")
		end
	else
		local dir = math.random()
	
		-- random chance to generate room or tunnel
		local is_room = math.random()
		room = 1

		if dir < .25 then
			-- up
			if is_room > .6 then
				if last_dir ~= "up" then
					local y2 = gen_tunnel_up(map, x, y)
					if y2 then
						-- generate something with y2
					else
						gen_space(map, x, y, "up")
					end
				else
					gen_space(map, x, y, last_dir)
				end
			else
				-- generate room
				local room = {}

				room.w = math.random(3, 5)
				room.h = math.random(3, 5)
			end
		elseif dir < .5 then
			-- down
			if is_room > .6 then
				if last_dir ~= "down" then
					local y2 = gen_tunnel_down(map, x, y)
					if y2 then
						-- generate something with y2
					else
						gen_space(map, x, y, "down")
					end
				else
					gen_space(map, x, y, last_dir)
				end
			else
				-- generate room
			end
		elseif dir < .75 and last_dir ~= "left" then
			-- left
			if is_room > .6 then
				if last_dir ~= "left" then
					local x2 = gen_tunnel_left(map, x, y)
					if x2 then
						-- generate something with x2
					else
						gen_space(map, x, y, "left")
					end
				else
					gen_space(map, x, y, last_dir)
				end
			else
				-- generate room
			end
		elseif dir < 1 then
			-- right
			if is_room > .6 then
				if last_dir ~= "right" then
					local x2 = gen_tunnel_right(map, x, y)
					if x2 then
						-- generate something with x2
					else
						gen_space(map, x, y, "right")
					end
				else
					gen_space(map, x, y, last_dir)
				end
			else
				-- generate room
			end
		end
	end
end

local function gen_level()
	log.pwrite(log_path, "[Lua] [Map] Generating Layer 1 with size ("..map_w..","..map_h..")\n")
	local out = {}

	for y = 1, map_h do
		out[y] = {}
		for x = 1, map_w do
			out[y][x] = 1
		end
	end

	log.pwrite(log_path, "[Lua] [Map] Creating tunnels/rooms\n")
	gen_space(out, 2, 2)

	log.pwrite(log_path, "[Lua] [Core] Setting player spawn\n")
	Engine.player.set_x(1.5)
	Engine.player.set_y(1.5)

	return out
end

return gen_level()

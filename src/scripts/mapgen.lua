-- Map generation script
-- util/mapgen.h uses this script to generate the maps
-- 2025 Aethari

local log = Engine.log
local log_path = log.get_path()

-- == Tunnel Generation ========================================
local function gen_tunnel_up(map, x, y)
	local dist = math.random(5, 15)
end

local function gen_tunnel_down(map, x, y)
	local dist = math.random(5, 15)
	if y + dist < map_h then
		local y2 = y + dist
		for i = y, y2 do map[i][x] = 0 end
		return y2
	else
		return false
	end
end

local function gen_tunnel_left(map, x, y)
	local dist = math.random(5, 15)
end

local function gen_tunnel_right(map, x, y)
	local dist = math.random(5, 15)
	if x + dist < map_w then
		local x2 = x + dist
		for i = x, x2 do map[y][i] = 0 end
		return x2
	else
		return false
	end
end

-- == "Main" Generation ========================================

-- Generates either a room or a tunnel, starting from 
-- one position and moving to a new, randomly generated
-- one.
local function gen_space(map, x, y)
	if x == 2 and y == 2 then
		local dir = math.random()
		
		if dir < .5 then
			local x2 = gen_tunnel_right(map, x, y)
			Engine.player.set_angle(0)
			gen_space(map, x2, y)
		else
			local y2 = gen_tunnel_down(map, x, y)
			Engine.player.set_angle(-4.71239)
			gen_space(map, x, y2)			
		end
	else
		local dir = math.random()
	
		-- random chance to generate room or tunnel
		local room = math.random()

		if dir < .25 then
			-- up
			if room > .5 then
				local y2 = gen_tunnel_up(map, x, y)
				if y2 then
					-- generate something with y2
				else
					gen_space(map, x, y)
				end
			else
				-- generate room
			end
		elseif dir < .5 then
			-- down
			if room > .5 then
				local y2 = gen_tunnel_down(map, x, y)
				if y2 then
					-- generate something with y2
				else
					gen_space(map, x, y)
				end
			else
				-- generate room
			end
		elseif dir < .75 then
			-- left
			if room > .5 then
				local x2 = generate_tunnel_left(map, x, y)
				if x2 then
					-- generate something with x2
				else
					gen_space(map, x, y)
				end
			else
				-- generate room
			end
		elseif dir < 1 then
			-- right
			if room > .5 then
				local x2 = generate_tunnel_right(map, x, y)
				if x2 then
					-- generate something with x2
				else
					gen_space(map, x, y)
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

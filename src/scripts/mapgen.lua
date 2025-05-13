-- Map generation script
-- util/mapgen.h uses this script to generate the maps
-- 2025 DJaySky

local log = Engine.log
local log_path = log.get_path()

local function gen_Layer_1()
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

	return out
end

local function gen_Layer_2()
	log.pwrite(log_path, "[Lua] [Map] Generating Layer 2 with size ("..map_w..","..map_h..")\n")		
end

local function gen_Layer_3()
	log.pwrite(log_path, "[Lua] [Map] Generating Layer 3 with size ("..map_w..","..map_h..")\n")		
end

local function gen_Layer_4()
	log.pwrite(log_path, "[Lua] [Map] Generating Layer 4 with size ("..map_w..","..map_h..")\n")
end

if layer == 1 then
	return gen_layer_1()
elseif layer == 2 then
	return gen_layer_2()
elseif layer == 3 then
	return gen_layer_3()
elseif layer == 4 then
	return gen_layer_4()
end

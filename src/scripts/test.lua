-- Engine.log tests
local log = Engine.log
local log_path = log.get_path()

log.pwrite(log_path, "[Lua] [Core] Hello from Lua!\n")
log.write(log_path, "[Lua] [Core] This should not show up in the terminal\n")

-- Engine.map tests
local map = Engine.map
log.pwrite(log_path, "[Lua] [Map] Getting map tile at (1, 0): "..map.get(1, 0).."\n")

map.set(2, 3, 1)

local col = tostring(map.check(1,0))
log.pwrite(log_path, "[Lua] [Map] Checking map tile collision at (1, 0): "..col.."\n")

col = tostring(map.check_dir(1, 1, 0, -1))
log.pwrite(log_path, "[Lua] [Map] Checking map tile collision at (1, 0) in dir (0, -1): "..col.."\n")

-- Engine.player tests
local player = Engine.player

local x = player.get_x()
local y = player.get_y()
local speed = player.get_speed()
local turnspeed = player.get_turnspeed()
local angle = player.get_angle()
local fov = player.get_fov()

log.pwrite(log_path, "[Lua] [Core] Engine.player.x: "..x.."\n")
log.pwrite(log_path, "[Lua] [Core] Engine.player.y: "..y.."\n")
log.pwrite(log_path, "[Lua] [Core] Engine.player.speed: "..speed.."\n")
log.pwrite(log_path, "[Lua] [Core] Engine.player.turnspeed: "..turnspeed.."\n")
log.pwrite(log_path, "[Lua] [Core] Engine.player.angle: "..angle.."\n")
log.pwrite(log_path, "[Lua] [Core] Engine.player.fov: "..fov.."\n")

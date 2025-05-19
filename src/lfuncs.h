/*
 * Bindings from engine functions to lua_CFunctions
 * 2025 Aethari
 */

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#ifndef LFUNCS_H
#define LFUNCS_H

// logger funcs
int l_log_get_path(lua_State *L);
int l_log_clear(lua_State *L);
int l_log_write(lua_State *L);
int l_log_pwrite(lua_State *L);

// map funcs
int l_map_get(lua_State *L);
int l_map_set(lua_State *L);
int l_map_check_pos(lua_State *L);
int l_map_check_dir(lua_State *L);

// player funcs
int l_player_get_x(lua_State *L);
int l_player_get_y(lua_State *L);
int l_player_get_speed(lua_State *L);
int l_player_get_turnspeed(lua_State *L);
int l_player_get_angle(lua_State *L);
int l_player_get_fov(lua_State *L);
int l_player_set_x(lua_State *L);
int l_player_set_y(lua_State *L);
int l_player_set_speed(lua_State *L);
int l_player_set_turnspeed(lua_State *L);
int l_player_set_angle(lua_State *L);
int l_player_set_fov(lua_State *L);

#endif

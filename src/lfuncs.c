/*
 * Bindings from engine functions to lua_CFunctions
 * See lfuncs.h for documentation
 * 2025 DJaySky
 */

#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

// log
#include "util/log.h"
int l_log_get_path(lua_State *L) {
	char *log_path = log_get_path();
	lua_pushstring(L, log_path);
	free(log_path);
	return 1;
}

int l_log_clear(lua_State *L) {
	const char *path = luaL_checkstring(L, 1);
	char *mod_path = strdup(path);

	log_clear(mod_path);

	free(mod_path);
	return 0;
}

int l_log_write(lua_State *L) {
	const char *path = luaL_checkstring(L, 1);
	char *mod_path = strdup(path);

	const char *msg = luaL_checkstring(L, 2);
	char *mod_msg = strdup(msg);

	log_write(mod_path, mod_msg);

	free(mod_path);
	free(mod_msg);

	return 0;
}

int l_log_pwrite(lua_State *L) {
	const char *path = luaL_checkstring(L, 1);
	char *mod_path = strdup(path);

	const char *msg = luaL_checkstring(L, 2);
	char *mod_msg = strdup(msg);

	log_pwrite(mod_path, mod_msg);

	free(mod_path);
	free(mod_msg);

	return 0;
}

// map
#include "util/map.h"
int l_map_get(lua_State *L) {
	int x = luaL_checknumber(L, 1);
	int y = luaL_checknumber(L, 2);

	int tile = map_get(x, y);
	lua_pushnumber(L, tile);

	return 1;
}

int l_map_set(lua_State *L) {
	int value = luaL_checknumber(L, 1);
	int x = luaL_checknumber(L, 2);
	int y = luaL_checknumber(L, 3);

	map_set(value, x, y);
	
	return 0;
}

int l_map_check_pos(lua_State *L) {
	int x = luaL_checknumber(L, 1);
	int y = luaL_checknumber(L, 2);

	bool col = map_check_pos(x, y);
	lua_pushboolean(L, col);

	return 1;
}

int l_map_check_dir(lua_State *L) {
	int x = luaL_checknumber(L, 1);
	int y = luaL_checknumber(L, 2);
	float dx = luaL_checknumber(L, 3);
	float dy = luaL_checknumber(L, 4);

	bool col = map_check_dir(x, y, dx, dy);
	lua_pushboolean(L, col);

	return 1;
}

// player
#include "player.h"
int l_player_get_x(lua_State *L) {
	float x = player_get_pos_x();
	lua_pushnumber(L, x);
	return 1;
}

int l_player_get_y(lua_State *L) {
	float y = player_get_pos_y();
	lua_pushnumber(L, y);
	return 1;
}

int l_player_get_speed(lua_State *L) {
	float speed = player_get_speed();
	lua_pushnumber(L, speed);
	return 1;
}

int l_player_get_turnspeed(lua_State *L) {
	float turnspeed = player_get_turnspeed();
	lua_pushnumber(L, turnspeed);
	return 1;
}

int l_player_get_angle(lua_State *L) {
	float angle = player_get_angle();
	lua_pushnumber(L, angle);
	return 1;
}

int l_player_get_fov(lua_State *L) {
	float fov = player_get_fov();
	lua_pushnumber(L, fov);
	return 1;
}

int l_player_set_x(lua_State *L) {
	float new_x = luaL_checknumber(L, 1);
	player_set_pos_x(new_x);
	return 0;
}

int l_player_set_y(lua_State *L) {
	float new_y = luaL_checknumber(L, 1);
	player_set_pos_y(new_y);
	return 0;
}

int l_player_set_speed(lua_State *L) {
	float new_speed = luaL_checknumber(L, 1);
	player_set_speed(new_speed);
	return 0;
}

int l_player_set_turnspeed(lua_State *L) {
	float new_turnspeed = luaL_checknumber(L, 1);
	player_set_turnspeed(new_turnspeed);
	return 0;
}

int l_player_set_angle(lua_State *L) {
	float new_angle = luaL_checknumber(L, 1);
	player_set_angle(new_angle);
	return 0;
}

int l_player_set_fov(lua_State *L) {
	float new_fov = luaL_checknumber(L, 1);
	player_set_fov(new_fov);
	return 0;
}

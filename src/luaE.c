/*
 * A custom Lua scripting interface built on Lua's C API
 * Provides helper functions and easy access to the Lua state
 * See luaE.h for documentation
 * 2025 Aethari
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "util/log.h"
#include "lfuncs.h"

lua_State *luaE_new() {
	char *log_path = log_get_path();

	log_pwrite(log_path, "[ C ] [Script] Creating new Lua state\n");

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	// Engine
	lua_newtable(L);

	// Engine.log
	lua_pushstring(L, "log");
	lua_newtable(L);

	// log.get_path()
	lua_pushstring(L, "get_path");
	lua_pushcfunction(L, l_log_get_path);
	lua_settable(L, -3);

	// log.clear()
	lua_pushstring(L, "clear");
	lua_pushcfunction(L, l_log_clear);
	lua_settable(L, -3);

	// log.write()
	lua_pushstring(L, "write");
	lua_pushcfunction(L, l_log_write);
	lua_settable(L, -3);

	// log.pwrite()
	lua_pushstring(L, "pwrite");
	lua_pushcfunction(L, l_log_pwrite);
	lua_settable(L, -3);

	lua_settable(L, -3);

	// Engine.map
	lua_pushstring(L, "map");
	lua_newtable(L);

	// map.get()
	lua_pushstring(L, "get");
	lua_pushcfunction(L, l_map_get);
	lua_settable(L, -3);

	// map.set()
	lua_pushstring(L, "set");
	lua_pushcfunction(L, l_map_set);
	lua_settable(L, -3);

	// map.check()
	lua_pushstring(L, "check");
	lua_pushcfunction(L, l_map_check_pos);
	lua_settable(L, -3);

	// map.check_dir()
	lua_pushstring(L, "check_dir");
	lua_pushcfunction(L, l_map_check_dir);
	lua_settable(L, -3);

	lua_settable(L, -3);

	// Engine.player
	lua_pushstring(L, "player");
	lua_newtable(L);

	// player.get_x()
	lua_pushstring(L, "get_x");
	lua_pushcfunction(L, l_player_get_x);
	lua_settable(L, -3);

	// player.get_y()
	lua_pushstring(L, "get_y");
	lua_pushcfunction(L, l_player_get_y);
	lua_settable(L, -3);

	// player.get_speed()
	lua_pushstring(L, "get_speed");
	lua_pushcfunction(L, l_player_get_speed);
	lua_settable(L, -3);

	// player.get_turnspeed()
	lua_pushstring(L, "get_turnspeed");
	lua_pushcfunction(L, l_player_get_turnspeed);
	lua_settable(L, -3);

	// player.get_angle()
	lua_pushstring(L, "get_angle");
	lua_pushcfunction(L, l_player_get_angle);
	lua_settable(L, -3);

	// player.get_fov()
	lua_pushstring(L, "get_fov");
	lua_pushcfunction(L, l_player_get_fov);
	lua_settable(L, -3);

	// player.set_x()
	lua_pushstring(L, "set_x");
	lua_pushcfunction(L, l_player_set_x);
	lua_settable(L, -3);

	// player.set_y()
	lua_pushstring(L, "set_y");
	lua_pushcfunction(L, l_player_set_y);
	lua_settable(L, -3);

	// player.set_speed()
	lua_pushstring(L, "set_speed");
	lua_pushcfunction(L, l_player_set_speed);
	lua_settable(L, -3);

	// player.set_turnspeed()
	lua_pushstring(L, "set_turnspeed");
	lua_pushcfunction(L, l_player_set_turnspeed);
	lua_settable(L, -3);

	// player.set_angle()
	lua_pushstring(L, "set_angle");
	lua_pushcfunction(L, l_player_set_angle);
	lua_settable(L, -3);

	// player.set_fov()
	lua_pushstring(L, "set_fov");
	lua_pushcfunction(L, l_player_set_fov);
	lua_settable(L, -3);

	lua_settable(L, -3);

	lua_setglobal(L, "Engine");

	free(log_path);
	return L;
}

void luaE_dostring(char s[], lua_State *L) {
	char *log_path = log_get_path();

	if(L == NULL) {
		L = luaE_new();
	}

	char msg[1000];
	char buff[] = "[ C ] [Script] Attempting to execute Lua string \"%s\"\n\n";
	sprintf(msg, buff, s);

	log_pwrite(log_path, msg);

	if(luaL_dostring(L, s) == LUA_OK) {
		log_pwrite(log_path, "\n[ C ] [Script] Successfully executed Lua string\n");
	} else {
		log_pwrite(log_path, "[ C ] [Script] Execution of Lua string failed:\n");
		luaL_error(L, "Error:%s\n", lua_tostring(L, -1));

		free(log_path);
		lua_close(L);
		exit(1);
	}

	free(log_path);
	lua_close(L);
}

void luaE_dofile(char path[], lua_State *L) {
	char *log_path = log_get_path();
	bool new_state = false;

	if(L == NULL) {
		L = luaE_new();
		new_state = true;
	}

	char msg[1000];
	char buff[] = "[ C ] [Script] Attempting to execute Lua file \"%s\"\n\n";
	sprintf(msg, buff, path);

	log_pwrite(log_path, msg);

	if(luaL_dofile(L, path) == LUA_OK) {
		char mesg[1000];
		char buff[] = "\n[ C ] [Script] Successfully executed Lua file \"%s\"\n";
		sprintf(mesg, buff, path);
		
		log_pwrite(log_path, mesg);
	} else {
		char mesg[1000];
		char buff[] = "[ C ] [Script] Execution of \"%s\" failed:\n";
		sprintf(mesg, buff, path);

		log_pwrite(log_path, mesg);
		luaL_error(L, "Error:%s\n", lua_tostring(L, -1));

		free(log_path);
		if(new_state) lua_close(L);
		exit(1);
	}

	free(log_path);
	if(new_state) lua_close(L);
}

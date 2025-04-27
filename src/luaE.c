/*
 * A custom Lua scripting interface built on Lua's C API
 * Provides helper functions and easy access to the Lua state
 * See luaE.h for documentation
 * 2025 DJaySky
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <lua5.4/lua.h>
#include <lua5.4/lauxlib.h>
#include <lua5.4/lualib.h>

#include "util/log.h"

lua_State *luaE_new() {
	char *log_path = log_get_path();

	log_pwrite(log_path, "[ C ] [Script] Creating new Lua state\n");

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	free(log_path);
	return L;
}

void luaE_dostring(char s[]) {
	char *log_path = log_get_path();

	lua_State *L = luaE_new();

	char msg[1000];
	char buff[] = "[ C ] [Script] Attempting to execute Lua string \"%s\"\n";
	sprintf(msg, buff, s);

	log_pwrite(log_path, msg);

	if(luaL_dostring(L, s) == LUA_OK) {
		log_pwrite(log_path, "[ C ] [Script] Successfully executed Lua string\n");
	} else {
		log_pwrite(log_path, "[ C ] [Script] Execution of Lua string failed:\n");
		luaL_error(L, "Error:%s\n", lua_tostring(L, -1));
	}

	free(log_path);
	lua_close(L);
}

void luaE_dofile(char path[]) {
	char *log_path = log_get_path();

	lua_State *L = luaE_new();

	char msg[1000];
	char buff[] = "[ C ] [Script] Attempting to execute Lua file \"%s\"\n";
	sprintf(msg, buff, path);

	log_pwrite(log_path, msg);

	if(luaL_dofile(L, path) == LUA_OK) {
		char mesg[1000];
		char buff[] = "[ C ] [Script] Successfully executed Lua file \"%s\"\n";
		sprintf(mesg, buff, path);

		log_pwrite(log_path, mesg);
	} else {
		char mesg[1000];
		char buff[] = "[ C ] [Script] Execution of \"%s\" failed:\n";
		sprintf(mesg, buff, path);

		log_pwrite(log_path, mesg);
		luaL_error(L, "Error:%s\n", lua_tostring(L, -1));
	}

	free(log_path);
	lua_close(L);
}

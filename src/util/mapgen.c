/*
 * Map generation methods and script access
 * See mapgen.h for documentation
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL3/SDL.h>
#include <lua.h>

#include "log.h"
#include "luaE.h"
#include "map.h"

void map_gen(int w, int h) {
	char *log_path = log_get_path();
	lua_State *L = luaE_new();

	// reorganize these into a global table later
	lua_pushinteger(L, w);
	lua_setglobal(L, "map_w");

	lua_pushinteger(L, h);
	lua_setglobal(L, "map_h");
	
	char *exe_path = SDL_GetBasePath();
	strcat(exe_path, "%s");

	char file[1000];
	char buff[] = "scripts/mapgen.lua";
	sprintf(file, exe_path, buff);

	luaE_dofile(file, L);

	int *new_map = (int *)calloc(h * w, sizeof(int));
	if(!new_map) {
		log_pwrite(log_path, "[ C ] [Error] Failed to allocate memory for map\n");
		free(log_path);
		lua_close(L);
		exit(1);
	}
	
	if(lua_istable(L, -1)) {
		for(int y = 1; y <= h; y++) {
			lua_pushinteger(L, y);
			lua_gettable(L, -2);

			if(!lua_istable(L, -1)) {
				log_pwrite(log_path, "[ C ] [Error] Value retrieved from map generation is not a 2 dimensional matrix\n");
				free(log_path);
				free(new_map);
				exit(1);
			}

			for(int x = 1; x <= w; x++) {
				lua_pushinteger(L, x);
				lua_gettable(L, -2);

				if(!lua_isinteger(L, -1)) {
					log_pwrite(log_path, "[ C ] [Error] Value retrieved from map generation does not use integers for map cells\n");
					free(log_path);
					free(new_map);
					exit(1);
				}

				if(y-1 == 0 || x-1 == 0 || y == h-1 || x == w-1) {
					new_map[(y-1) * w + (x-1)] = 1;
				} else if(y-1 > 0 && x-1 > 0 && y < h-1 && x < w-1) {
					new_map[(y-1) * w + (x-1)] = lua_tointeger(L, -1);
				}

				lua_pop(L, 1);
			}
			
			lua_pop(L, 1);
		}				
	} else {
		log_pwrite(log_path, "[ C ] [Error] Value retrieved from map generation is not a table\n");
		free(log_path);
		free(new_map);
		exit(1);
	}
	
	map_change(new_map, w, h);

	free(log_path);
	lua_close(L);
}

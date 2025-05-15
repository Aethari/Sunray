/*
 * Definition and manipulation of the game's map
 * See map.h for documentation
 * 2025 DJaySky
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "log.h"
#include "map.h"

int *map = NULL;
int map_size_x, map_size_y;

int map_get_size_x() {
	return map_size_x;
}

int map_get_size_y() {
	return map_size_y;
}

void map_change(int *new_map, int sx, int sy) {
	char *log_path = log_get_path();
	log_pwrite(log_path, "[ C ] [Map] Changing loaded map\n");
	map = new_map;

	char msg[1000];
	char buff[] = "[ C ] [Map] Setting new map size (%d, %d)\n";
	sprintf(msg, buff, sx, sy);

	log_pwrite(log_path, msg);
	map_size_x = sx;
	map_size_y = sy;

	free(log_path);
}

TileType map_get(int x, int y) {
	char *log_path = log_get_path();

	if(map == NULL) {
		printf("[ C ] [WARNING] Map is NULL in map_get()\n");
		return TILE_EMPTY;
	}

	if(
		x >= 0 &&
		x < map_get_size_x() &&
		y >= 0 &&
		y < map_get_size_y()
	) {
		free(log_path);
		return (TileType)map[y * map_get_size_x() + x];
	} else {
		char msg[1000];
		char buff[] = "[ C ] [Error] Map tile (%d, %d) out of bounds in map_get()\n";
		sprintf(msg, buff, x, y);

		log_pwrite(log_path, msg);

		free(log_path);
		exit(1);
	}
}

void map_set(int value, int x, int y) {
	map[y * map_get_size_x() + x] = value;
}

bool map_check_pos(int pos_x, int pos_y) {
	TileType tile = (TileType)map_get(pos_x, pos_y);

	switch(tile) {
		case TILE_EMPTY:
			return false;
		default:
			return true;
	}
}

bool map_check_dir(int pos_x, int pos_y, float dx, float dy) {
	TileType tile = (TileType)map_get((int)(pos_x + dx), (int)(pos_y + dy));

	switch(tile) {
		case TILE_EMPTY:
			return false;
		default:
			return true;
	}
}

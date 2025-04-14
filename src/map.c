#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log.h"

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

int map_get(int x, int y) {
	return 0;
}

void map_set(int value, int x, int y) {
}

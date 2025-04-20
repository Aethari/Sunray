#ifndef MAP_H
#define MAP_H

extern int *map;

int map_get_size_x();
int map_get_size_y();

/// Changes the currently loaded map to a completely new one.
/// Also sets map_size_x and map_size_y to new values.
int map_change(int *new_map, int sx, int sy);

/// Gets the value of a tile on the currently loaded map
int map_get(int x, int y);

/// Sets the value of a tile on the currently loaded map
void map_set(int value, int x, int y);

/// Checks collision from the given position.
/// Returns true if collision was found, false if not
bool map_check_pos(int pos_x, int pos_y);

/// Checks collision from the given position, in the given direction
/// Returns true if collision was found, false if not
bool map_check_dir(int pos_x, int pos_y, float dx, float dy);

#endif

/*
 * Definition and manipulation of the game's map
 * 2025 Aethari
 *
 * Some notes about maps:
 * - There can only ever be one map loaded at any given time
 *   - Other maps can (obviously) be stored in variables
 */

#include <stdbool.h>

#ifndef MAP_H
#define MAP_H

typedef enum {
	TILE_EMPTY,
	TILE_BRICK_WALL,
	TILE_DEBUG,
	TILE_INVISIBLE
} TileType;

extern int *map;

int map_get_size_x();
int map_get_size_y();

/// Changes the currently loaded map to a completely new one.
/// Also sets map_size_x and map_size_y to new values.
///
/// Parameters:
/// - new_map: A pointer to a integer array representing the new map
/// - sx: 	   The width of the new map
/// - sy: 	   The height of the new map
void map_change(int *new_map, int sx, int sy);

/// Gets the value of a tile on the currently loaded map.
///
/// Parameters:
/// - x,y: The coordinates of the tile to get
TileType map_get(int x, int y);

/// Sets the value of a tile on the currently loaded map.
///
/// Parameters:
/// - value: The new number for the tile
/// - x, y:  The coordinates of the tile to set
void map_set(int value, int x, int y);

/// Checks collision from the given position.
/// Returns true if collision was found, false if not.
///
/// Parameters:
/// - pos_x, pos_y: The coordiantes of the tile to be checked
bool map_check_pos(int pos_x, int pos_y);

/// Checks collision from the given position, in the given direction.
///
/// Parameters:
/// - pos_x, pos_y: The coordinates of the central tile to be checked
/// - dx, dy: 		The direction (distance) to check. Will be added to 
/// 		  		pos_x and pos_y
///
/// Returns:
/// True if collision was found, false if not.
bool map_check_dir(int pos_x, int pos_y, float dx, float dy);

#endif

/*
 * Map generation methods and script access
 * 2025 Aethari
 */

#ifndef MAPGEN_H
#define MAPGEN_H

/// Generates a 1D integer array representing a
/// unique dungeon. Uses a Lua script (src/scripts
/// /mapgen.lua) to do the actual generation, then
/// converts the resulting table into the C array.
/// After generating the map, map_change() from 
/// `map.h` is called to immediately change to the 
/// new map.
///
/// Parameters:
/// - w,h: The dimensions (in tiles) of the map
void map_gen(int w, int h);

#endif

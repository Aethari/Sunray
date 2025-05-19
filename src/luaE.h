/*
 * A custom Lua scripting interface built on Lua's C API
 * Provides helper functions and easy access to the Lua state
 * 2025 Aethari
 *
 * I chose to name the header and also functions luaE to go
 * along with the existing C API's naming conventions of "lua"
 * with a capital letter appended.
 *
 * "luaE" stands for "Lua Engine"
 */

#include <lua.h>

#ifndef LUAE_H
#define LUAE_H

/// Creates a new lua_State with the neccessary engine 
/// globals that can be used to run Lua code.
///
/// Returns:
/// A pointer to a new lua_State with the engine's 
/// globals
///
/// Example usage:
/// 	lua_State *L = luaE_new();
/// 	// you MUST close it when done
/// 	lua_close(L);
lua_State *luaE_new();

/// Uses a given lua_State to run a string of Lua
/// code. If the lua_State is NULL, a new lua_State
/// is created with luaE_new().
///
/// Parameters:
/// - s: The string of Lua code to run
void luaE_dostring(char s[], lua_State *L);

/// Uses a given lua_State to run Lua code loaded
/// from a file. If the lua_State is NULL, a new
/// lua_State is created with luaE_new().
///
/// Parameters:
/// - path: The path to a .lua file to run
/// - L: A pointer to a Lua state that the code will be run with
void luaE_dofile(char path[], lua_State *L);

#endif

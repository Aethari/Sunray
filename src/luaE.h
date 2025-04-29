/*
 * A custom Lua scripting interface built on Lua's C API
 * Provides helper functions and easy access to the Lua state
 * 2025 DJaySky
 *
 * I chose to name the header and also functions luaE to go
 * along with the existing C API's naming conventions of "lua"
 * with a capital letter appended.
 *
 * "luaE" stands for "Lua Engine"
 */

#include <lua5.4/lua.h>

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

/// Creates a new lua_State using luaE_new and then
/// uses that state to run Lua code.
///
/// Parameters:
/// - s: The string of Lua code to run
void luaE_dostring(char s[]);

/// Creates a new lua_State using luaE_new and then
/// uses that state to run Lua code loaded from a 
/// file.
///
/// Parameters:
/// - path: The path to a .lua file to run
void luaE_dofile(char path[]);

#endif

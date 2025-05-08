Vendored programs all have their own LICENSE files located in the directory the
source can be found in.

VCR OSD Mono font: https://www.dafont.com/vcr-osd-mono.font

Vendored directories:
	SDL: a mirror of the SDL development repo
	SDL_ttf: a mirror of the SDL_ttf development repo
	Lua: a copy of the Lua 5.4 source code - not a repo 

Unix dependencies:
	liblua54.a: static library for Lua 5.4
	libSDL3.so.0.2.12: dynamic library for SDL
	libSDL3_ttf.so.0.3.0: dynamic library for SDL_ttf

	.so files are symlinked into <name>.so.0 and
	<name>.so within the build directory during the
	build process.

Win dependencies:
	lua54.dll: dynamic library for Lua 5.4
	lua54.dll.a: static library for Lua 5.4 only needed at link/compile time
	SDL3.dll: dynamic library for SDL
	SDL3_ttf.dll: dynamic library for SDL_ttf

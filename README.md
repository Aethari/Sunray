# Sunray: A raycasted game/engine
Welcome to Sunray, my current main project. Sunray is a first person,
raycasted dungeon crawler in ***very*** early development. As the 
project expands, its focus and direction will become more clear, as I
have not fully finished the game's design yet.

**Note:** Sunray is merely a working title. When I am further along with
the game's development, I will choose an actual title for the game. Once
the game's development is complete, I will make a game framework/engine
for raycasting called Sunray.

### "Real" name ideas:
- 

## Building
Because of the required cross-platform functionality required by modern games,
I have done my best to make the build process as seamless for the user as
possible. In order to do this, `SDL`, `SDL_ttf`, and Lua are all vendored in
the [lib](lib/) directory. `SDL` and `SDL_ttf` are Git submodules, so that
the entirety of their codebase is not being pushed and pulled during development.  

#### Availability
Due to testing constraints and platform maintenance restrictions, Sunray is
only supported on two platforms: UNIX (tested on Linux with glibc) and
Windows. There are few instances of platform-specific code in the project,
but they are there. The Makefile also only supports these platforms. If
you want additional platforms to be supported, feel free to make the
changes and create a pull request. This, however, is not a priority for
me, and I will not be undertaking it myself.

### 0. Dependencies
- `git`: I am going to assume that your access of this repo indicates that
		 you probably have git anyway. But for a thorough list, it should
		 be included anyway.

- `Make`: Make is used to simplify the build process via the [Makefile](Makefile).
		  You can check if Make is installed by running `make -v` in your terminal.

- C compiler: I use `gcc` on Unix and MinGW's gcc on Windows. This can be
			  changed in the [Makefile](Makefile) to suit your environment. 

### 1. Submodules
Because Sunray uses git submodules as dependencies, two commands need to
be run from the project's root folder when the repo is first cloned:
```bash
git submodule init
git submodule update
```
These commands setup the submodules, where the project's headers are located.  

### 2. Building the project
Sunray uses the Make build system. Once the submodules are initialized, 
the [Makefile](Makefile) provides several targets (ran with the `make 
<target>` command):

- all: Also accessible by simply running `make`, this builds the project
	   into an executable for your platform. Runs `make clean` before
	   building to remove outdated build files.

- test: Runs `make all` to build the program, then runs it

- clean: Deletes the "build" dir, including all files within it

If you use a different C compiler than gcc (MinGW gcc on Windows),
you can change the value of the CC (UNIX) and CC_WIN (Windows)
variables in the Makefile.  

To build the project (for packaging, manual installation, etc.),
run `make`. The neccessary files + folders will be placed in
a new "build" directory, alongside the executable. If you want
to immediately run Sunray, run `make test`.  

The files in the "build" directory should be kept in the same
location relative to Sunray's executable. Other than those files,
Sunray is completely portable.

### Build TLDR
1. Clone the repo
2. Setup submodules: `git submodule init && git submodule update`
3. Build the project: `make`
	- or use `make test` to build + run the game

## Project Structure:
Sunray is set up to be both a game and an engine, combined into one program.
As such, it can be hard to tell where the "engine" ends and the "game" begins.
For better comprehension of the source code, it is recommended that you treat
Sunray as a single program split up into modules, and not follow the "game
built on engine" mentality.

### Headers:
It should be pretty easy to figure out which headers do what. I have also
provided a short description of the header's functionality at the top of
the header (.h) file. Just in case, however, they are also documented here.  
(This documentation may be moved to a different location later on)  

[main.c](main.c): The project's main file. This is what is ran when a user
                  runs the executable.  

[player.h](src/player.h): The player. Very few headers outside of the main file
                      should access the code in here. Also handles all of the
                      game's input while not in the menus.  

[luaE.h](src/luaE.h): A simple Lua interface for the engine. `luaE` stands for 
                  "Lua Engine"  

[tex.h](src/assets/tex.h): Contains most (if not all) of the game's textures,
                       plus some functions for accessing and manipulating
                       them.  

[log.h](src/util/log.h): A logger that allows any header to access and log to 
                     the same file.  

[map.h](src/util/map.h): Access and manipulation of the game's current map.
                     Only one map can be loaded at any given time.  

[mapgen.h](src/util/mapgen.h): Handles map generation via a Lua script
							   located at [src/scripts/mapgen.lua](src/
							   scripts/mapgen.lua)

[rays.h](src/util/rays.h): One of the most important headers in the repo. 
                       Provides the ability to cast rays and draw from
                       a perspective.  

[page.h](src/util/page.h): Handles the currently loaded screen/page. This
                           does **not** handle drawing or updating of the
                           pages.

[lfuncs.h](src/lfuncs.h): Redefines engine C functions so that they can be 
                       bound to Lua.

### Folders:
Headers are organized into a variety of folders, whose purpose might not
be quickly reconizable. As such, I have provided documentation here for
what the folders are for.  

[assets](src/assets/): Contains files such as [tex.h](src/assets/tex.h)
                      that hold and provide utility for assets.  

[scripts](src/scripts/): Contains various Lua scripts used by the engine.  

[util](src/util/): Contains various engine utility folders that are 
                   usually used by multiple headers.

[pages](src/pages/): Contains drawing, update, and other such functionality
                     for several of the game's pages.

## License:
Sunray is licensed under the MIT license.  
See [LICENSE.txt](LICENSE.txt) for more info.

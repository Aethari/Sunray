# Sunray: A raycasted game/engine

## "Real" name ideas:
- 

## Project Structure:
### Headers:
It should be pretty easy to figure out which headers do what. I have also
provided a short description of the header's functionality at the top of
the header (.h) file. Just in case, however, they are also documented here.  
(This documentation may be moved to a different location later on)  

[main.c](main.c): The project's main file. This is what is ran when a user
                  runs the executable.  

[player.h](src/player.h): The player. Very few headers outside of the main file
                      should access the code in here. Handles all of the
                      game's input.  

[luaE.h](src/luaE.h): A simple Lua interface for the engine. `luaE` stands for 
                  "Lua Engine"  

[tex.h](src/assets/tex.h): Contains most (if not all) of the game's textures,
                       plus some functions for accessing and manipulating
                       them.  

[log.h](src/util/log.h): A logger that allows any header to access and log to 
                     the same file.  

[map.h](src/util/map.h): Access and manipulation of the game's current map.
                     Only one map can be loaded at any given time.  

[rays.h](src/util/rays.h): One of the most important headers in the repo. 
                       Provides the ability to cast rays and draw from
                       a perspective.  

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

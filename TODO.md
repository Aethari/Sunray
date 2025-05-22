# TODO
Mostly various tasks and small things that need done that could be easily forgotten.

## Easy

## Medium
- Change path logging in luaE.c (in the dofile/dostring commands) to be limited
  to a certain amount of characters - truncate with ... (ellipses)

## Hard

# Specific headers/groups
Tasks that aren't so miscellanious

## [mapgen.lua](src/scripts/mapgen.lua)
- allow tunnels to be generated in the middle of existing tunnels - when generating,
  	- get a random value to decide whether or not to generate the new tunnel
  	- generate a new distance
  	- make a new tunnel perpendicular to the current one, using the new distance
  	- call split at the new tunnel's end
- allow tunnels to connect?
	- this could already be happening because of circling around/divergent
	  generation

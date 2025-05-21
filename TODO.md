# TODO
Mostly various tasks and small things that need done that could be easily forgotten.

## Easy

## Medium
- Change path logging in luaE.c (in the dofile/dostring commands) to be limited
  to a certain amount of characters - truncate with ... (ellipses)

## Hard

# Specific parts
Areas that may have multiple items to do with them

## `mapgen(.lua)`
- add a max size for rooms too (and split areas if they are too big)?
- stop the player from spawning inside of a tile
- fix whatever is causing gaps in walls/allowing sight into OOB

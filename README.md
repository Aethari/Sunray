# Todo
- setup a game loop
    - update then
    - draw
- create a basic map system
    - two layers
        - "main" layer (walls, collision-enabled sprites)
        - "object" layer (enemies, items)
    - maps are stored in a text format, where each value in the table is 
      a single map tile
    - create an enum for map tiles and item/enemies that is mapped to numbers
        - this is what will be used when deciding what is where - it
          simplifies the code so that there aren't a bunch of elifs
    - for now there will be a demo map that is hardcoded into the engine
- implement a player
    - input() function that all input is sent to from the update loop
        - function parses input and decides what to do with it
    - cast() function that displays a raycasted view from the player's 
      perspective
    - player's position is kept in 2d space

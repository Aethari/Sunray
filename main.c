#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/// Access to the engine's log, located next to the engine's executable
#include "log.h"

/// Library functions for the game's map
#include "map.h"

#include "player.h"

/// The game's primary processing loop. Must return a bool determining whether 
/// or not the game should continue running.
bool update() {
	return player_handle_input();
}

/// The game's drawing loop. All draw operations should be called from here
void draw(SDL_Renderer *rend) {
	SDL_SetRenderDrawColorFloat(rend, 0, 0, 0, 1);
	SDL_RenderClear(rend);

	player_draw_cast(rend, true);

	SDL_RenderPresent(rend);
}

int main(int arc, char *argv[]) {
	SDL_Window *window;
	bool running = true;

	log_init();
	char *log_path = log_get_path();

	// Initilize SDL
	log_pwrite(log_path, "[ C ] [Core] Initializing SDL\n");
	SDL_Init(
		SDL_INIT_AUDIO |
		SDL_INIT_VIDEO |
		SDL_INIT_JOYSTICK |
		SDL_INIT_EVENTS
	);

	// Setup the window
	log_pwrite(log_path, "[ C ] [Core] Creating window\n");
	window = SDL_CreateWindow(
		"Sunray",
		800,
		600, 
		SDL_WINDOW_OPENGL
	);
	SDL_Renderer *rend = SDL_CreateRenderer(window, NULL);

	// DEBUG - set the default map
	int map[] = {
		1,1,1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,0,0,0,0,0,0,1,
		1,0,1,1,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,0,0,1,
		1,1,1,1,1,1,1,1,1,1
	};
	map_change(map, 10, 10);
	
	// Main game loop
	log_pwrite(log_path, "[ C ] [Core] Starting main game loop\n");

	player_set_pos_y(1.25);
	player_set_angle(0);
	player_set_speed(.0003);
	player_set_turnspeed(.00025);
	player_set_fov(1.0472);

	while(running) {
		// Update game state
		running = update(window);

		// Draw to the screen
		draw(rend);
	}

	log_pwrite(log_path, "[ C ] [Core] Shutting down\n");
	free(log_path);

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

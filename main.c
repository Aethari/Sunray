#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/// Access to the engine's log, located next to the engine's executable
#include "log.h"

/// Library functions for the game's map
#include "map.h"

/// The game's primary processing loop. Must return a bool determining whether 
/// or not the game should continue running.
bool update(SDL_Window *window) {
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_EVENT_QUIT) {
			return false;
		}
	}

	return true;
}

/// The game's drawing loop. All draw operations should be called from here
void draw(SDL_Window *window) {
	SDL_Surface *surface = SDL_GetWindowSurface(window);
	SDL_ClearSurface(surface, 0, 0, 0, 1);

	SDL_UpdateWindowSurface(window);
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
	log_pwrite(log_path, "[ C ] [Core] Creating SDL window\n");
	window = SDL_CreateWindow(
		"Sunray",
		800,
		600, 
		SDL_WINDOW_OPENGL
	);

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
	while(running) {
		// Update game state
		running = update(window);

		// Draw to the screen
		draw(window);
	}

	free(log_path);

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

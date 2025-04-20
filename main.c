#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/// Access to the engine's log, located next to the engine's executable
#include "log.h"

/// Library functions for the game's map
#include "map.h"

#include "player.h"

/// How long a frame should be, in ms (16ms is 60 fps)
#define FRAME_TARGET_TIME 16
Uint64 last_frame_time = 0;

/// The game's primary processing loop. Must return a bool determining whether 
/// or not the game should continue running.
bool update() {
	Uint64 now = SDL_GetTicks();
	if(last_frame_time == 0) {
		last_frame_time = now;
		return true;
	}

	// we divide by 1000 to convert ms to seconds
	float dt = (now - last_frame_time) / (float)1000;
	last_frame_time = now;

	return player_handle_input(dt);
}

/// The game's drawing loop. All draw operations should be called from here
void draw(SDL_Renderer *rend) {
	SDL_SetRenderDrawColorFloat(rend, 0, 0, 0, 1);
	SDL_RenderClear(rend);

	player_draw_cast(rend);

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

	player_set_pos_x(1);
	player_set_pos_y(1.5);
	player_set_angle(0);
	player_set_speed(4);
	player_set_turnspeed(4);
	player_set_fov(1.0472); // (in radians)

	while(running) {
		Uint64 frame_start = SDL_GetTicks();

		// Update game state
		running = update();

		// Draw to the screen
		draw(rend);

		// Lock processing to FRAME_TARGET_TIME ms per frame
		// was a neccesary step for delta time to work
		Uint64 frame_time = SDL_GetTicks() - frame_start;
		if(frame_time < FRAME_TARGET_TIME) {
			SDL_Delay(FRAME_TARGET_TIME - frame_time);
		}
	}

	log_pwrite(log_path, "[ C ] [Core] Shutting down\n");
	free(log_path);

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

/*
 * The main file, where SDL is started and the game loops run
 * 2025 Aethari
 */

#include <stdio.h>
#include <stdlib.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "util/log.h"
#include "util/map.h"
#include "util/mapgen.h"
#include "util/font.h"
#include "util/page.h"
#include "util/rays.h"

#include "pages/main_menu.h"
#include "player.h"

#include "luaE.h"

#if defined(__WIN32)
	bool is_win = true;
#endif

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
	SDL_SetRenderDrawColorFloat(rend, .04, .04, .04, 1);
	SDL_RenderClear(rend);

	ray_draw_cast(
		rend,
		player_get_fov(),
		player_get_angle(),
		player_get_pos_x(),
		player_get_pos_y()
	);

	SDL_RenderPresent(rend);
}

int main(int arc, char *argv[]) {
	SDL_Window *window;
	bool running = true;

	log_init();
	char *log_path = log_get_path();
	log_clear(log_path);

	// Initialize SDL_ttf
	TTF_Init();

	// Load the game's font
	const char *base_path = SDL_GetBasePath();

	char font_path[2048];
	strcpy(font_path, base_path);
	strcat(font_path, "vcr_ost_mono.ttf");

	font_open(font_path, 12);

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
		1600,
		900, 
		SDL_WINDOW_OPENGL
	);
	SDL_Renderer *rend = SDL_CreateRenderer(window, "opengl");

	// Lock the mouse
	log_pwrite(log_path, "[ C ] [Core] Locking mouse\n");
	SDL_SetWindowRelativeMouseMode(window, true);

	// Main game loop
	log_pwrite(log_path, "[ C ] [Core] Starting main game loop\n");

	page_set_name("Main Menu");

	// Setup player state
	player_set_pos_x(2);
	player_set_pos_y(2);
	player_set_angle(0);
	player_set_speed(3);
	player_set_turnspeed(4);
	player_set_fov(1.22173); // (in radians)

	while(running) {
		char *page_name = page_get_name();
		
		if(strcmp(page_name, "Game") == 0) {
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
		} else if(strcmp(page_name, "Main Menu") == 0) {
			// Update menu state
			running = main_menu_update();

			// Draw main menu
			main_menu_draw(rend);
		} else {
			char msg[1000];
			char buff[] = "[ C ] [Error] Page \"%s\" not found\n";
			sprintf(msg, buff, page_name);

			log_pwrite(log_path, msg);
			exit(0);
		}

		free(page_name);
	}

	log_pwrite(log_path, "[ C ] [Core] Freeing allocated memory\n");
	log_pwrite(log_path, "[ C ] [Core] Shutting down\n");
	free(log_path);
	free(map);

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

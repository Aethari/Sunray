#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL3/SDL.h>

#include "log.h"

float player_pos_x, player_pos_y, player_speed, player_angle;

float player_get_pos_x() {
	return player_pos_x;
}

float player_get_pos_y() {
	return player_pos_y;
}

float player_get_speed() {
	return player_speed;
}

float player_get_angle() {
	return player_angle;
}

void player_set_angle(float new_angle) {
	player_angle = new_angle;
}

bool player_handle_input() {
	SDL_Event event;

	char *log_path = log_get_path();

	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_EVENT_KEY_DOWN:
				switch(event.key.key) {
					case SDLK_W:
						log_pwrite(log_path, "[ C ] [Input] W key down\n");
						break;
					case SDLK_A:
						log_pwrite(log_path, "[ C ] [Input] A key down\n");
						break;
					case SDLK_S:
						log_pwrite(log_path, "[ C ] [Input] S key down\n");
						break;
					case SDLK_D:
						log_pwrite(log_path, "[ C ] [Input] D key down\n");
						break;
					case SDLK_ESCAPE:
						log_pwrite(log_path, "[ C ] [Input] ESC key down\n");
						free(log_path);
						return false;
					default:
						log_pwrite(log_path, "[ C ] [Input] Key not recognized\n");
						break;
				}

				free(log_path);
				return true;
			case SDL_EVENT_QUIT:
				return false;
			default:
				free(log_path);
				return true;
		}
	}

	free(log_path);

	return true;
}

void player_draw_cast(SDL_Renderer *rend) {
	// Create a buffer draw color from the original color (GetRenderDrawColor) to be restored 
	// at the end of the function

	int width, height;
	SDL_GetRenderOutputSize(rend, &width, &height);

	SDL_SetRenderDrawColor(rend, 0, 0, 255, 255);
	SDL_FRect ground = {0, height/2, width, height/2}
	SDL_RenderFillRect(rend, ground);
}

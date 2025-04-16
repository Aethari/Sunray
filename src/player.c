#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL3/SDL.h>

#include "log.h"

float player_pos_x, player_pos_y, player_speed, player_turnspeed, player_angle;

float player_get_pos_x() {
	return player_pos_x;
}

float player_get_pos_y() {
	return player_pos_y;
}

float player_get_speed() {
	return player_speed;
}

float player_get_turnspeed() {
	return player_turnspeed;
}

float player_get_angle() {
	return player_angle;
}

void player_set_speed(float new_speed) {
	player_speed = new_speed;
}

void player_set_turnspeed(float new_speed) {
	player_turnspeed = new_speed;
}

void player_set_angle(float new_angle) {
	player_angle = new_angle;
}

bool player_handle_input() {
	SDL_Event event;
	
	char *log_path = log_get_path();

	float dx = 0;
	float dy = 0;

	// quitting
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_EVENT_QUIT) {
			free(log_path);
			return false;
		}
	}

	// listen for keys
	const bool *keys = SDL_GetKeyboardState(NULL);

	// forwards and backwards
	if(keys[SDL_SCANCODE_W]) {
		dx = cos(player_get_angle()) * player_get_speed();
		dy = sin(player_get_angle()) * player_get_speed();
	} else if(keys[SDL_SCANCODE_S]) {
		dx = -cos(player_get_angle()) * player_get_speed();
		dy = -sin(player_get_angle()) * player_get_speed();
	}

	// left and right
	if(keys[SDL_SCANCODE_A]) {
		dx = cos(player_get_angle() - M_PI/2) * player_get_speed();
		dy = sin(player_get_angle() - M_PI/2) * player_get_speed();
	} else if(keys[SDL_SCANCODE_D]) {
		dx = -cos(player_get_angle() - M_PI/2) * player_get_speed();
		dy = -sin(player_get_angle() - M_PI/2) * player_get_speed();
	}

	// arrow keys to turn
	if(keys[SDL_SCANCODE_LEFT]) {
		player_set_angle(player_get_angle() - player_get_turnspeed());
	} else if(keys[SDL_SCANCODE_RIGHT]) {
		player_set_angle(player_get_angle() + player_get_turnspeed());
	}

	player_pos_x += dx;
	player_pos_y += dy;

	free(log_path);
	return true;
}

void player_cast_rays() {
	float angle = player_get_angle();
}

void player_draw_cast(SDL_Renderer *rend, bool draw_debug) {
	int width, height;
	SDL_GetRenderOutputSize(rend, &width, &height);

	// Draw the ground
	SDL_FRect ground;
	ground.x = 0;
	ground.y = height/2;
	ground.w = width;
	ground.h = height/2;

	SDL_SetRenderDrawColorFloat(rend, 0, .1, .2, 1);
	SDL_RenderFillRect(rend, &ground);

	if(draw_debug) {
		float new_x = player_get_pos_x() * 500;
		float new_y = player_get_pos_y() * 500;

		SDL_FRect player;
		player.x = new_x;
		player.y = new_y;
		player.w = 16;
		player.h = 16;

		SDL_SetRenderDrawColorFloat(rend, 0, 1, 0, 1);
		SDL_RenderFillRect(rend, &player);

		SDL_SetRenderDrawColorFloat(rend, 1, 0, 0, 1);
		SDL_RenderLine(rend, 
			new_x, 
			new_y, 
			new_x + cos(player_get_angle()) * 100, 
			new_y + sin(player_get_angle()) * 100
		);
	}

	player_cast_rays();
}

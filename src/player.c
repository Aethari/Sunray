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
	char *log_path = log_get_path();

	char msg[1000];
	sprintf(msg, "[ C ] [Event] Setting player speed to %f\n", new_speed);
	log_pwrite(log_path, msg);

	player_speed = new_speed;

	free(log_path);
}

void player_set_turnspeed(float new_speed) {
	char *log_path = log_get_path();

	char msg[1000];
	sprintf(msg, "[ C ] [Event] Setting player turn speed to %f\n", new_speed);
	log_pwrite(log_path, msg);

	player_turnspeed = new_speed;

	free(log_path);
}

void player_set_angle(float new_angle) {
	char *log_path = log_get_path();

	char msg[1000];
	sprintf(msg, "[ C ] [Event] Setting player angle to %f\n", new_angle);
	log_pwrite(log_path, msg);

	player_angle = new_angle;

	free(log_path);
}

bool player_handle_input() {
	SDL_Event event;
	
	char *log_path = log_get_path();

	float dx = 0;
	float dy = 0;

	const Uint8 *keys = SDL_GetKeyboardState(NULL);

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

	// quitting
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_EVENT_QUIT) {
			free(log_path);
			return false;
		}
	}

	//printf("player_x, player_y: %f, %f\n", player_get_pos_x(), player_get_pos_y());

	player_pos_x += dx;
	player_pos_y += dy;

	free(log_path);
	return true;
}

void player_cast_ray() {
	float angle = player_get_angle();
}

void player_draw_cast(SDL_Renderer *rend) {
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
}

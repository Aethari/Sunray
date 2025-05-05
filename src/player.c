/*
 * Variables and functions to manage the player
 * See player.h for documentation
 * 2025 DJaySky
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SDL3/SDL.h>

#include "util/log.h"
#include "util/map.h"
#include "assets/tex.h"

#define WALL_COLLISION_DISTANCE .2

float player_pos_x, player_pos_y, player_speed, player_turnspeed, player_angle, player_fov;

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

float player_get_fov() {
	return player_fov;
}

void player_set_pos_x(float new_x) {
	player_pos_x = new_x;
}

void player_set_pos_y(float new_y) {
	player_pos_y = new_y;
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

void player_set_fov(float new_fov) {
	player_fov = new_fov;
}

bool player_handle_input(float dt) {
	SDL_Event event;
	
	float dx = 0;
	float dy = 0;

	float speed = player_get_speed() * dt;
	float turn_speed = player_get_turnspeed() * dt;

	// quitting
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_EVENT_QUIT) {
			return false;
		}
	}

	// listen for keys
	const bool *keys = SDL_GetKeyboardState(NULL);

	// forwards and backwards
	if(
		keys[SDL_SCANCODE_W] ||
		keys[SDL_SCANCODE_UP] ||
		keys[SDL_SCANCODE_I]
	) {
		int pos_x = player_get_pos_x() + cos(player_get_angle()) * WALL_COLLISION_DISTANCE;
		int pos_y = player_get_pos_y() + sin(player_get_angle()) * WALL_COLLISION_DISTANCE;

		if(!map_check_pos(pos_x, pos_y)) {
			dx = cos(player_get_angle()) * speed;
			dy = sin(player_get_angle()) * speed;
		}
	} else if(
		keys[SDL_SCANCODE_S] ||
		keys[SDL_SCANCODE_DOWN] ||
		keys[SDL_SCANCODE_K]
	) {
		int pos_x = player_get_pos_x() - cos(player_get_angle()) * WALL_COLLISION_DISTANCE;
		int pos_y = player_get_pos_y() - sin(player_get_angle()) * WALL_COLLISION_DISTANCE;

		if(!map_check_pos(pos_x, pos_y)) {
			dx += -cos(player_get_angle()) * speed;
			dy += -sin(player_get_angle()) * speed;
		}
	}

	// left and right
	if(keys[SDL_SCANCODE_A]) {
		int pos_x = player_get_pos_x() + cos(player_get_angle() - M_PI/2) * WALL_COLLISION_DISTANCE;
		int pos_y = player_get_pos_y() + sin(player_get_angle() - M_PI/2) * WALL_COLLISION_DISTANCE;

		if(!map_check_pos(pos_x, pos_y)) {
			dx += cos(player_get_angle() - M_PI/2) * speed;
			dy += sin(player_get_angle() - M_PI/2) * speed;
		}
	} else if(keys[SDL_SCANCODE_D]) {
		int pos_x = player_get_pos_x() - cos(player_get_angle() - M_PI/2) * WALL_COLLISION_DISTANCE;
		int pos_y = player_get_pos_y() - sin(player_get_angle() - M_PI/2) * WALL_COLLISION_DISTANCE;

		if(!map_check_pos(pos_x, pos_y)) {
			dx += -cos(player_get_angle() - M_PI/2) * speed;
			dy += -sin(player_get_angle() - M_PI/2) * speed;
		}
	}

	// arrow keys to turn
	if(keys[SDL_SCANCODE_LEFT] || keys[SDL_SCANCODE_J]) {
		player_set_angle(player_get_angle() - turn_speed);
	} else if(keys[SDL_SCANCODE_RIGHT] || keys[SDL_SCANCODE_L]) {
		player_set_angle(player_get_angle() + turn_speed);
	}

	player_pos_x += dx;
	player_pos_y += dy;

	return true;
}

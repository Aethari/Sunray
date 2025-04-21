#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SDL3/SDL.h>

#include "log.h"
#include "map.h"

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

	// collision (kind of, almost) works, but instead of checking absolute directions,
	// we need to check the direction the player is trying to move (using trig and stuff)

	// forwards and backwards
	if(
		keys[SDL_SCANCODE_W] ||
		keys[SDL_SCANCODE_UP]
	) {
		int pos_x = player_get_pos_x() + cos(player_get_angle()) * WALL_COLLISION_DISTANCE;
		int pos_y = player_get_pos_y() + sin(player_get_angle()) * WALL_COLLISION_DISTANCE;

		if(!map_check_pos(pos_x, pos_y)) {
			dx = cos(player_get_angle()) * speed;
			dy = sin(player_get_angle()) * speed;
		}
	} else if(
		keys[SDL_SCANCODE_S] ||
		keys[SDL_SCANCODE_DOWN]
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

void player_cast_ray(float angle, float *perp_wall_dist, float *wall_height) {
	float x = player_get_pos_x();
	float y = player_get_pos_y();
	int map_x = floor(x);
	int map_y = floor(y);

	// the directions of the ray
	float ray_dir_x = cos(angle);
	float ray_dir_y = sin(angle);

	// how far to move the ray to cross a tile
	// dd = DeltaDist
	float dd_x = fabsf(1 / ray_dir_x);
	float dd_y = fabsf(1 / ray_dir_y);

	// which direction to move the ray
	int step_x, step_y;

	//  distance from the player's position to the wall
	float side_dist_x, side_dist_y;

	if(ray_dir_x < 0) {
		step_x = -1;
		side_dist_x = (x-map_x) * dd_x;
	} else {
		step_x = 1;
		side_dist_x = (map_x + 1 - x) * dd_x;
	}

	if(ray_dir_y < 0) {
		step_y = -1;
		side_dist_y = (y-map_y) * dd_y;
	} else {
		step_y = 1;
		side_dist_y = (map_y + 1 - y) * dd_y;
	}

	bool hit = false;
	int side;

	while(!hit) {
		// get which wall is closer and move ray along the closer wall
		if(side_dist_x < side_dist_y) {
			side_dist_x = side_dist_x + dd_x;
			map_x = map_x + step_x;
			side = 0;
		} else {
			side_dist_y = side_dist_y + dd_y;
			map_y = map_y + step_y;
			side = 1;
		}

		if(map_get(map_x, map_y) == 1) {
			hit = true;
		}
	}

	if(side == 0) {
		*perp_wall_dist = (map_x - x + (1-step_x) / 2) / ray_dir_x;
	} else {
		*perp_wall_dist = (map_y - y + (1-step_y) / 2) / ray_dir_y;
	}

	*wall_height = 300 / *perp_wall_dist;
}

void player_draw_cast(SDL_Renderer *rend) {
	int width, height;
	SDL_GetRenderOutputSize(rend, &width, &height);

	// the amount of rays to be cast (columns on the screen)
	int rays = 150;

	// the width of each column
	float slice_width = (float)width / rays;

	// how far to move after each ray
	float step = player_get_fov() / (float)rays;

	// draw the ground
	SDL_FRect ground;
	ground.x = 0;
	ground.y = height/2;
	ground.w = width;
	ground.h = height/2;

	SDL_SetRenderDrawColorFloat(rend, .15, .15, .15, 1);
	SDL_RenderFillRect(rend, &ground);

	for(int i = 0; i < rays; i++) {
		float angle = player_get_angle() - (player_get_fov() / 2) + i * step;

		float perp_wall_dist, wall_height;
		player_cast_ray(angle, &perp_wall_dist, &wall_height);

		float corrected_dist = perp_wall_dist * cosf(angle - player_get_angle());
		wall_height = height / corrected_dist;

		int scaled_height;
		if(height < wall_height) {
			scaled_height = height;
		} else {
			scaled_height = wall_height;
		}

		int y_pos = (height/2) - (scaled_height/2);

		SDL_FRect wall;
		wall.x = i*slice_width;
		wall.y = y_pos;
		wall.w = slice_width;
		wall.h = scaled_height;

		float new_color = floor(180 / (1 + corrected_dist / 4));

		SDL_SetRenderDrawColorFloat(rend, new_color/200, new_color/200, new_color/200, 1);
		SDL_RenderFillRect(rend, &wall);
	}
}

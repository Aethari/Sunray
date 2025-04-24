/*
 * Casting primary and helper functions
 * See rays.h for documentation
 * 2025 DJaySky
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <SDL3/SDL.h>

#include "log.h"
#include "map.h"
#include "tex.h"

float ray_cast(float *perp_wall_dist, float *wall_height, float angle, float x, float y) {
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

	float hit_pos = 0;
	
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

		if(map_get(map_x, map_y) >= 1) {
			hit = true;
		}
	}

	if(side == 0) {
		*perp_wall_dist = (map_x - x + (1-step_x) / 2) / ray_dir_x;
		hit_pos = y + *perp_wall_dist * ray_dir_y;
		hit_pos -= floor(hit_pos);
	} else {
		*perp_wall_dist = (map_y - y + (1-step_y) / 2) / ray_dir_y;
		hit_pos = x + *perp_wall_dist * ray_dir_x;
		hit_pos -= floor(hit_pos);
	}

	*wall_height = 300 / *perp_wall_dist;

	return hit_pos;
}

void ray_draw_cast(SDL_Renderer *rend, float fov, float angle, float x, float y) {
	int width, height;
	SDL_GetRenderOutputSize(rend, &width, &height);

	// the amount of rays to be cast (columns on the screen)
	int rays = 150;

	// the width of each column
	float slice_width = (float)width / rays;

	// how far to move after each ray
	float step = fov / (float)rays;

	// draw the ground
	SDL_FRect ground;
	ground.x = 0;
	ground.y = height/2;
	ground.w = width;
	ground.h = height/2;

	SDL_SetRenderDrawColorFloat(rend, .15, .15, .15, 1);
	SDL_RenderFillRect(rend, &ground);

	for(int i = 0; i < rays; i++) {
		float new_angle = angle - (fov / 2) + i * step;

		float perp_wall_dist, wall_height;

		// tile is the coordinate on the wall that the ray hit
		float tile = ray_cast(&perp_wall_dist, &wall_height, new_angle, x, y);

		// the column of the texture to be pulled from
		// remember - this is zero-indexed
		int tex_x = tile * TEX_WIDTH;

		float corrected_dist = perp_wall_dist * cosf(new_angle - angle);
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

		int (*tex)[TEX_WIDTH] = NULL;

		// instead of getting the player's position, it needs to be the 
		// global point of collision with the wall
		switch(map_get(map_x, map_y)) {
			case TILE_BRICK_WALL:
				tex = brick_tex;
				break;
			default:
				break;
		}

		// loop through, from (bottom to top?) (top to bottom?) of the wall,
		// sampling from the texture to decide which color to draw
		if(tex != NULL) {
			for(int j = 0; j < wall_height; j++) {
				// the segment/pixel on the wall
				int seg = wall_height/j;

				// the pixel y of the texture
				int tex_y = 0;
				tex_y = seg;

				int color = tex_get_pix(tex, tex_x, tex_y);

				printf("color: %d\n", color);
				//SDL_SetRenderDrawColor(rend,
			}
		}

		SDL_SetRenderDrawColorFloat(rend, new_color/200, new_color/200, new_color/200, 1);
		SDL_RenderFillRect(rend, &wall);
	}
}

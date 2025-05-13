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

#include "util/log.h"
#include "util/map.h"
#include "assets/tex.h"

float ray_cast(float *perp_wall_dist, float *wall_height, float *hit_x, float *hit_y, float *out_map_x, float *out_map_y, float angle, float x, float y) {
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
		if(side_dist_x <= side_dist_y) {
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

		if(ray_dir_x > 0) hit_pos = 1 - hit_pos;

		if(hit_pos >= 1) hit_pos = nextafter(1, 0);
		if(hit_pos < 0) hit_pos = 0;
	} else {
		*perp_wall_dist = (map_y - y + (1-step_y) / 2) / ray_dir_y;
		hit_pos = x + *perp_wall_dist * ray_dir_x;
		hit_pos -= floor(hit_pos);

		if(ray_dir_y < 0) hit_pos = 1 - hit_pos;

		if(hit_pos >= 1) hit_pos = nextafter(1, 0);
		if(hit_pos < 0) hit_pos = 0;
	}

	*hit_x = x + ray_dir_x * *perp_wall_dist;
	*hit_y = y + ray_dir_y * *perp_wall_dist;

	*out_map_x = map_x;
	*out_map_y = map_y;

	*wall_height = 300 / *perp_wall_dist;

	return hit_pos;
}

void ray_draw_cast(SDL_Renderer *rend, float fov, float angle, float x, float y) {
	int width, height;
	SDL_GetRenderOutputSize(rend, &width, &height);

	// the amount of rays to be cast (columns on the screen)
	// 150 is good for a pixelated look, but has some rendering issues
	int rays = width;

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

		float perp_wall_dist, wall_height, hit_x, hit_y, map_x, map_y;

		// tile is the coordinate on the wall that the ray hit
		float tile = ray_cast(&perp_wall_dist, &wall_height, &hit_x, &hit_y, &map_x, &map_y, new_angle, x, y);

		// the column of the texture to be pulled from
		int tex_x = tile * TEX_WIDTH;

		if(tex_x < 0) {
			tex_x = 0;
		} else if(tex_x >= TEX_WIDTH) {
			tex_x = TEX_WIDTH - 1;
		}

		float corrected_dist = perp_wall_dist * cosf(new_angle - angle);
		wall_height = height / corrected_dist;

		int scaled_height;
		scaled_height = wall_height;

		int y_pos = (height/2) - (scaled_height/2);

		int (*tex)[TEX_WIDTH] = NULL;

		switch(map_get(map_x, map_y)) {
			case TILE_BRICK_WALL:
				tex = brick_tex;
				break;
			case TILE_DEBUG:
				tex = debug_tex;
				break;
			default:
				tex = empty_tex;
				break;
		}

		// loop through the wall slice, sampling the texture to
		// draw on the wall
		if(tex != NULL) {
			// how big the pixels need to be on the wall
			float scale = scaled_height / (float)TEX_HEIGHT;

			for(int tex_y = 0; tex_y < TEX_HEIGHT; tex_y++) {
				Color color = tex_get_pix(tex, tex_x, tex_y);
				float r, g, b;

				switch(color) {
					case WHITE:
						r = 1;
						g = 1;
						b = 1;
						break;
					default:
						r = 0;
						g = 0;
						b = 0;
						break;
				}

				float new_color = floor(180 / (1 + corrected_dist / 2.5));
				float brightness = new_color / 200;

				SDL_FRect wall;
				wall.x = i*slice_width;
				wall.y = y_pos + tex_y * scale;
				wall.w = slice_width;
				wall.h = scale;

				SDL_SetRenderDrawColorFloat(rend, r * brightness, g * brightness, b * brightness, 1);
				SDL_RenderFillRect(rend, &wall);
			}
		}
	}
}

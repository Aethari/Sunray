/*
 * Various textures used throughout the game, and some helper functions
 * See tex.h for documentation
 * 2025 DJaySky
 */

#include "tex.h"

// textures
int brick_tex[TEX_HEIGHT][TEX_WIDTH] = {
	{0,1,0,0,0,1,0,0},
	{0,1,0,0,0,1,0,0},
	{1,1,1,1,1,1,1,1},
	{0,0,1,0,0,0,1,0},
	{0,0,1,0,0,0,1,0},
	{1,1,1,1,1,1,1,1},
	{1,0,0,0,1,0,0,0},
	{1,0,0,0,1,0,0,0}
};

// functions
int tex_get_pix(int tex[TEX_HEIGHT][TEX_WIDTH], int x, int y) {
	return tex[y][x];
}

/*
 * Various textures used throughout the game, and some helper functions
 * 2025 DJaySky
 */

#ifndef TEX_H
#define TEX_H

#define TEX_WIDTH 8
#define TEX_HEIGHT 8

// textures
extern int brick_tex[TEX_HEIGHT][TEX_WIDTH];

// Gets the given pixel from the given texture
int tex_get_pix(int tex[TEX_HEIGHT][TEX_WIDTH], int x, int y);

#endif

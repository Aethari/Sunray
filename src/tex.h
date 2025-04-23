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

/// Gets the given pixel from the given texture
///
/// Parameters:
/// - tex: The texture to get the pixel from
/// - x, y: The coordinates of the piexel to get
int tex_get_pix(int tex[TEX_HEIGHT][TEX_WIDTH], int x, int y);

#endif

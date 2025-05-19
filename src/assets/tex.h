/*
 * Various textures used throughout the game, colors, and some helper functions
 * 2025 Aethari
 */

#ifndef TEX_H
#define TEX_H

#define TEX_WIDTH 16
#define TEX_HEIGHT 16

typedef enum {
	BLACK,
	WHITE,
	GRAY
} Color;

// textures
extern int empty_tex[TEX_HEIGHT][TEX_WIDTH];
extern int brick_tex[TEX_HEIGHT][TEX_WIDTH];
extern int debug_tex[TEX_HEIGHT][TEX_WIDTH];

/// Gets the given pixel from the given texture
///
/// Parameters:
/// - tex: The texture to get the pixel from
/// - x, y: The coordinates of the piexel to get
Color tex_get_pix(int (*tex)[TEX_WIDTH], int x, int y);

#endif

/*
 * Middleground between UI and SDL_ttf designed to help performance
 * 2025 Aethari
 */

#include <SDL3_ttf/SDL_ttf.h>

#ifndef FONT_H
#define FONT_H

/// Returns the font last set with font_open().
TTF_Font *font_get();

/// Sets up the font that will be accessed by other methods
/// in the header. This reads files, and therefore should
/// not be called every frame.
///
/// Parameters:
/// - path: A string pointing to the .ttf font file to be loaded
/// - size: The pt size to be used for the font
void font_open(char path[], float size);

#endif

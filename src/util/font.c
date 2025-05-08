/*
 * Middleground between UI and SDL_ttf designed to help performance
 * See font.h for documentation
 * 2025 DJaySky
 */

#include <stdio.h>
#include <stdlib.h>

#include <SDL3_ttf/SDL_ttf.h>

#include "util/log.h"

/// This is the actual font var that is accessed by the
/// header.
TTF_Font *font;

TTF_Font *font_get() {
	return font;
}

void font_open(char path[], float size) {
	char *log_path = log_get_path();

	char msg[1000];
	char buff[] = "[ C ] [Font] Loading new font from \"%s\"\n";
	sprintf(msg, buff, path);

	log_pwrite(log_path, msg);
	free(log_path);

	font = TTF_OpenFont(path, size);
}

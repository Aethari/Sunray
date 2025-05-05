/*
 * Drawing and updating for the main menu
 * See main_menu.h for documentation
 * 2025 DJaySky
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL3/SDL.h>

#include "util/log.h"
#include "util/page.h"

#define MENU_MAX_TEXT_LEN 2048

int menu_index = 0;

/// A struct representing a single menu item.
/// Mostly used to simplify update and draw
/// calls.
struct MenuItem {
	int index;
	char text[MENU_MAX_TEXT_LEN];
	SDL_FRect rect;
};

bool main_menu_update() {
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_EVENT_QUIT) {
			return false;
		}
	}

	const bool *keys = SDL_GetKeyboardState(NULL);
	if(
		keys[SDL_SCANCODE_W] ||
		keys[SDL_SCANCODE_UP]
	) {
		if(menu_index - 1 > -1) {
			menu_index--;
		}
	} else if(
		keys[SDL_SCANCODE_S] ||
		keys[SDL_SCANCODE_DOWN]
	) {
		if(menu_index + 1 <= 2) { // change this later
		}
	} else if(
		keys[SDL_SCANCODE_RETURN] ||
		keys[SDL_SCANCODE_X]
	) {
		switch(menu_index) {
			case 0:
				page_set_name("Game");
				break;
			case 1:
				// run item 1
				break;
			case 2:
				// run item 2
				break;
			default:
				char *log_path = log_get_path();

				char msg[1000];
				char buff[] = "[ C ] [Core] Main Menu: item %d not found";
				sprintf(msg, buff, menu_index);

				log_pwrite(log_path, msg);

				free(log_path);
				break;
		}
	}

	return true;
}

void main_menu_draw(SDL_Renderer *rend) {
	int w, h;
	SDL_GetRenderOutputSize(rend, &w, &h);

	struct MenuItem start_game;
	start_game.index = 0;
	strcpy(start_game.text, "Start Game");

	start_game.rect.w = 300;
	start_game.rect.h = 150;
	start_game.rect.x = (w/2) - (start_game.rect.w/2);
	start_game.rect.y = (h/2) - start_game.rect.h - 10;

	SDL_SetRenderDrawColorFloat(rend, 1, 1, 1, 1);
	SDL_FRect *rect;
	rect = &start_game.rect;
	SDL_RenderFillRect(rend, rect);
}

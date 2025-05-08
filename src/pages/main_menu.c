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
#include <SDL3_ttf/SDL_ttf.h>

#include "util/log.h"
#include "util/font.h"
#include "util/page.h"

#define MENU_ITEM_COUNT 2
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

struct MenuItem menu_items[MENU_ITEM_COUNT] = {
	{0, "Start Game", {0}},
	{1, "Quit Game", {0}}
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
		keys[SDL_SCANCODE_I] ||
		keys[SDL_SCANCODE_UP]
	) {
		if(menu_index - 1 > -1) {
			menu_index--;
		}
	} else if(
		keys[SDL_SCANCODE_S] ||
		keys[SDL_SCANCODE_K] ||
		keys[SDL_SCANCODE_DOWN]
	) {
		if(menu_index + 1 <= 1) { // change this later
			menu_index++;
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
				return false;
			default:
				char *log_path = log_get_path();

				char msg[1000];
				char buff[] = "[ C ] [Core] Main Menu: item %d not found";
				sprintf(msg, buff, menu_index);

				log_pwrite(log_path, msg);

				free(log_path);
				break;
		}
	} else if(
		keys[SDL_SCANCODE_ESCAPE]
	) {
		return false;
	}

	return true;
}

void main_menu_draw(SDL_Renderer *rend) {
	int w, h;
	SDL_GetRenderOutputSize(rend, &w, &h);

	SDL_SetRenderDrawColorFloat(rend, 0, 0, 0, 1);
	SDL_RenderClear(rend);
	
	for (int i = 0; i < MENU_ITEM_COUNT; i++) {
		menu_items[i].rect.w = 300;
		menu_items[i].rect.h = 75;
		menu_items[i].rect.x = (w/2) - (menu_items[i].rect.w/2);
		menu_items[i].rect.y = (h/2) - 100 + (i * 150);
	}

	TTF_TextEngine *eng = TTF_CreateRendererTextEngine(rend);
	TTF_SetFontSize(font_get(), 40);

	for(int i = 0; i < MENU_ITEM_COUNT; i++) {
		struct MenuItem item = menu_items[i];
		SDL_FRect *rect = &item.rect;
		
		if(menu_index == item.index) {
			SDL_SetRenderDrawColorFloat(rend, .12, .12, .12, 1);
			SDL_RenderFillRect(rend, rect);
		}

		SDL_SetRenderDrawColorFloat(rend, 1, 1, 1, 1);
		SDL_RenderRect(rend, rect);

		TTF_Text *text_rend = TTF_CreateText(eng, font_get(), item.text, strlen(item.text));
		TTF_SetTextColorFloat(text_rend, 1, 1, 1, 1);

		int text_w, text_h;
		TTF_GetStringSize(font_get(), item.text, strlen(item.text), &text_w, &text_h);
		
		TTF_DrawRendererText(text_rend, rect->x +rect->w/2 - text_w/2, rect->y + text_h/2);
		TTF_DestroyText(text_rend);
	}

	TTF_DestroyRendererTextEngine(eng);

	SDL_RenderPresent(rend);
}

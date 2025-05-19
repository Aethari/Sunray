/*
 * Drawing and updating for the main menu
 * 2025 Aethari
 */

#ifndef MAIN_MENU_H
#define MAIN_MENU_H

/// The main menu's primary processing loop. Must return
/// a bool determining whether or not the game should
/// continue running. Also directly handles input.
///
/// Returns:
/// A bool representing whether or not the game should
/// continue updating. If false, the game closes.
bool main_menu_update();

/// Draws all of the elements present in the main menu
/// to the screen.
///
/// Parameters:
/// - rend: A pointer to the SDL_Renderer to be drawn on
void main_menu_draw(SDL_Renderer *rend);

#endif

#ifndef PLAYER_H
#define PLAYER_H

float player_get_pos_x();
float player_get_pos_y();
float player_get_speed();
float player_get_turnspeed();
float player_get_angle();

void player_set_speed(float new_speed);
void player_set_turnspeed(float new_speed);
void player_set_angle(float new_angle);

/// Recieves all input events from SDL and decides what to do with them.
bool player_handle_input();

/// Casts a ray out
/// Not to be confused with player_draw_cast(), which takes the data
/// returned by this function and draws it on the screen
void player_cast_ray(float angle, float *perp_wall_dist, float *wall_height);

/// Draws the map from the player's perspective on the given SDL_Surface.
/// Should be called at the end of the drawing loop
void player_draw_cast(SDL_Renderer *rend, bool draw_debug);

#endif

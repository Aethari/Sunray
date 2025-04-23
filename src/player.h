/*
 * Variables and functions to manage the player
 * 2025 DJaySky
 */

#ifndef PLAYER_H
#define PLAYER_H

float player_get_pos_x();
float player_get_pos_y();
float player_get_speed();
float player_get_turnspeed();
float player_get_angle();
float player_get_fov();

void player_set_pos_x(float new_x);
void player_set_pos_y(float new_y);
void player_set_speed(float new_speed);
void player_set_turnspeed(float new_speed);
void player_set_angle(float new_angle);
void player_set_fov(float new_fov);

/// Recieves all input events from SDL and decides what to do with them.
/// Intended to be called from the game's update loop, which should 
/// handle delta time.
///
/// Parameters:
/// - dt: The deltatime from the game's update loop
bool player_handle_input(int dt);

#endif

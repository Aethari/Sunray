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
bool player_handle_input(int dt);

#endif

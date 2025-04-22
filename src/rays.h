#ifndef RAYS_H
#define RAYS_H

/// Casts a ray and modifies the values of perp_wall_dist and wall_height
/// based on the collision it finds. Not to be confused with ray_draw_cast,
/// which uses the data from this function to draw to the screen.
void ray_cast(float *perp_wall_dist, float *wall_height, float angle, float x, float y);

/// Casts a ray from somthing with a FOV and rotation (like the player 
/// or an enemy) and draws it. Not to be confused with ray_cast, which
/// retrieves the data from a casted ray.
void ray_draw_cast(SDL_Renderer *rend, float fov, float angle, float x, float y);

#endif

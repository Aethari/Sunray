/*
 * Casting primary and helper functions
 * 2025 DJaySky
 */

#ifndef RAYS_H
#define RAYS_H

/// Casts a ray and modifies the values of perp_wall_dist and wall_height
/// based on the collision it finds. Not to be confused with ray_draw_cast,
/// which uses the data from this function to draw to the screen.
///
/// Parameters:
/// - perp_wall_dist: A pointer to a float var representing how far the
///   ray travelled before hitting a wall
/// - wall_height: A pointer to a float var representing the height of the
///   wall that the ray hit
/// - angle: The angle that the ray is being casted from
/// - x, y: The position where the ray is being casted from
///
/// Returns:
/// A float representing the texture coordinate on the wall that was hit
float ray_cast(float *perp_wall_dist, float *wall_height, float angle, float x, float y);

/// Casts a ray from somthing with a FOV and rotation (like the player 
/// or an enemy) and draws it. Not to be confused with ray_cast, which
/// retrieves the data from a casted ray.
///
/// Parameters:
/// - rend: A pointer to an SDL renderer to be drawn on
/// - fov: The fov of the "camera" that the ray is being casted from
/// - angle: The angle that the ray is being casted from
/// - x, y: The position where the ray is being casted from
void ray_draw_cast(SDL_Renderer *rend, float fov, float angle, float x, float y);

#endif

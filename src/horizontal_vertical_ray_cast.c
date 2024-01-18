/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_vertical_ray_cast.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:17:13 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/18 19:30:02 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void find_h_intersection(t_vars *vars)
{
    t_ray *ray;

    ray = vars->ray;
    ray->h_y_intersection = floor(vars->player_y / TILE_SIZE) * TILE_SIZE;
    if (ray->is_down)
    {
        ray->h_y_intersection += TILE_SIZE;
        ray->ya = TILE_SIZE;
    }
    else
        ray->ya = -TILE_SIZE;
    ray->h_x_intersection = ((ray->h_y_intersection - vars->player_y) / tan(ray->angle));
    ray->h_x_intersection += vars->player_x;
    if (!ray->is_down)
        ray->h_y_intersection--;
    ray->xa = TILE_SIZE / tan(ray->angle);
}

void horizontal_ray_cast(t_vars *vars) 
{   
    int     hit_wall;
    t_ray   *ray;

    hit_wall = 0;
    ray = vars->ray;
    find_h_intersection(vars);
    if ((!ray->is_right && ray->xa > 0) || (ray->is_right && ray->xa < 0))
        ray->xa *= -1;
    while (!hit_wall) {
        hit_wall = is_wall(&vars->data->map, ray->h_x_intersection, ray->h_y_intersection);
        if (hit_wall == 1)
            ray->h_distance = sqrt(pow(vars->player_x - ray->h_x_intersection, 2) + pow(vars->player_y - ray->h_y_intersection, 2));
        else
        {
            ray->h_x_intersection += ray->xa;
            ray->h_y_intersection += ray->ya;
        }
    }
}

void find_v_intersection(t_vars *vars)
{
    t_ray *ray;

    ray = vars->ray;
    ray->v_x_intersection = floor(vars->player_x / TILE_SIZE) * TILE_SIZE;
    if (ray->is_right)
    {
        ray->v_x_intersection += TILE_SIZE;
        ray->xa = TILE_SIZE;
    }
    else
        ray->xa = -TILE_SIZE;
    ray->v_y_intersection = ((ray->v_x_intersection - vars->player_x) * tan(ray->angle));
    ray->v_y_intersection += vars->player_y;
    if (!ray->is_right)
        ray->v_x_intersection--;
    ray->ya = (double)TILE_SIZE * tan(ray->angle);
}

void vertical_ray_cast(t_vars *vars)
{
    int     hit_wall;
    t_ray   *ray;

    hit_wall = 0;
    ray = vars->ray;
    find_v_intersection(vars);
    if ((!ray->is_down && ray->ya > 0) || (ray->is_down && ray->ya < 0))
        ray->ya *= -1;
    while (!hit_wall) {
        hit_wall = is_wall(&vars->data->map, ray->v_x_intersection, ray->v_y_intersection);
        if (hit_wall == 1)
            ray->v_distance = sqrt(pow(vars->player_x - ray->v_x_intersection, 2) + pow(vars->player_y - ray->v_y_intersection, 2));
        else
        {
            ray->v_x_intersection += ray->xa;
            ray->v_y_intersection += ray->ya;
        }
    }
}
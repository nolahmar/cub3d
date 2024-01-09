/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:25:07 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/09 16:48:03 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_ray   initialize_ray(double x, double y, double angle)
// {
//     t_ray ray;
//     ray.ray_x = x;
//     ray.ray_y = y;
//     ray.angle = angle;
//     ray.intersection_x = 0.0;
//     ray.intersection_y = 0.0;
//     ray.xa = 0.0;
//     ray.ya = 0.0;
//     ray.distance = 0.0;
//     return (ray);
// }

void horizontal_ray_cast(t_vars *vars) 
{   
    int     hit_wall;
    t_ray   *ray;

    hit_wall = 0;
    ray = vars->ray;
    // printf("ray_angle: [%f]\n", ray->angle);
    // printf("ray dir: %d\n", ray->is_down);
    ray->h_y_intersection = floor(vars->player_y / (double)TILE_SIZE) * TILE_SIZE;
    // printf("after: h_x_intersection: [%f] h_y_intersection: [%f]\n", ray->h_x_intersection, ray->h_y_intersection);
    if (ray->is_down)
    {
        ray->h_y_intersection += TILE_SIZE;
        ray->ya = TILE_SIZE;
    }
    else
        ray->ya = -TILE_SIZE;
    ray->h_x_intersection = ((ray->h_y_intersection - vars->player_y) / (double)tan(ray->angle));
    ray->h_x_intersection += vars->player_x;
    // printf("before: h_x_intersection: [%f] h_y_intersection: [%f]\n", ray->h_x_intersection, ray->h_y_intersection);
    if (!ray->is_down)
        ray->h_y_intersection--;
    ray->xa = TILE_SIZE / (double)tan(ray->angle);
    if ((!ray->is_right && ray->xa > 0) || (ray->is_right && ray->xa < 0))
        ray->xa *= -1;
    // printf("y: [%f] x: [%f]\n", ray->h_y_intersection, ray->h_x_intersection);
    while (!hit_wall) {
        hit_wall = is_wall(ray->h_x_intersection, ray->h_y_intersection);
        if (hit_wall == 1)
            ray->h_distance = sqrt(pow(vars->player_x - ray->h_x_intersection, 2) + pow(vars->player_y - ray->h_y_intersection, 2));
        else
        {
            ray->h_x_intersection += ray->xa;
            ray->h_y_intersection += ray->ya;
        }
    }
    // printf("hit_wall: [%d]\n", hit_wall);
}

void vertical_ray_cast(t_vars *vars)
{
    int     hit_wall;
    t_ray   *ray;

    hit_wall = 0;
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
    ray->ya = TILE_SIZE * tan(ray->angle);
    if ((!ray->is_down && ray->ya > 0) || (ray->is_down && ray->ya < 0))
        ray->ya *= -1;
    while (!hit_wall) {
        hit_wall = is_wall(ray->v_x_intersection, ray->v_y_intersection);
        if (hit_wall == 1)
            ray->v_distance = sqrt(pow(vars->player_x - ray->v_x_intersection, 2) + pow(vars->player_y - ray->v_y_intersection, 2));
        else
        {
            ray->v_x_intersection += ray->xa;
            ray->v_y_intersection += ray->ya;
        }
    }
}

void draw_3d(t_vars *vars)
{
    int i;
    double wall_height;

    i = 0;
    while (i < WINDOW_WIDTH)
    {
        wall_height = (TILE_SIZE / vars->ray->distance) * 255;
        double constant_factor = TILE_SIZE/ 255.0;
        wall_height = constant_factor * 255;
        int wall_start = (WINDOW_HEIGHT - wall_height) / 2;
        wall_start += WINDOW_HEIGHT / 2;
        int j = wall_start;
        while (j < wall_start + wall_height)
        {
            mlx_pixel_put(vars->mlx, vars->win, i, j, 0xFF0000);
            j++;
        }
        i++;
    }
}

void ray_cast(t_vars *vars)
{
    double current_angle;
    int i;

    current_angle = vars->player_angle - (FOV / 2);
    i = 0;
     while(i <= WINDOW_WIDTH)
     {
        current_angle = fmod(current_angle + 360, 360);
        
        vars->ray->h_distance = 1e6;
        vars->ray->v_distance = 1e6;
        vars->ray->angle = current_angle * M_PI / 180.0;
        check_ray_direction(vars->ray);
        horizontal_ray_cast(vars);
        vertical_ray_cast(vars);
        if (vars->ray->h_distance <= vars->ray->v_distance)
        {
            vars->ray->intersection_x = vars->ray->h_x_intersection;
            vars->ray->intersection_y = vars->ray->h_y_intersection;
            vars->ray->distance = vars->ray->h_distance;
        }
        else
        {
            vars->ray->intersection_x = vars->ray->v_x_intersection;
            vars->ray->intersection_y = vars->ray->v_y_intersection;
            vars->ray->distance = vars->ray->v_distance;
        }
        drawline(vars, vars->ray->intersection_x, vars->ray->intersection_y, 0xFF0000);
        //draw_3d(vars);
        i++;
        current_angle += FOV / (double)WINDOW_WIDTH;
        printf("current_angle: [%f]\n", current_angle);
     }
}
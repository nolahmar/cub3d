/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:25:07 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/11 16:09:56 by nolahmar         ###   ########.fr       */
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
    ray->h_y_intersection = floor(vars->player_y / (double)TILE_SIZE) * TILE_SIZE;
    if (ray->is_down)
    {
        ray->h_y_intersection += TILE_SIZE;
        ray->ya = TILE_SIZE;
    }
    else
        ray->ya = -TILE_SIZE;
    ray->h_x_intersection = ((ray->h_y_intersection - vars->player_y) / (double)tan(ray->angle));
    ray->h_x_intersection += vars->player_x;
    if (!ray->is_down)
        ray->h_y_intersection--;
    ray->xa = TILE_SIZE / (double)tan(ray->angle);
    if ((!ray->is_right && ray->xa > 0) || (ray->is_right && ray->xa < 0))
        ray->xa *= -1;
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

void put_pixel(char* data, int x, int y, int color, int size_line)
{
    char *offset;
    
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        offset = data + (y * size_line) + (x * 4);
        *(unsigned int*)offset = color;
    }
}

void draw_3d(t_vars *vars, int x)
{
    double start_wall;
    double end_wall;
    int y;
    double b;
    double distance;
    double wall_height;
    char *data;
    int size_line;
    int bits_per_pixel;
    int endian;

    b = (vars->player_angle * M_PI / 180.0) - vars->ray->angle;
    y = 0;
    vars->ray->distance *= cos(b);
    distance = (WINDOW_WIDTH / 2) / tan((FOV / 2) * M_PI / 180.0);
    wall_height = (TILE_SIZE / vars->ray->distance) * distance;
    start_wall = (WINDOW_HEIGHT / 2) - (wall_height / 2);
    end_wall = (WINDOW_HEIGHT / 2) + (wall_height / 2);
    data = mlx_get_data_addr (vars->image, &bits_per_pixel, &size_line, &endian);
    for (y = 0; y < start_wall; y++)
        put_pixel(data, x, y, 0xADD8E6, size_line);
    for (y = end_wall; y < WINDOW_HEIGHT; y++)
        put_pixel(data, x, y, 0xFFC7C7, size_line);
    for (y = start_wall; y <= end_wall; y++)
        put_pixel(data, x, y, 0xFF0060, size_line);
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
        // drawline(vars, vars->ray->intersection_x, vars->ray->intersection_y, 0xFF0000);
        draw_3d(vars, i);
        i++;
        current_angle += FOV / (double)WINDOW_WIDTH;
     }
}
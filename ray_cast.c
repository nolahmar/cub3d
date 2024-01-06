/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:25:07 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/06 18:53:19 by nolahmar         ###   ########.fr       */
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
    // printf("player angle hor[%f]\n", vars->ray->angle);
    int hit_wall;

    hit_wall = 0;
    vars->ray->h_y_intersection = floor(vars->player_y / (double)TILE_SIZE) * (double)TILE_SIZE;
    if (check_player_direction(vars, 1) == 2)
        vars->ray->ya = -TILE_SIZE;
    else if (check_player_direction(vars, 1) == 1) {
        vars->ray->h_y_intersection += TILE_SIZE;
        vars->ray->ya = TILE_SIZE;
    }
    vars->ray->xa = vars->ray->ya / (double)tan(vars->ray->angle);
    vars->ray->h_x_intersection = vars->player_x - ((vars->player_y - vars->ray->h_y_intersection) / tan(vars->ray->angle));
    while (!hit_wall) {
        hit_wall = is_wall(vars, vars->ray->h_x_intersection, vars->ray->h_y_intersection, 1);
        printf("h_x[%d] h_y[%d]\n", (int)(vars->ray->h_x_intersection / TILE_SIZE),  (int)(vars->ray->h_y_intersection / TILE_SIZE));
        if (hit_wall == 1)
        {
            vars->ray->h_distance = sqrt(pow(vars->player_x - vars->ray->h_x_intersection, 2) + pow(vars->player_y - vars->ray->h_y_intersection, 2));
            drawline(vars, vars->ray->h_x_intersection, vars->ray->h_y_intersection, 0xF3AA60);
        }
        else
        {
            vars->ray->h_x_intersection += (double)vars->ray->xa;
            vars->ray->h_y_intersection += (double)vars->ray->ya;
        }
    }
}

// void vertical_ray_cast(t_vars *vars) 
// {
//     int hit_wall;

//     hit_wall = 0;
//     // printf("player angle ver[%f]\n", vars->ray->angle);
//     if (check_player_direction(vars, 0) == 3) {
//         vars->ray->v_x_intersection = floor(vars->player_x / (double)TILE_SIZE) * (double)TILE_SIZE + (double)TILE_SIZE;
//         vars->ray->xa = TILE_SIZE;
//         vars->ray->v_y_intersection = vars->player_y + (vars->player_x - vars->ray->v_x_intersection) * tan(vars->ray->angle);
//         vars->ray->ya = (double)TILE_SIZE * (double)tan(vars->ray->angle);
//     } else if (check_player_direction(vars, 0) == 4) {
//         vars->ray->v_x_intersection = floor(vars->player_x / (double)TILE_SIZE) * (double)TILE_SIZE - 1.0;
//         vars->ray->xa = -TILE_SIZE;
//         vars->ray->v_y_intersection = vars->player_y + (vars->player_x - vars->ray->v_x_intersection) * -tan(vars->ray->angle);
//         vars->ray->ya = (double)TILE_SIZE * -tan(vars->ray->angle);
//     }
//     vars->ray->distance = 0.0;
//     hit_wall = is_wall((int)(vars->ray->v_x_intersection / TILE_SIZE), (int)(vars->ray->v_y_intersection / TILE_SIZE));
//     while (!hit_wall) {
//         vars->ray->v_x_intersection += (double)vars->ray->xa;
//         vars->ray->v_y_intersection += (double)vars->ray->ya;
//         hit_wall = is_wall((int)(vars->ray->v_x_intersection / TILE_SIZE), (int)(vars->ray->v_y_intersection / TILE_SIZE));
//     }
//     if (hit_wall == 1)
//     {
//         vars->ray->v_distance = sqrt(pow(vars->player_x - vars->ray->v_x_intersection, 2) + pow(vars->player_y - vars->ray->v_y_intersection, 2));
//         // printf("v_x[%d] v_y[%d]\n", (int)(vars->ray->v_x_intersection / TILE_SIZE),  (int)(vars->ray->v_y_intersection / TILE_SIZE));
//         // printf("v_dis[%f]\n", vars->ray->v_distance);
//     }
//     if (vars->ray->v_x_intersection >= 0 && vars->ray->v_x_intersection < WINDOW_WIDTH 
//         && vars->ray->v_y_intersection >= 0 && vars->ray->v_y_intersection < WINDOW_HEIGHT) {
//         // mlx_pixel_put(vars->mlx, vars->win, vars->ray->v_x_intersection, vars->ray->v_y_intersection, 0xFF9800);
//         drawline(vars, vars->ray->v_x_intersection, vars->ray->v_y_intersection, 0xF6FA70);
//     }
// }

void ray_cast(t_vars *vars)
{
    vars->ray->h_distance = 1e6;
    vars->ray->v_distance = 1e6;
    if (vars->player_angle == 90 || vars->player_angle == 270
    || vars->player_angle == 180 || vars->player_angle == 360)
        vars->player_angle += 1e-10;
    vars->ray->angle = vars->player_angle * M_PI / 180.0;
    horizontal_ray_cast(vars);
    // vertical_ray_cast(vars);
    // if (vars->ray->h_distance <= vars->ray->v_distance)
    // {
        vars->ray->intersection_x = vars->ray->h_x_intersection;
        vars->ray->intersection_y = vars->ray->h_y_intersection;
        vars->ray->distance = vars->ray->h_distance;
    // }
    // else
    // {
    //     vars->ray->intersection_x = vars->ray->v_x_intersection;
    //     vars->ray->intersection_y = vars->ray->v_y_intersection;
    //     vars->ray->distance = vars->ray->v_distance;
    // }
    // if (vars->ray->intersection_x >= 0 && vars->ray->intersection_x < WINDOW_WIDTH 
    //     && vars->ray->intersection_y >= 0 && vars->ray->intersection_y < WINDOW_HEIGHT) {
    //     // mlx_pixel_put(vars->mlx, vars->win, vars->ray->intersection_x, vars->ray->v_y_intersection, 0xFF9800);
    //     drawline(vars, vars->ray->intersection_x, vars->ray->intersection_y, 0xFF0000);
    // }
}

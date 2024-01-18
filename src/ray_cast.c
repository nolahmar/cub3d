/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:25:07 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/18 18:31:22by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void min_distance(t_vars *vars)
{
    printf("ver h_distance[%f] v_distance[%f] diff[%f]\n", vars->ray->h_distance, vars->ray->v_distance, vars->ray->h_distance - vars->ray->v_distance);
    if (vars->ray->h_distance < vars->ray->v_distance)
    {   
        if (vars->ray->h_distance - vars->ray->v_distance >= 0.0 && vars->ray->h_distance - vars->ray->v_distance <= 1.0)
        {
            vars->is_v_ray_cast = 1;
            vars->ray->intersection_x = vars->ray->v_x_intersection;
            vars->ray->intersection_y = vars->ray->v_y_intersection;
            vars->ray->distance = vars->ray->v_distance;
        }
        else
        {
            vars->is_v_ray_cast = 0;
            vars->ray->intersection_x = vars->ray->h_x_intersection;
            vars->ray->intersection_y = vars->ray->h_y_intersection;
            vars->ray->distance = vars->ray->h_distance;
        }
    }
    else
    {
        if (vars->ray->h_distance - vars->ray->v_distance >= 0.0 && vars->ray->h_distance - vars->ray->v_distance <= 1.0)
        {
           vars->is_v_ray_cast = 0;
            vars->ray->intersection_x = vars->ray->h_x_intersection;
            vars->ray->intersection_y = vars->ray->h_y_intersection;
            vars->ray->distance = vars->ray->h_distance; 
        }
        else
        {
            vars->is_v_ray_cast = 1;
            vars->ray->intersection_x = vars->ray->v_x_intersection;
            vars->ray->intersection_y = vars->ray->v_y_intersection;
            vars->ray->distance = vars->ray->v_distance;
        }
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
        vars->ray->angle = current_angle * M_PI / 180;
        check_ray_direction(vars->ray);
        horizontal_ray_cast(vars);
        vertical_ray_cast(vars);
        printf("v_x_inter: [%f] v_y_inter: [%f]\n", vars->ray->v_x_intersection / TILE_SIZE, vars->ray->v_y_intersection / TILE_SIZE);
        printf("h_x_inter: [%f] h_y_inter: [%f]\n", vars->ray->h_x_intersection / TILE_SIZE, vars->ray->h_y_intersection / TILE_SIZE);
        min_distance(vars);
        // printf("ray_cast: [%d]\n", vars->is_v_ray_cast);
        draw_3d(vars, i);
        i++;
        current_angle += FOV / (double)WINDOW_WIDTH;
     }
    //  exit(1);
}
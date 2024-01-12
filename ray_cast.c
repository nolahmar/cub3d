/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:25:07 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/12 18:23:22 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void min_distance(t_vars *vars)
{
    if (vars->ray->h_distance <= vars->ray->v_distance)
        {
            vars->is_h_ray_cast = 1;
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
        vars->ray->angle = current_angle * RED;
        check_ray_direction(vars->ray);
        horizontal_ray_cast(vars);
        vertical_ray_cast(vars);
        min_distance(vars);
        draw_3d(vars, i);
        i++;
        current_angle += FOV / (double)WINDOW_WIDTH;
     }
}
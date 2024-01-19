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
    if (vars->ray->h_distance < vars->ray->v_distance)
    {   
        printf("hor\n");
        vars->is_v_ray_cast = 0;
        vars->ray->intersection_x = vars->ray->h_x_intersection;
        vars->ray->intersection_y = vars->ray->h_y_intersection;
        vars->ray->distance = vars->ray->h_distance;
    }
    else
    {
        printf("ver\n");
        vars->is_v_ray_cast = 1;
        vars->ray->intersection_x = vars->ray->v_x_intersection;
        vars->ray->intersection_y = vars->ray->v_y_intersection;
        vars->ray->distance = vars->ray->v_distance;
    }
}

void copy_ray_data(t_vars *vars, t_ray *ray_copy)
{
    ray_copy->angle = vars->ray->angle;
    ray_copy->h_distance = vars->ray->h_distance;
    ray_copy->v_distance = vars->ray->v_distance;
    ray_copy->is_ver = vars->is_v_ray_cast;
    ray_copy->is_down = vars->ray->is_down;
    ray_copy->is_right = vars->ray->is_right;
}

void correction(t_ray *ray_data, int correct_v)
{
    int i;

    i = 0;
    while (i < WINDOW_WIDTH)
    {
        if (correct_v && ray_data[i].is_ver)
        {
            ray_data->is_ver = 0;
            ray_data->distance = ray_data->h_distance;
        }
        if (!correct_v && !ray_data[i].is_ver)
        {
            ray_data->is_ver = 1;
            ray_data->distance = ray_data->v_distance;
        }
        i++;
    }
}

void correct_rays(t_ray *rays_data)
{
    int i;
    int v_rays_cnt;
    int h_rays_cnt;
    double v_rays_prct;
    double h_rays_prct;

    v_rays_cnt = 0;
    h_rays_cnt = 0;
    i = 0;
    while (i < WINDOW_WIDTH)
    {
        v_rays_cnt += rays_data[i].is_ver;
        h_rays_cnt += !rays_data[i].is_ver;
        i++;
    }
    v_rays_prct = (v_rays_cnt * 100.0) / (double)WINDOW_WIDTH;
    h_rays_prct = (h_rays_cnt * 100.0) / (double)WINDOW_WIDTH;
    if (fmin(v_rays_prct, h_rays_prct) <= 1.0)
    {
        if (v_rays_cnt < h_rays_cnt)
            correction(rays_data, 1);
        else
            correction(rays_data, 0);
    }
}

void ray_cast(t_vars *vars)
{
    double current_angle;
    int i;
    t_ray *rays_data;

    rays_data = (t_ray*)malloc(sizeof(t_ray) * WINDOW_WIDTH);
    // check for malloc failure
    current_angle = vars->player_angle - (FOV / 2);
    i = 0;
    while(i < WINDOW_WIDTH)
    {
        current_angle = fmod(current_angle + 360, 360);
        vars->ray->h_distance = 1e6;
        vars->ray->v_distance = 1e6;
        vars->ray->angle = current_angle * M_PI / 180;
        // printf("--------------------------------------------------------------------------------\n");
        check_ray_direction(vars->ray);
        horizontal_ray_cast(vars);
        vertical_ray_cast(vars);
        // printf("v_x_inter: [%f] v_y_inter: [%f] dis: [%f]\n", vars->ray->v_x_intersection / TILE_SIZE, vars->ray->v_y_intersection / TILE_SIZE, vars->ray->v_distance);
        // printf("h_x_inter: [%f] h_y_inter: [%f] dis: [%f]\n", vars->ray->h_x_intersection / TILE_SIZE, vars->ray->h_y_intersection / TILE_SIZE, vars->ray->h_distance);
        min_distance(vars);
        copy_ray_data(vars, &rays_data[i]);
        // printf("hit_wall: x[%d] y[%d]\n", (int)(vars->ray->intersection_x / TILE_SIZE), (int)(vars->ray->intersection_y / TILE_SIZE));
        // printf("--------------------------------------------------------------------------------\n");
        // printf("ray_cast: [%d]\n", vars->is_v_ray_cast);
        // draw_3d(vars, i);
        i++;
        current_angle += FOV / (double)WINDOW_WIDTH;
    }
    correct_rays(rays_data);
    i = 0;
    while (i < WINDOW_WIDTH)
    {
        vars->ray->distance = rays_data[i].distance;
        vars->ray->angle = rays_data[i].angle;
        vars->is_v_ray_cast = rays_data[i].is_ver;
        vars->ray->is_down = rays_data[i].is_down;
        vars->ray->is_right = rays_data[i].is_right;
        draw_3d(vars, i);
        i++;
    }
    // exit(1);
}
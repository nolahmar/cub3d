/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:33:29 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/16 15:17:24 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map[MAP_WIDTH][MAP_HEIGHT] = {
/*0*/    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
/*1*/    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
/*2*/    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
/*3*/    {1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
/*4*/    {1, 0, 1, 0, 1, 2, 0, 1, 0, 1},
/*5*/    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
/*6*/    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
/*7*/    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
/*8*/    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void check_ray_direction(t_ray *ray)
{
    ray->is_down = 0;
    ray->is_right = 0;
    if (ray->angle > 0 && ray->angle < M_PI)
        ray->is_down = 1;
    if (ray->angle < M_PI_2 || ray->angle > (3 * M_PI) / 2)
        ray->is_right = 1;
}

int is_wall(double x, double y) 
{
    int tmp_x;
    int tmp_y;
    
    tmp_x = (int)(x / TILE_SIZE);
    tmp_y = (int)(y / TILE_SIZE);
    if (tmp_x >= 0 && tmp_x < MAP_WIDTH && tmp_y >= 0 && tmp_y < MAP_HEIGHT) {
        if (map[tmp_y][tmp_x] == 1)
            return 1;
        return 0;
    }
    return 2; 
}

void init(t_vars *vars)
{
    t_window_image *window_img;

    vars->ray = (t_ray*)malloc(sizeof(t_ray));
    window_img = (t_window_image*)malloc(sizeof(t_window_image));
    vars->txt_img = (t_texture_image*)malloc(sizeof(t_texture_image));
    vars->mlx = mlx_init();
    vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
    window_img->ptr = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    window_img->data = mlx_get_data_addr (window_img->ptr, &window_img->bits_per_pixel, \
        &window_img->size_line, &window_img->endian);
    vars->window_img = window_img;
    vars->player_x = (5 * TILE_SIZE) + (TILE_SIZE / 2);
    vars->player_y = (4 * TILE_SIZE) + (TILE_SIZE / 2);
    vars->player_angle = 10.0;
    vars->key_w = -1;
    vars->key_s = -1;
    vars->key_a = -1;
    vars->key_d = -1;
}

int main(void) {
    t_vars vars;

    init(&vars);
    mlx_hook(vars.win, 17, 0, close_window, &vars);
    mlx_hook(vars.win, 2, 0, key_press, &vars);
    mlx_hook(vars.win, 3, 0, key_release, &vars);
    mlx_loop_hook(vars.mlx, update, &vars);
    mlx_loop(vars.mlx);
    return (0);
}

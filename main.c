/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:33:29 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/06 18:52:29 by nolahmar         ###   ########.fr       */
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

int check_player_direction(t_vars *vars, int ray_cast_type)
{
    if (ray_cast_type == 1 && vars->player_angle >= 0 && vars->player_angle <= 180) //Player is facing down
        return (1);
    if (ray_cast_type == 1 && vars->player_angle >= 180 && vars->player_angle <= 360) //Player is facing up
        return (2);
    if (vars->player_angle >= 270 || vars->player_angle <= 90) //Player is facing rigth
        return (3);
    if (vars->player_angle >= 90 && vars->player_angle <= 270) //Player is facing left
        return (4);
    return (0);
}

int is_wall(t_vars *vars, double x, double y, int ray_cast_type) 
{
    int tmp_x;
    int tmp_y;
    
    if (x == vars->player_x && (check_player_direction(vars, ray_cast_type) == 4))
        x -= 1;
    if (y == vars->player_y && (check_player_direction(vars, ray_cast_type) == 2))
        x -= 1;
    tmp_x = (int)(x / TILE_SIZE);
    tmp_y = (int)(y / TILE_SIZE);
    if (tmp_x >= 0 && tmp_x < MAP_WIDTH && tmp_y >= 0 && tmp_y < MAP_HEIGHT) {
        return map[tmp_y][tmp_x];
    }
    return 2; 
}

int main(void) {
    t_vars vars;

    vars.ray = (t_ray*)malloc(sizeof(t_ray));
    // check if not ray
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
    vars.player_x = -1; // Position initiale du joueur
    vars.player_angle = 10.0; // Angle initial du joueur
    mlx_hook(vars.win, 17, 0, close_window, &vars);
    mlx_hook(vars.win, 2, 0, key_hook, &vars);
    mlx_clear_window(vars.mlx, vars.win);
    draw_map(&vars);
    draw_player(&vars);
    //horizontal_ray_cast(&vars, &ray);
    // vertical_ray_cast(&vars, ray);
    ray_cast(&vars);
    mlx_loop(vars.mlx);
    return (0);
}

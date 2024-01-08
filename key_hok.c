/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noni <noni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:30:21 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/08 21:32:15 by noni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_collision(double next_x, double next_y) {
    int tmp_x = (int)(next_x / TILE_SIZE);
    int tmp_y = (int)(next_y / TILE_SIZE);

    if (tmp_x >= 0 && tmp_x < MAP_WIDTH && tmp_y >= 0 && tmp_y < MAP_HEIGHT) {
        return map[tmp_y][tmp_x] == 1; // Return 1 if there is a wall at the next position
    }

    return 1; // Return 1 to indicate collision if the next position is outside the map
}

int close_window(void *param) {
    t_vars *vars = (t_vars *)param;

    free(vars->ray);
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
}

int key_hook(int keycode, t_vars *vars)
{
    double move_step = 5.0;
    double rotate_step = 2.0;

    if (keycode == 53) // Touche ESC pour quitter
        close_window(vars);

    // Gérer le déplacement du joueur avec rotation d'angle
    if (keycode == 13) // Touche W pour avancer
{
    double next_x = vars->player_x + move_step * cos(vars->player_angle * M_PI / 180);
    double next_y = vars->player_y + move_step * sin(vars->player_angle * M_PI / 180);

    if (!is_collision(next_x, next_y)) {
        vars->player_x = next_x;
        vars->player_y = next_y;
    }
}  
    else if (keycode == 1) // Touche S pour reculer
    {
     double move_angle = vars->player_angle + 180.0; // Calculate opposite direction angle
    double next_x = vars->player_x + move_step * cos(move_angle * M_PI / 180);
    double next_y = vars->player_y + move_step * sin(move_angle * M_PI / 180);

    if (!is_collision(next_x, next_y)) {
        vars->player_x = next_x;
        vars->player_y = next_y;
    }
    }
    else if (keycode == 0) // Touche A pour tourner à gauche
    {
        vars->player_angle -= rotate_step;
        if (vars->player_angle < 0)
            vars->player_angle += 360;
    }
    else if (keycode == 2) // Touche D pour tourner à droite
    {
        vars->player_angle += rotate_step;
        if (vars->player_angle >= 360)
            vars->player_angle -= 360;
    }
     if (vars->player_angle == 0 || vars->player_angle == 90
    || vars->player_angle == 180 || vars->player_angle == 270)
        vars->player_angle += 1e-3;
    //printf("Angle: %.2f\n", vars->player_angle);
    mlx_clear_window(vars->mlx, vars->win);
    draw_map(vars);
    draw_player(vars);
    //horizontal_ray_cast(vars, ray);
    // vertical_ray_cast(vars, ray);
    ray_cast(vars);
    return (0);
}
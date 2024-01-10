/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:30:21 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/10 16:39:13 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_window(void *param) {
    t_vars *vars = (t_vars *)param;

    free(vars->ray);
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
}

int key_hook(int keycode, t_vars *vars)
{
    double move_step = 10.0;
    double rotate_step = 10.0;

    if (keycode == 53) // Touche ESC pour quitter
        close_window(vars);

    // Gérer le déplacement du joueur avec rotation d'angle
    if (keycode == 13) // Touche W pour avancer
    {
        double next_x = vars->player_x + move_step * cos(vars->player_angle * M_PI / 180);
        double next_y = vars->player_y + move_step * sin(vars->player_angle * M_PI / 180);

        if (!is_wall(next_x, next_y)) {
            vars->player_x = next_x;
            vars->player_y = next_y;
        }
    }  
    else if (keycode == 1) // Touche S pour reculer
    {
     double move_angle = vars->player_angle + 180.0; // Calculate opposite direction angle
    double next_x = vars->player_x + move_step * cos(move_angle * M_PI / 180);
    double next_y = vars->player_y + move_step * sin(move_angle * M_PI / 180);

    if (!is_wall(next_x, next_y)) {
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:30:21 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/06 16:35:17 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_window(void *param) {
    t_vars *vars = (t_vars *)param;

    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
}

int key_hook(int keycode, t_vars *vars)
{
    double move_step = 5.0;
    double rotate_step = 3.0;

    if (keycode == 53) // Touche ESC pour quitter
        close_window(vars);

    // Gérer le déplacement du joueur avec rotation d'angle
    if (keycode == 13) // Touche W pour avancer
    {
        vars->player_x += move_step * cos(vars->player_angle * M_PI / 180);
        vars->player_y += move_step * sin(vars->player_angle * M_PI / 180);
    }
    else if (keycode == 1) // Touche S pour reculer
    {
        vars->player_x -= move_step * cos(vars->player_angle * M_PI / 180);
        vars->player_y -= move_step * sin(vars->player_angle * M_PI / 180);
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
    //printf("Angle: %.2f\n", vars->player_angle);
    mlx_clear_window(vars->mlx, vars->win);
    draw_map(vars);
    draw_player(vars);
    //horizontal_ray_cast(vars, ray);
    // vertical_ray_cast(vars, ray);
    ray_cast(vars);
    return (0);
}
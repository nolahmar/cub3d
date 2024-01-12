/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:30:21 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/12 13:40:20 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_window(void *param) {
    t_vars *vars = (t_vars *)param;

    free(vars->ray);
    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
}

int key_press(int keycode, t_vars *vars)
{
    if (keycode == KEY_ESC)
        close_window(vars);
    if (keycode == KEY_W)
    {
        vars->key_w = 1;
        if (!is_wall(vars->next_x, vars->next_y)) {
            vars->player_x = vars->next_x;
            vars->player_y = vars->next_y;
        }
    }  
    else if (keycode == KEY_S)
    {
        vars->key_s = 1;
        if (!is_wall(vars->next_x, vars->next_y)) 
        {
            vars->player_x = vars->next_x;
            vars->player_y = vars->next_y;
        }
    }
    else if (keycode == KEY_A)
        vars->key_a = 1;
    else if (keycode == KEY_D)
        vars->key_d = 1;
    return (0);
}

int key_release(int keycode, t_vars *vars)
{
    if (keycode == KEY_W)
        vars->key_w = -1;
    else if (keycode == KEY_S)
        vars->key_s = -1;
    else if (keycode == KEY_A)
        vars->key_a = -1;
    else if (keycode == KEY_D)
        vars->key_d = -1;
    return (0);
}

int update(t_vars *vars)
{
    double move_step = 10.0;
    double rotate_step = 10.0;
    
    if (vars->key_w == 1)
    {
        vars->next_x = vars->player_x + move_step * cos(vars->player_angle * M_PI / 180);
        vars->next_y = vars->player_y + move_step * sin(vars->player_angle * M_PI / 180);
    }
    if (vars->key_s == 1)
    {
        vars->move_angle = vars->player_angle + 180.0; // Calculate opposite direction angle
        vars->next_x = vars->player_x + move_step * cos(vars->move_angle * M_PI / 180);
        vars->next_y = vars->player_y + move_step * sin(vars->move_angle * M_PI / 180);
    }
    if (vars->key_a == 1)
    {
        vars->player_angle -= rotate_step;
        if (vars->player_angle < 0)
            vars->player_angle += 360;
    }
    if (vars->key_d == 1)
    {
        vars->player_angle += rotate_step;
        if (vars->player_angle >= 360)
            vars->player_angle -= 360;
    }
    if (vars->player_angle == 0 || vars->player_angle == 90
    || vars->player_angle == 180 || vars->player_angle == 270)
        vars->player_angle += 1e-3;
    mlx_clear_window(vars->mlx, vars->win);
    // draw_map(vars);
    // draw_player(vars);
    ray_cast(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->image->ptr, 0, 0);
    vars->key_w = -1;
    vars->key_s = -1;
    vars->key_a = -1;
    vars->key_d = -1;
    return (0);
}
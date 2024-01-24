/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:30:21 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/24 16:56:21 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == KEY_ESC)
		close_window(vars);
	if (keycode == KEY_W)
		vars->key_w = 1;
	else if (keycode == KEY_S)
		vars->key_s = 1;
	else if (keycode == KEY_GAUCHE)
		vars->key_gauche = 1;
	else if (keycode == KEY_DROIT)
		vars->key_droit = 1;
	else if (keycode == KEY_D)
		vars->key_d = 1;
	else if (keycode == KEY_A)
		vars->key_a = 1;
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
	if (keycode == KEY_W)
		vars->key_w = -1;
	else if (keycode == KEY_S)
		vars->key_s = -1;
	else if (keycode == KEY_GAUCHE)
		vars->key_gauche = -1;
	else if (keycode == KEY_DROIT)
		vars->key_droit = -1;
	else if (keycode == KEY_A)
		vars->key_a = -1;
	else if (keycode == KEY_D)
		vars->key_d = -1;
	return (0);
}

void	move_w_s(t_vars *vars)
{
	if (vars->key_w == 1)
	{
		vars->d_x = MOVE_STEP * cos(vars->player_angle * M_PI / 180);
		vars->d_y = MOVE_STEP * sin(vars->player_angle * M_PI / 180);
		vars->next_x = vars->player_x + vars->d_x;
		vars->next_y = vars->player_y + vars->d_y;
		if (!is_wall(vars, vars->player_x + (2 * vars->d_x), vars->player_y + (2 * vars->d_y)))
		{
			vars->player_x = vars->next_x;
			vars->player_y = vars->next_y;
		}
	}
	else if (vars->key_s == 1)
	{
		vars->d_x = -MOVE_STEP * cos(vars->player_angle * M_PI / 180);
		vars->d_y = -MOVE_STEP * sin(vars->player_angle * M_PI / 180);
		vars->next_x = vars->player_x + vars->d_x;
		vars->next_y = vars->player_y + vars->d_y;
		if (!is_wall(vars, vars->player_x + (2 * vars->d_x), vars->player_y + (2 * vars->d_y)))
		{
			vars->player_x = vars->next_x;
			vars->player_y = vars->next_y;
		}
	}
}

void	udapte_helper(t_vars *vars)
{
	move_w_s(vars);
	if (vars->key_d == 1)
	{
		vars->d_x = -MOVE_STEP * cos((vars->player_angle - 90) * M_PI / 180);
		vars->d_y = -MOVE_STEP * sin((vars->player_angle - 90) * M_PI / 180);
		vars->next_x = vars->player_x + vars->d_x;
		vars->next_y = vars->player_y + vars->d_y;
		if (!is_wall(vars, vars->player_x + (2 * vars->d_x), vars->player_y + (2 * vars->d_y)))
		{
			vars->player_x = vars->next_x;
			vars->player_y = vars->next_y;
		}
	}
	else if (vars->key_a == 1)
	{
		vars->d_x = MOVE_STEP * cos((vars->player_angle - 90) * M_PI / 180);
		vars->d_y = MOVE_STEP * sin((vars->player_angle - 90) * M_PI / 180);
		vars->next_x = vars->player_x + vars->d_x;
		vars->next_y = vars->player_y + vars->d_y;
		if (!is_wall(vars, vars->player_x + (2 * vars->d_x), vars->player_y + (2 * vars->d_y)))
		{
			vars->player_x = vars->next_x;
			vars->player_y = vars->next_y;
		}
	}
}

int	update(t_vars *vars)
{
	udapte_helper(vars);
	if (vars->key_gauche == 1)
	{
		vars->player_angle -= ROTATE_STEP;
		if (vars->player_angle < 0)
			vars->player_angle += 360;
	}
	else if (vars->key_droit == 1)
	{
		vars->player_angle += ROTATE_STEP;
		if (vars->player_angle >= 360)
			vars->player_angle -= 360;
	}
	if (vars->player_angle == 0 || vars->player_angle == 90
		|| vars->player_angle == 180 || vars->player_angle == 270)
		vars->player_angle += 1e-3;
	mlx_clear_window(vars->mlx, vars->win);
	ray_cast(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->window_img->ptr, 0, 0);
	return (0);
}

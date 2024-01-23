/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:23:11 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/23 16:22:42 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	close_window(t_vars *vars)
{
	free(vars->ray);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	rgb_to_int(int r, int g, int b)
{
	int	result;

	result = (r << 16) | (g << 8) | (b);
	return (result);
}

void	put_pixel(t_vars *vars, int x, int y, int color)
{
	char	*offset;
	int		val;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		val = (y * vars->window_img->size_line) + (x * 4);
		offset = vars->window_img->data + val;
		*(unsigned int *)offset = color;
	}
}

void	draw_3d(t_vars *vars, int x)
{
	int		y;
	double	beta;

	beta = (vars->player_angle * M_PI / 180) - vars->ray->angle;
	y = -1;
	vars->ray->distance *= cos(beta);
	vars->dst_to_plane = (WINDOW_WIDTH / 2) / tan((FOV / 2) * M_PI / 180);
	vars->wall_height = (TILE_SIZE / vars->ray->distance) * vars->dst_to_plane;
	vars->start_wall = (WINDOW_HEIGHT / 2) - (vars->wall_height / 2);
	vars->end_wall = (WINDOW_HEIGHT / 2) + (vars->wall_height / 2);
	while (++y < vars->start_wall)
		put_pixel(vars, x, y, rgb_to_int(vars->data->ceilcolor.red, \
		vars->data->ceilcolor.green, vars->data->ceilcolor.blue));
	y = vars->end_wall - 1;
	while (++y < WINDOW_HEIGHT)
		put_pixel(vars, x, y, rgb_to_int(vars->data->floorcolor.red, \
		vars->data->floorcolor.green, vars->data->floorcolor.blue));
	y = vars->start_wall - 1;
	texture(vars, x);
}

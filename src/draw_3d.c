/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:23:11 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/22 11:23:48 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
		put_pixel(vars, x, y, 0xADD8E6);
	y = vars->end_wall - 1;
	while (++y < WINDOW_HEIGHT)
		put_pixel(vars, x, y, 0xFFC7C7);
	y = vars->start_wall - 1;
	texture(vars, x);
}

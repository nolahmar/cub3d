/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 18:23:11 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/12 18:45:03 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    put_pixel(t_vars *vars, int x, int y, int color)
{
    char    *offset;

    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
    {
        offset = vars->image->data + (y * vars->image->size_line) + (x * 4);
        *(unsigned int*)offset = color;
    }
}

void    draw_3d(t_vars *vars, int x)
{
    int     y;
    double  beta;
   
    beta = (vars->player_angle * RED) - vars->ray->angle;
    y = -1;
    vars->ray->distance *= cos(beta);
    vars->dst_to_plane = (WINDOW_WIDTH / 2) / tan((FOV / 2) * RED);
    vars->wall_height = (TILE_SIZE / vars->ray->distance) * vars->dst_to_plane;
    vars->start_wall = (WINDOW_HEIGHT / 2) - (vars->wall_height / 2);
    vars->end_wall = (WINDOW_HEIGHT / 2) + (vars->wall_height / 2);
    while (++y < vars->start_wall)
        put_pixel(vars, x, y, 0xADD8E6);
    y = vars->end_wall - 1;
    while (++y < WINDOW_HEIGHT)
        put_pixel(vars, x, y, 0xFFC7C7);
    y = vars->start_wall - 1;
    while (++y <= vars->end_wall)
        put_pixel(vars, x, y, 0xFF0060);
}

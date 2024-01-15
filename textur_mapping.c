/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textur_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:41:35 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/15 17:03:14 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int get_pixel_color(t_vars *vars, int offset_x, int offset_y)
{
    char *image_data;
    int bit_par_pixel;
    int size_line;
    int pixel_index;
    unsigned int color;
    
     image_data = vars->image->ptr;
     bit_par_pixel = vars->image->bits_per_pixel / 8;
     size_line = vars->image->size_line; 
     pixel_index = offset_y * size_line + offset_x * bit_par_pixel;
     color = *((unsigned int *)(image_data + pixel_index));
     return (color);
}

void texture(t_vars *vars, int top, int bottom, int x)
{
    int y;
    int offset_x;
    int offset_y;
    unsigned int texel;

    if (vars->is_v_ray_cast == 1)
        offset_x = (int)vars->ray[x].v_distance % TILE_SIZE;
    else
        offset_y = (int)vars->ray[x].h_distance % TILE_SIZE;
    y = top;
    while (y < bottom)
    {
       texel = get_pixel_color(vars, offset_x, offset_y);
        put_pixel(vars, x, y, texel);
        y++;
    }   
}
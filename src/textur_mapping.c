/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textur_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:41:35 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/17 14:51:24 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int load_tex(t_vars *vars, char *path)
{
    t_texture_image *image;
    
    image = vars->txt_img;
    if (path)
    {
        if ((image->ptr = mlx_xpm_file_to_image(vars->mlx, path, &image->width, &image->height)))
            image->data = mlx_get_data_addr(image->ptr, &image->bits_per_pixel, &image->size_line, &image->endian);
        else
            return (0);
    }
    return (1);
}


void texture(t_vars *vars, int x)
{
    int y;
    int offset_x;
    double offset_y;
    unsigned int texel;
    double y_step;
    int *data;
    int pixel_index;

    y_step = vars->txt_img->height / (double)(vars->end_wall - vars->start_wall);
    offset_y = 0;
    if (vars->is_v_ray_cast == 1)
        offset_x = (int)vars->ray->intersection_y % TILE_SIZE;
    else
        offset_x = (int)vars->ray->intersection_x % TILE_SIZE;
    data = (int*)vars->txt_img->data;
    y = vars->start_wall;
    while (y <= vars->end_wall)
    {
        pixel_index = (int)((int)offset_y * vars->txt_img->width + offset_x);
        if (pixel_index < vars->txt_img->width * vars->txt_img->height)
            texel = data[pixel_index];
        put_pixel(vars, x, y, texel);
        y++;
        offset_y += y_step;
    }   
}
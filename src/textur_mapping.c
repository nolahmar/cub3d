/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textur_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:41:35 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/18 16:36:24by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int load_tex(t_vars *vars)
{
    t_GlobaleData *data;

    data = vars->data;
    if ((data->east->ptr = mlx_xpm_file_to_image(vars->mlx, data->east->path, &data->east->width, &data->east->height)))
        data->east->data = mlx_get_data_addr(data->east->ptr, &data->east->bits_per_pixel, &data->east->size_line, &data->east->endian);
    else
        return (0);
    if ((data->west->ptr = mlx_xpm_file_to_image(vars->mlx, data->west->path, &data->west->width, &data->west->height)))
        data->west->data = mlx_get_data_addr(data->west->ptr, &data->west->bits_per_pixel, &data->west->size_line, &data->west->endian);
    else
        return (0);
    if ((data->south->ptr = mlx_xpm_file_to_image(vars->mlx, data->south->path, &data->south->width, &data->south->height)))
        data->south->data = mlx_get_data_addr(data->south->ptr, &data->south->bits_per_pixel, &data->south->size_line, &data->south->endian);
    else
        return (0);
    if ((data->north->ptr = mlx_xpm_file_to_image(vars->mlx, data->north->path, &data->north->width, &data->north->height)))
        data->north->data = mlx_get_data_addr(data->north->ptr, &data->north->bits_per_pixel, &data->north->size_line, &data->north->endian);
    else
        return (0);
    return (1);
}

t_Texture *get_texture_data(t_vars *vars)
{
    if (!vars->is_v_ray_cast && !vars->ray->is_down)
        return vars->data->north;
    if (vars->is_v_ray_cast && vars->ray->is_right)
        return vars->data->east;
    if (!vars->is_v_ray_cast && vars->ray->is_down)
        return vars->data->south;
    return vars->data->west;
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
    t_Texture *txt_imag;

    txt_imag = get_texture_data(vars);
    y_step = txt_imag->height / (double)(vars->end_wall - vars->start_wall);
    offset_y = 0;
    if (vars->is_v_ray_cast == 1)
        offset_x = (int)vars->ray->intersection_y % TILE_SIZE;
    else
        offset_x = (int)vars->ray->intersection_x % TILE_SIZE;
    data = (int*)txt_imag->data;
    y = vars->start_wall;
    while (y <= vars->end_wall)
    {
        pixel_index = (int)((int)offset_y * txt_imag->width + offset_x);
        if (pixel_index < txt_imag->width * txt_imag->height)
            texel = data[pixel_index];
        put_pixel(vars, x, y, texel);
        y++;
        offset_y += y_step;
    }   
}
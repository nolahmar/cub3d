/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textur_mapping.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:08:10 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/22 14:12:18 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	loed_tex_helper(t_vars *vars, t_GlobaleData *data)
{
	data = vars->data;
	data->east->ptr = mlx_xpm_file_to_image
		(vars->mlx, data->east->path, &data->east->width, &data->east->height);
	if (data->east->ptr)
		data->east->data = mlx_get_data_addr
			(data->east->ptr, &data->east->bits_per_pixel, \
				&data->east->size_line, &data->east->endian);
	else
		return (0);
	data->west->ptr = mlx_xpm_file_to_image
		(vars->mlx, data->west->path, &data->west->width, &data->west->height);
	if (data->west->ptr)
		data->west->data = mlx_get_data_addr
			(data->west->ptr, &data->west->bits_per_pixel, \
				&data->west->size_line, &data->west->endian);
	else
		return (0);
	return (1);
}

int	load_tex(t_vars *vars)
{
	t_GlobaleData	*data;

	data = vars->data;
	loed_tex_helper(vars, data);
	data->south->ptr = mlx_xpm_file_to_image
		(vars->mlx, data->south->path, &data->south->width, \
			&data->south->height);
	if (data->south->ptr)
		data->south->data = mlx_get_data_addr
			(data->south->ptr, &data->south->bits_per_pixel, \
				&data->south->size_line, &data->south->endian);
	else
		return (0);
	data->north->ptr = mlx_xpm_file_to_image
		(vars->mlx, data->north->path, \
			&data->north->width, &data->north->height);
	if (data->north->ptr)
		data->north->data = mlx_get_data_addr
			(data->north->ptr, &data->north->bits_per_pixel, \
				&data->north->size_line, &data->north->endian);
	else
		return (0);
	return (1);
}

t_Texture	*get_texture_data(t_vars *vars)
{
	if (!vars->is_v_ray_cast && !vars->ray->is_down)
		return (vars->data->north);
	if (vars->is_v_ray_cast && vars->ray->is_right)
		return (vars->data->east);
	if (!vars->is_v_ray_cast && vars->ray->is_down)
		return (vars->data->south);
	return (vars->data->west);
}

void	texture(t_vars *vars, int x)
{
	int				y;
	unsigned int	texel;
	int				*data;
	t_Texture		*txt_imag;

	txt_imag = get_texture_data(vars);
	vars->y_step = txt_imag->height / (double)(vars->end_wall \
		- vars->start_wall);
	vars->offset_y = 0;
	if (vars->is_v_ray_cast == 1)
		vars->offset_x = (int)vars->ray->intersection_y % TILE_SIZE;
	else
		vars->offset_x = (int)vars->ray->intersection_x % TILE_SIZE;
	data = (int *)txt_imag->data;
	y = vars->start_wall;
	while (y <= vars->end_wall)
	{
		vars->pixel_index = (int)((int)vars->offset_y * txt_imag->width \
			+ vars->offset_x);
		if (vars->pixel_index < txt_imag->width * txt_imag->height)
			texel = data[vars->pixel_index];
		put_pixel(vars, x, y, texel);
		y++;
		vars->offset_y += vars->y_step;
	}
}

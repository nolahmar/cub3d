/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:13:38 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/26 14:20:03 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_map_line(t_MapLine *lines)
{
	t_MapLine	*tmp;

	while (lines)
	{
		tmp = lines->next;
		free(lines);
		lines = tmp;
	}
}

void	free_map_data(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		++i;
	}
	free(data);
}

int	close_window(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->window_img->ptr);
	free(vars->data->north->path);
	free(vars->data->south->path);
	free(vars->data->east->path);
	free(vars->data->west->path);
	free_map_line(vars->data->mapline);
	free_map_data(vars->data->map.data);
	free_map_data(vars->data->file_content);
	free(vars->window_img);
	free(vars->data);
	free(vars->ray);
	mlx_destroy_window(vars->mlx, vars->win);
	system("leaks Cub3d");
	exit(0);
}

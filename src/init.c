/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:46:35 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/23 16:23:36 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_helper(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		print_error("Error\nInitializing mlx\n", 1);
	load_tex(vars);
	vars->win = mlx_new_window(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (vars->win == NULL)
		print_error("Error\nCreating window with mlx_new_window\n", 1);
}

void	init_player(t_vars *vars, t_GlobaleData *data)
{
	vars->player_x = (data->playerposition.x * TILE_SIZE) + (TILE_SIZE / 2);
	vars->player_y = (data->playerposition.y * TILE_SIZE) + (TILE_SIZE / 2);
	vars->player_angle = data->playerposition.angle;
}

void	init(t_vars *vars, int ac, char **av)
{
	t_window_image	*window_img;
	t_GlobaleData	*data;

	data = (t_GlobaleData *)malloc(sizeof(t_GlobaleData));
	if (data == NULL)
		print_error("Error\nAllocating memory for t_GlobaleData\n", 1);
	parse(ac, av, data);
	vars->data = data;
	vars->ray = (t_ray *)malloc(sizeof(t_ray));
	if (vars->ray == NULL)
		print_error("Error\nAllocating memory for t_ray\n", 1);
	window_img = (t_window_image *)malloc(sizeof(t_window_image));
	if (window_img == NULL)
		print_error("Error\nAllocating memory for t_window_image\n", 1);
	init_helper(vars);
	window_img->ptr = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (window_img->ptr == NULL)
		print_error("Error\nCreating image with mlx_new_image\n", 1);
	window_img->data = mlx_get_data_addr
		(window_img->ptr, &window_img->bits_per_pixel, \
			&window_img->size_line, &window_img->endian);
	if (window_img == NULL)
		print_error("Error\nGetting image data\n", 1);
	vars->window_img = window_img;
	init_player(vars, data);
}

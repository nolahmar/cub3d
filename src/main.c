/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 11:55:20 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/24 11:56:15 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_ray_direction(t_ray *ray)
{
	ray->is_down = 0;
	ray->is_right = 0;
	if (ray->angle > 0 && ray->angle < M_PI)
		ray->is_down = 1;
	if (ray->angle <= M_PI_2 || ray->angle >= (3 * M_PI) / 2)
		ray->is_right = 1;
}

int	is_wall(t_vars *vars, double x, double y)
{
	int		tmp_x;
	int		tmp_y;
	t_Map	*map;

	map = &vars->data->map;
	tmp_x = (int)(x / TILE_SIZE);
	tmp_y = (int)(y / TILE_SIZE);
	if (tmp_x >= 0 && tmp_x < map->width && tmp_y >= 0 && tmp_y < map->height)
	{
		if (map->data[tmp_y][tmp_x] == '1')
			return (1);
		return (0);
	}
	return (2);
}

int	main(int ac, char **av)
{
	t_vars	vars;

	init(&vars, ac, av);
	mlx_hook(vars.win, 17, 0, close_window, &vars);
	mlx_hook(vars.win, 2, 0, key_press, &vars);
	mlx_hook(vars.win, 3, 0, key_release, &vars);
	mlx_loop_hook(vars.mlx, update, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

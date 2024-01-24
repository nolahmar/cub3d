/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:02:24 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/24 17:28:29 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	min_distance(t_vars *vars)
{
	if (vars->ray->h_distance < vars->ray->v_distance)
	{
		vars->is_v_ray_cast = 0;
		vars->ray->intersection_x = vars->ray->h_x_intersection;
		vars->ray->intersection_y = vars->ray->h_y_intersection;
		vars->ray->distance = vars->ray->h_distance;
	}
	else
	{
		vars->is_v_ray_cast = 1;
		vars->ray->intersection_x = vars->ray->v_x_intersection;
		vars->ray->intersection_y = vars->ray->v_y_intersection;
		vars->ray->distance = vars->ray->v_distance;
	}
}

void	copy_ray_data(t_vars *vars, t_ray *ray_copy)
{
	ray_copy->angle = vars->ray->angle;
	ray_copy->h_distance = vars->ray->h_distance;
	ray_copy->v_distance = vars->ray->v_distance;
	ray_copy->distance = vars->ray->distance;
	ray_copy->intersection_x = vars->ray->intersection_x;
	ray_copy->intersection_y = vars->ray->intersection_y;
	ray_copy->h_x_intersection = vars->ray->h_x_intersection;
	ray_copy->h_y_intersection = vars->ray->h_y_intersection;
	ray_copy->v_x_intersection = vars->ray->v_x_intersection;
	ray_copy->v_y_intersection = vars->ray->v_y_intersection;
	ray_copy->is_ver = vars->is_v_ray_cast;
	ray_copy->is_down = vars->ray->is_down;
	ray_copy->is_right = vars->ray->is_right;
}

void	ray_cast_corr(t_vars *vars, t_ray *rays_data)
{
	int	i;

	correct_rays(rays_data);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		vars->ray->distance = rays_data[i].distance;
		vars->ray->angle = rays_data[i].angle;
		vars->is_v_ray_cast = rays_data[i].is_ver;
		vars->ray->is_down = rays_data[i].is_down;
		vars->ray->is_right = rays_data[i].is_right;
		vars->ray->intersection_x = rays_data[i].intersection_x;
		vars->ray->intersection_y = rays_data[i].intersection_y;
		draw_3d(vars, i);
		i++;
	}
	free(rays_data);
}

void	ray_cast(t_vars *vars)
{
	double	current_angle;
	int		i;
	t_ray	*rays_data;

	rays_data = (t_ray *)malloc(sizeof(t_ray) * WINDOW_WIDTH);
	if (rays_data == NULL)
		print_error("Error\nAllocating memory for t_ray\n", 1);
	current_angle = vars->player_angle - (FOV / 2);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		current_angle = fmod(current_angle + 360, 360);
		vars->ray->h_distance = 1e6;
		vars->ray->v_distance = 1e6;
		vars->ray->angle = current_angle * M_PI / 180;
		check_ray_direction(vars->ray);
		horizontal_ray_cast(vars);
		vertical_ray_cast(vars);
		min_distance(vars);
		copy_ray_data(vars, &rays_data[i]);
		i++;
		current_angle += FOV / (double)WINDOW_WIDTH;
	}
	ray_cast_corr(vars, rays_data);
}

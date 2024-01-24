/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corr_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:41:07 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/24 17:48:32 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	v_correction(t_ray *rays_data, int start_index)
{
	int	i;

	i = start_index;
	while (i >= 0 && rays_data[i].is_ver)
	{
        if ((int)fabs(rays_data[i].h_distance - rays_data[i].v_distance) <= 5)
        {
            rays_data[i].is_ver = 0;
            rays_data[i].distance = rays_data[i].h_distance;
            rays_data[i].intersection_x = rays_data[i].h_x_intersection;
            rays_data[i].intersection_y = rays_data[i].h_y_intersection;
        }
		i--;
	}
}

void	h_correction(t_ray *rays_data, int start_index)
{
	int	i;

	i = start_index;
	while (i >= 0 && !rays_data[i].is_ver)
	{
        if ((int)fabs(rays_data[i].h_distance - rays_data[i].v_distance) <= 5)
        {
            rays_data[i].is_ver = 1;
            rays_data[i].distance = rays_data[i].v_distance;
            rays_data[i].intersection_x = rays_data[i].v_x_intersection;
            rays_data[i].intersection_y = rays_data[i].v_y_intersection;
        }
		i--;
	}
}

void	vertical_correction(t_ray *rays_data)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (i < WINDOW_WIDTH)
	{
		if (rays_data[i].is_ver)
			cnt++;
		else if (cnt > 0)
		{
			if (cnt < 30)
				v_correction(rays_data, i - 1);
			cnt = 0;
		}
		i++;
	}
}

void	horizontal_correction(t_ray *rays_data)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (i < WINDOW_WIDTH)
	{
		if (!rays_data[i].is_ver)
			cnt++;
		else if (cnt > 0)
		{
			if (cnt < 30)
				h_correction(rays_data, i - 1);
			cnt = 0;
		}
		i++;
	}
}

void	correct_rays(t_ray *rays_data)
{
	vertical_correction(rays_data);
	horizontal_correction(rays_data);
}
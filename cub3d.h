/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:16:55 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/15 17:02:03 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>

# define MAP_WIDTH 10
# define MAP_HEIGHT 10
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define TILE_SIZE 64
# define FOV 60
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_GAUCHE 123
# define KEY_DROIT 124
# define KEY_ESC 53
# define MOVE_STEP 10
# define ROTATE_STEP 10

extern int  map[MAP_WIDTH][MAP_HEIGHT];

typedef struct s_ray
{
	double	angle;
	double	intersection_x;
	double	intersection_y;
	double	ya;
	double	xa;
	double	distance;
	double	h_x_intersection;
	double	h_y_intersection;
	double	h_distance;
	double	v_x_intersection;
	double	v_y_intersection;
	double	v_distance;
	int		is_down;
	int		is_right;
}	t_ray;	
typedef struct s_image
{
	void	*ptr;
	char	*data;
	int32_t	bits_per_pixel;
	int32_t	size_line;
	int32_t	endian;
}	t_image;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	double	player_x;
	double	player_y;
	double	next_x;
	double	next_y;
	double	delta_x;
	double	delta_y;
	double	move_angle;
	double	start_wall;
	double	end_wall;
	double	dst_to_plane;
	double	wall_height;
	double	player_angle;
	int		key_w;
	int		key_s;
	int		key_a;
	int		key_d;
	int		key_gauche;
	int		key_droit;
	int		is_v_ray_cast;
	t_ray	*ray;
	t_image	*image;
}	t_vars;

void	horizontal_ray_cast(t_vars *vars);
void	vertical_ray_cast(t_vars *vars);
int		close_window(void *param);
int		key_press(int keycode, t_vars *vars);
int		key_release(int keycode, t_vars *vars);
void	check_ray_direction(t_ray *ray);
int		is_wall(double x, double y);
void	ray_cast(t_vars *vars);
int		update(t_vars *vars);
void	draw_3d(t_vars *vars, int x);
void texture(t_vars *vars, int top, int bottom, int x);
void    put_pixel(t_vars *vars, int x, int y, int color);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:16:55 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/11 15:57:53 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_HPP
# define CUB3D_HPP

#include <stdlib.h>
# include <mlx.h>
#include <math.h>
#include <stdio.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define TILE_SIZE 64
#define FOV 60

extern int map[MAP_WIDTH][MAP_HEIGHT];

typedef struct s_ray {
    double angle;
    double intersection_x;
    double intersection_y;
    double ya;
    double xa;
    double distance;
    double h_x_intersection;
    double h_y_intersection;
    double h_distance;
    double v_x_intersection;
    double v_y_intersection;
    double v_distance;
    double distance_to_projection_plane;
    int     is_down;
    int     is_right;
} t_ray;

typedef struct s_vars {
    void *mlx;
    void *win;
    void *image;
    double player_x;
    double player_y;
    double next_x;
    double next_y;
    double move_angle;
    double  player_angle;
    int     key_w;
    int     key_s;
    int     key_a;
    int     key_d;
    t_ray *ray;
} t_vars;

void draw_map(t_vars *vars);
void draw_player(t_vars *vars);
void drawline(t_vars *vars, int x1, int y1, int color);
int close_window(void *param);
int key_hook(int keycode, t_vars *vars);
void check_ray_direction(t_ray *ray);
int is_wall(double x, double y);
// t_ray   initialize_ray(double x, double y, double angle);
void horizontal_ray_cast(t_vars *vars);
// void vertical_ray_cast(t_vars *vars);
void ray_cast(t_vars *vars);
int update(t_vars *vars);

#endif

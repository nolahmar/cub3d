/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wind.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 11:27:34 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/05 14:55:42 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <stdio.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10 

int map[MAP_WIDTH][MAP_HEIGHT] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 1, 0, 1, 0, 1},
    {1, 0, 1, 0, 1, 2, 0, 1, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

typedef struct s_vars {
    void *mlx;
    void *win;
    double player_x;
    double player_y;
    double  player_angle;
} t_vars;

void draw_map(t_vars *vars) {
    int wall_color = 0x0000FF;
    int square_size = 64;

    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            if (map[i][j] == 1) {
                for (int y = i * square_size; y < (i + 1) * square_size; ++y) {
                    for (int x = j * square_size; x < (j + 1) * square_size; ++x) {
                        mlx_pixel_put(vars->mlx, vars->win, x, y, wall_color);
                    }
                }
            }
            else if (map[i][j] == 2 && vars->player_x == -1) {
                vars->player_x = (j * 64) + 32;
                vars->player_y = (i * 64) + 32;
            }
        }
    }
}

void draw_player(t_vars *vars) {
    int size = 5; 
    int color = 0xFFFFFF;
    double x;
    double y;
    
   for (int angle = 0; angle <= 360; angle++) {
        x = (vars->player_x + size * cos(angle * M_PI / 180));
        y = (vars->player_y + size * sin(angle * M_PI / 180));
        mlx_pixel_put(vars->mlx, vars->win, x, y, color);
    }
}

int close_window(void *param) {
    t_vars *vars = (t_vars *)param;

    mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
}

int is_wall(int x, int y) 
{
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        return map[y][x];
    }
    return 2; 
}

void drawline(t_vars *vars, int X1, int Y1) 
{ 
    int X0 = vars->player_x;
    int Y0 = vars->player_y;
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float)steps; 
    float Yinc = dy / (float)steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) { 
        // putpixel(round(X), round(Y), 
        //          RED); // put pixel at (X,Y)
        mlx_pixel_put(vars->mlx, vars->win, X, Y, 0xFF0000);
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
        // delay(100); // for visualization of line- 
        //             // generation step by step 
    } 
} 

int check_player_direction(t_vars *vars)
{
    double angle;
    
    angle = vars->player_angle;
    if (angle >= 0 && angle <= 180) //Player is facing down
        return (1);
    if (angle >= 180 && angle <= 360) //Player is facing up
        return (2);
    if (angle >= 270 && angle <= 90) //Player is facing rigth
        return (3);
    if (angle >= 90 && angle <= 270) //Player is facing left
        return (4);
    return (0);
}

void horizontal_ray_cast(t_vars *vars)
{
    double ray_x;
    double ray_y;
    double angle;
    double intersection_x;
    double intersection_y;
    double ya;
    double xa;
    double distance_horizontal;

    ray_x = vars->player_x;
    ray_y = vars->player_y;
    if (vars->player_angle == 90 || vars->player_angle == 270
        || vars->player_angle == 180 || vars->player_angle == 360)
        vars->player_angle += 1e-10;
    //printf("player_angle[%f]\n", vars->player_angle);
    angle = vars->player_angle * M_PI / 180.0;
    // this if the player is facing up
    if (check_player_direction(vars) == 2)
    {
        intersection_y = floor(ray_y / 64) * 64 - 1;
        ya = -64;
        intersection_x = ray_x + (ray_y - intersection_y) / -tan(angle);
        xa = 64.0 / -(double)tan(angle);
    }
    // if the player is facing down
    if (check_player_direction(vars) == 1)
    {
        intersection_y = floor(ray_y / 64) * 64 + 64;
        ya = 64;
        intersection_x = ray_x + (ray_y - intersection_y) / tan(angle);
        xa = 64.0 / (double)tan(angle);
    }

    distance_horizontal = 0.0;
    while (!is_wall((int)(intersection_x / 64), (int)(intersection_y / 64)))
    {
        intersection_x += xa;
        intersection_y += ya;
    }
    distance_horizontal = sqrt(pow(vars->player_x - intersection_x, 2) + pow(vars->player_y - intersection_y, 2));
    // int tmp_x = (int)(intersection_x / 64);
    // int tmp_y = (int)(intersection_y / 64);
    // printf("x_intersection[%f] y_intersection[%f]\n", intersection_x, intersection_y);
    if (intersection_x >= 0 && intersection_x < 800 && intersection_y >= 0 && intersection_y < 600)
    {
        mlx_pixel_put(vars->mlx, vars->win, intersection_x, intersection_y, 0xFF9800);
        drawline(vars, intersection_x, intersection_y);
    }
}

void vertical_ray_cast(t_vars *vars)
{
    double ray_x;
    double ray_y;
    double angle;
    double intersection_x;
    double intersection_y;
    double xa;
    double ya;
    double distance_vertical;

    ray_x = vars->player_x;
    ray_y = vars->player_y;
    angle = vars->player_angle * M_PI / 180.0;

    // Player is facing right
    if (check_player_direction(vars) == 3)
    {
        intersection_x = floor(ray_x / 64) * 64 + 64;
        xa = 64.0;
    }
    // Player is facing left
    if (check_player_direction(vars) == 4)
    {
        intersection_x = floor(ray_x / 64) * 64 - 1;
        xa = -64.0;
    }
    intersection_y = ray_y + (ray_x - intersection_x) * tan(angle);
    ya = 64.0 * (double)tan(angle);

    distance_vertical = 0.0;
    while (!is_wall((int)(intersection_x / 64), (int)(intersection_y / 64)))
    {
        intersection_x += xa;
        intersection_y += ya;
    }
    distance_vertical = sqrt(pow(vars->player_x - intersection_x, 2) + pow(vars->player_y - intersection_y, 2));
    drawline(vars, intersection_x, intersection_y);
}

int key_hook(int keycode, t_vars *vars)
{
    double move_step = 5.0;
    double rotate_step = 5.0;

    if (keycode == 53) // Touche ESC pour quitter
        close_window(vars);

    // Gérer le déplacement du joueur avec rotation d'angle
    if (keycode == 13) // Touche W pour avancer
    {
        vars->player_x += move_step * cos(vars->player_angle * M_PI / 180);
        vars->player_y += move_step * sin(vars->player_angle * M_PI / 180);
    }
    else if (keycode == 1) // Touche S pour reculer
    {
        vars->player_x -= move_step * cos(vars->player_angle * M_PI / 180);
        vars->player_y -= move_step * sin(vars->player_angle * M_PI / 180);
    }
    else if (keycode == 0) // Touche A pour tourner à gauche
    {
        vars->player_angle -= rotate_step;
        if (vars->player_angle < 0)
            vars->player_angle += 360;
    }
    else if (keycode == 2) // Touche D pour tourner à droite
    {
        vars->player_angle += rotate_step;
        if (vars->player_angle >= 360)
            vars->player_angle -= 360;
    }
    //printf("Angle: %.2f\n", vars->player_angle);
    mlx_clear_window(vars->mlx, vars->win);
    draw_map(vars);
    draw_player(vars);
    //horizontal_ray_cast(vars);
    vertical_ray_cast(vars);
    return (0);
}

int main(void) {
    t_vars vars;
    
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 800, 600, "Cub3D");
    vars.player_x = -1; // Position initiale du joueur
    vars.player_angle = 270.0; // Angle initial du joueur
    mlx_hook(vars.win, 17, 0, close_window, &vars);
    mlx_hook(vars.win, 2, 0, key_hook, &vars);
    mlx_clear_window(vars.mlx, vars.win);
    draw_map(&vars);
    draw_player(&vars);
    //horizontal_ray_cast(&vars);
    vertical_ray_cast(&vars);
    mlx_loop(vars.mlx);
    return (0);
}

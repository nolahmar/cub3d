/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wind.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 11:27:34 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/06 18:35:09 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
                vars->player_x = (j * TILE_SIZE) + (TILE_SIZE / 2);
                vars->player_y = (i * TILE_SIZE) + (TILE_SIZE / 2);
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

void drawline(t_vars *vars, int X1, int Y1, int color) 
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
        mlx_pixel_put(vars->mlx, vars->win, X, Y, color);
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
        // delay(100); // for visualization of line- 
        //             // generation step by step 
    } 
} 

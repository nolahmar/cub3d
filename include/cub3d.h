/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:16:55 by nolahmar          #+#    #+#             */
/*   Updated: 2024/01/26 14:30:14 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include "../mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"

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
# define MOVE_STEP 8
# define ROTATE_STEP 5
# define MAX_LINE_LENGTH 256

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
	int		is_ver;
}	t_ray;

typedef struct s_window_image
{
	void	*ptr;
	char	*data;
	int32_t	bits_per_pixel;
	int32_t	size_line;
	int32_t	endian;
}	t_window_image;

typedef struct MapLine
{
	char			*content;
	struct MapLine	*next;
}	t_MapLine;

typedef struct Texture
{
	char	*path;
	int		width;
	int		height;
	void	*ptr;
	char	*data;
	int32_t	bits_per_pixel;
	int32_t	size_line;
	int32_t	endian;
}	t_Texture;

typedef struct Position
{
	int		x;
	int		y;
	double	angle;
}	t_Position;

typedef struct Map
{
	char		**data;
	int			width;
	int			height;
}	t_Map;

typedef struct Color
{
	int	red;
	int	green;
	int	blue;
}	t_Color;

typedef struct GlobaleData
{
	t_Texture	*north;
	t_Texture	*south;
	t_Texture	*east;
	t_Texture	*west;
	void		*mlx;
	void		*win;
	char		**file_content;
	t_Color		floorcolor;
	t_Color		ceilcolor;
	t_Map		map;
	t_MapLine	*mapline;
	t_Position	playerposition;
}	t_GlobaleData;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	double			player_x;
	double			player_y;
	double			next_x;
	double			next_y;
	double			d_x;
	double			d_y;
	double			move_angle;
	double			start_wall;
	double			end_wall;
	double			dst_to_plane;
	double			wall_height;
	double			player_angle;
	double			y_step;
	double			offset_y;
	int				offset_x;
	int				pixel_index;
	int				key_w;
	int				key_s;
	int				key_a;
	int				key_d;
	int				key_gauche;
	int				key_droit;
	int				is_v_ray_cast;
	unsigned int	texel;
	t_ray			*ray;
	t_window_image	*window_img;
	t_GlobaleData	*data;
}	t_vars;

void	horizontal_ray_cast(t_vars *vars);
void	vertical_ray_cast(t_vars *vars);
int		close_window(t_vars *vars);
int		key_press(int keycode, t_vars *vars);
int		key_release(int keycode, t_vars *vars);
void	check_ray_direction(t_ray *ray);
void	check_wall(t_vars *vars);
int		is_wall(t_vars *vars, double x, double y);
void	ray_cast(t_vars *vars);
int		update(t_vars *vars);
void	draw_3d(t_vars *vars, int x);
void	put_pixel(t_vars *vars, int x, int y, int color);
void	load_tex(t_vars *vars);
void	texture(t_vars *vars, int x);
void	v_correction(t_ray *rays_data, int start_index);
void	h_correction(t_ray *rays_data, int start_index);
void	vertical_correction(t_ray *rays_data);
void	horizontal_correction(t_ray *rays_data);
void	init(t_vars *vars, int ac, char **av);
void	correct_rays(t_ray *rays_data);
void    free_map_line(t_MapLine *lines);
void    free_map_data(char **data);
void	check_player_pos(t_GlobaleData *gameMap);
void	remove_extra_spaces(char *str);
int		checkcolor(char *str);
int		check_map_delimited(t_Map map);
char	*fixline(char *line, int maxlen);
void	init_textures(t_GlobaleData *game);
void	ft_map(t_GlobaleData *ptr);
void	check_map_validity(t_Map map);
void	add_to_list(t_GlobaleData *mapList, char *line);
int		check_name_cub(char *str);
int		is_valid_rgb(int r, int g, int b);
int		get_number_of_rows(t_MapLine *map);
int		getsize_largline(t_MapLine *map);
int		cnt_vrgls(char *str);
int		set_fl_color_hpl(char *str, int *r, int *g, int *b);
void	set_floor_color(t_GlobaleData *data, char *line);
void	format_f_eror(char *line);
int		set_ce_color_hpl(char *str, int *r, int *g, int *b);
void	format_c_eror(char *line);
void	set_ceiling_color(t_GlobaleData *data, char *line);
int		is_space(int c);
int		in_set(char c);
int		nbr_of_lines(char *filename);
void	get_file_content(t_GlobaleData *ptr, char *filename);
void	parse(int ac, char **av, t_GlobaleData *ptr);
void	fill_textures(t_GlobaleData *data, char *ptr);
void	west_texture(t_GlobaleData *data, char **ptr);
void	north_texture(t_GlobaleData *data, char **ptr);
void	east_texture(t_GlobaleData *data, char **ptr);
void	south_texture(t_GlobaleData *data, char **ptr);
char	**split_after_space_reduction(char *line);
void	ft_free_split(char **words);
void	check_err(char *ptr);
void	print_error(char *error, int exit_code);
void	check_player_pos_help(t_GlobaleData *gameMap, int x, int y);
char	**ft_split_and_trim(char *line);
int		ft_count_words(const char *str, char c);
char	*ft_concat_split(char **split);
void	ft_free_concat(char *concat);
void	free_split_result(char **split_result);
int		find_last_dot_index(char **spt_rs);

#endif
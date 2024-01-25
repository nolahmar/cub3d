/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <bbendiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 11:13:26 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/24 16:30:22 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	set_fl_color_hpl(char *str, int *r, int *g, int *b)
{
	int	read_value;

	read_value = 0;
	while (*str && read_value < 3)
	{
		if (ft_isdigit(*str) && !in_set(*str))
		{
			if (read_value == 0)
				*r = ft_atoi(str);
			else if (read_value == 1)
				*g = ft_atoi(str);
			else if (read_value == 2)
				*b = ft_atoi(str);
			read_value++;
			while (*str && (ft_isdigit(*str)))
				str++;
		}
		else if (*str == ',')
			str++;
		else if (!ft_isdigit(*str) && *str != ',')
			print_error("Error\nformat de couleur invalide (sol) !\n", 1);
	}
	return (read_value);
}

char	*ft_concat_split(char **split)
{
	char	*concat;
	int		i;

	concat = NULL;
	i = 0;
	while (split[i])
	{
		if (i == 0)
			concat = ft_strdup(split[i]);
		else
		{
			concat = ft_strjoin(concat, ",");
			concat = ft_strjoin(concat, split[i]);
		}
		i++;
	}
	return (concat);
}

void	set_floor_color(t_GlobaleData *data, char *line)
{
	char	**rgb_ports;
	char	*rgb_str;
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 0;
	b = 0;
	if (data->floorcolor.blue >= 0)
		print_error("Error\nDuplicate floor color\n", 1);
	format_f_eror(line);
	rgb_ports = ft_split_and_trim(line + 2);
	rgb_str = ft_concat_split(rgb_ports);
	ft_free_split(rgb_ports);
	if (set_fl_color_hpl(rgb_str, &r, &g, &b) != 3 || cnt_vrgls(rgb_str) != 2
		|| checkcolor(rgb_str) == 0)
		print_error("Error\nformat de couleur invalide (sol) !\n", 1);
	if (!is_valid_rgb(r, g, b))
		print_error("Erreur :\nvaleur RGB invalide (sol) !\n", 1);
	ft_free_concat(rgb_str);
	data->floorcolor.red = r;
	data->floorcolor.green = g;
	data->floorcolor.blue = b;
}

int	set_ce_color_hpl(char *str, int *r, int *g, int *b)
{
	int	read_value;

	read_value = 0;
	while (*str && read_value < 3)
	{
		if (ft_isdigit(*str) && !in_set(*str))
		{
			if (read_value == 0)
				*r = ft_atoi(str);
			else if (read_value == 1)
				*g = ft_atoi(str);
			else if (read_value == 2)
				*b = ft_atoi(str);
			read_value++;
			while (*str && (ft_isdigit(*str)))
				str++;
		}
		else if (*str == ',')
			str++;
		else if (!ft_isdigit(*str) && *str != ',')
			print_error("Erreur :\nformat de couleur invalide  (ceil)!\n", 1);
	}
	return (read_value);
}

void	set_ceiling_color(t_GlobaleData *data, char *line)
{
	char	*rgb_str;
	char	**rgb_ports;
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 0;
	b = 0;
	if (data->ceilcolor.blue >= 0)
		print_error("Error\n", 1);
	format_c_eror(line);
	rgb_ports = ft_split_and_trim(line + 2);
	rgb_str = ft_concat_split(rgb_ports);
	if (set_ce_color_hpl(rgb_str, &r, &g, &b) != 3 || cnt_vrgls(rgb_str) != 2
		|| checkcolor(rgb_str) == 0)
		print_error("Erreur :\nformat de couleur invalide (ceil) !\n", 1);
	if (!is_valid_rgb(r, g, b))
		print_error("Erreur :\nvaleur RGB invalide (ceil) !\n", 1);
	ft_free_split(rgb_ports);
	ft_free_concat(rgb_str);
	data->ceilcolor.red = r;
	data->ceilcolor.green = g;
	data->ceilcolor.blue = b;
}

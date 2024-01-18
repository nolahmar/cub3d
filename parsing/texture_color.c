/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:45:47 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/18 16:07:30 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	north_texture(t_GlobaleData *data, char **ptr)
{
	int		i;
	char	**words;
	int		fd;

	i = 0;
	(*ptr) += 2;
	if (data->north != NULL)
		print_error("Error: north 1\n", 1);
	if (*ptr == NULL || **ptr != ' ')
		print_error("Error: north 2\n", 1);
	while ((*ptr)[i] != '\n')
		i++;  // wtf
	words = split_after_space_reduction(*ptr);
	if (words && words[1] == NULL)  // todo: possible seg
	{
		data->north = malloc(sizeof(t_Texture));
		// todo: check allocation failure
		data->north->path = ft_strdup(words[0]);
		// todo: check allocation failure for strdup
		ft_free_split(words);
	}
	else
		print_error("Error: north 3\n", 1);
	fd = open(data->north->path, O_RDONLY);
	if (fd < 0)
		print_error("Error: north 4\n", 1);
	// todo: close fd
}

void	south_texture(t_GlobaleData *data, char **ptr)
{
	int		i;
	char	**words;
	int		fd;

	i = 0;
	(*ptr) += 2;
	if (*ptr == NULL || **ptr != ' ')
		print_error("Error: south\n", 1);
	while ((*ptr)[i] != '\n')
		i++; // wtf
	if (data->south != NULL)
		print_error("Error: south\n", 1);
	words = split_after_space_reduction(*ptr);
	if (words && words[1] == NULL) // todo: possible seg
	{
		data->south = malloc(sizeof(t_Texture));
		// todo: check allocation failure
		data->south->path = ft_strdup(words[0]);
		// todo: check allocation failure for strdup
		ft_free_split(words);
	}
	else
		print_error("Error: south\n", 1);
	fd = open(data->south->path, O_RDONLY);
	if (fd < 0)
		print_error("Error: south\n", 1);
	// todo: close fd
}

void	east_texture(t_GlobaleData *data, char **ptr)
{
	int		i;
	char	**words;
	int		fd;

	i = 0;
	(*ptr) += 2;
	if (*ptr == NULL || **ptr != ' ')
		print_error("Error: east\n", 1);
	while ((*ptr)[i] != '\n')
		i++;  // wtf
	if (data->east != NULL)
		print_error("Error: east\n", 1);
	words = split_after_space_reduction(*ptr);
	if (words && words[1] == NULL) // todo: possible seg
	{
		data->east = malloc(sizeof(t_Texture));
		// todo: check allocation failure
		data->east->path = ft_strdup(*words);
		// todo: check allocation failure for strdup
		ft_free_split(words);
	}
	else
		print_error("Error: east\n", 1);
	fd = open(data->east->path, O_RDONLY);
	if (fd < 0)
		print_error("Error: east\n", 1);
	// todo: close fd
}

void	west_texture(t_GlobaleData *data, char **ptr)
{
	int		i;
	char	**words;
	int		fd;

	i = 0;
	(*ptr) += 2;
	if (*ptr == NULL || **ptr != ' ')
		print_error("Error: west\n", 1);
	while ((*ptr)[i] != '\n')
		i++; // wtf
	if (data->west != NULL)
		print_error("Error: west\n", 1);
	words = split_after_space_reduction(*ptr);
	if (words && words[1] == NULL)
	{
		data->west = malloc(sizeof(t_Texture));
		// todo: check allocation failure
		data->west->path = ft_strdup(words[0]);
		// todo: check allocation failure for strdup
		ft_free_split(words);
	}
	else
		print_error("Error: west\n", 1);
	fd = open(data->north->path, O_RDONLY);
	if (fd < 0)
		print_error("Error: west\n", 1);
	// todo: close fd
}

void	fill_textures(t_GlobaleData *data, char *ptr)
{
	if (*ptr && ft_strncmp(ptr, "NO ", 3) == 0)
		north_texture(data, &ptr);
	else if (*ptr && ft_strncmp(ptr, "SO ", 3) == 0)
		south_texture(data, &ptr);
	else if (*ptr && ft_strncmp(ptr, "WE ", 3) == 0)
		west_texture(data, &ptr);
	else if (*ptr && ft_strncmp(ptr, "EA ", 3) == 0)
		east_texture(data, &ptr);
	else if (*ptr && ft_strncmp(ptr, "F ", 2) == 0)
	{
		set_floor_color(data, ptr);
	}
	else if (*ptr && ft_strncmp(ptr, "C ", 2) == 0)
		set_ceiling_color(data, ptr);
	else
		check_err(ptr);
}

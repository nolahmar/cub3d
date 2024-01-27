/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 10:45:47 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/27 15:51:51 by nolahmar         ###   ########.fr       */
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
	if (data->north != NULL || *ptr == NULL || **ptr != ' ')
		print_error("Error\nTHE PATH IS NOT VALID (north) / DUPLICATE!\n", 1);
	while ((*ptr)[i] != '\n')
		i++;
	words = split_after_space_reduction(*ptr);
	if (words && words[0] != NULL && words[1] == NULL)
	{
		data->north = malloc(sizeof(t_Texture));
		if (data->north == NULL)
			print_error("Error\nAllocation error\n", 1);
		data->north->path = ft_strdup(words[0]);
		ft_free_split(words);
	}
	else
		print_error("Error\nInvalid path format!\n", 1);
	fd = open(data->north->path, O_RDONLY);
	if (fd < 0)
		print_error("Error\nOpen image (north)\n", 1);
	close(fd);
}

void	south_texture(t_GlobaleData *data, char **ptr)
{
	int		i;
	char	**words;
	int		fd;

	i = 0;
	(*ptr) += 2;
	if (data->south != NULL || *ptr == NULL || **ptr != ' ')
		print_error("Error\nTHE PATH IS NOT VALID (south)/DUPLICATE!\n", 1);
	while ((*ptr)[i] != '\n')
		i++;
	words = split_after_space_reduction(*ptr);
	if (words && words[0] != NULL && words[1] == NULL)
	{
		data->south = malloc(sizeof(t_Texture));
		if (data->south == NULL)
			print_error("Error\nallocation error\n", 1);
		data->south->path = ft_strdup(words[0]);
		ft_free_split(words);
	}
	else
		print_error("Error:\nInvalid path format!\n", 1);
	fd = open(data->south->path, O_RDONLY);
	if (fd < 0)
		print_error("Error:\nopen image (south)\n", 1);
	close(fd);
}

void	east_texture(t_GlobaleData *data, char **ptr)
{
	int		i;
	char	**words;
	int		fd;

	i = 0;
	(*ptr) += 2;
	if (data->east != NULL || *ptr == NULL || **ptr != ' ')
		print_error("Error\nTHE PATH IS NOT VALID (east)/DUPLICATE!\n", 1);
	while ((*ptr)[i] != '\n')
		i++;
	words = split_after_space_reduction(*ptr);
	if (words && words[0] != NULL && words[1] == NULL)
	{
		data->east = malloc(sizeof(t_Texture));
		if (data->east == NULL)
			print_error("Error\nAllocation error\n", 1);
		data->east->path = ft_strdup(*words);
		ft_free_split(words);
	}
	else
		print_error("Error\nInvalid path format!\n", 1);
	fd = open(data->east->path, O_RDONLY);
	if (fd < 0)
		print_error("Error\nOpen image (east)\n", 1);
	close(fd);
}

void	west_texture(t_GlobaleData *data, char **ptr)
{
	int		i;
	char	**words;
	int		fd;

	i = 0;
	(*ptr) += 2;
	if (data->west != NULL || *ptr == NULL || **ptr != ' ')
		print_error("Error\nTHE PATH IS NOT VALID (west)/DUPLICATE!\n", 1);
	while ((*ptr)[i] != '\n')
		i++;
	words = split_after_space_reduction(*ptr);
	if (words && words[0] != NULL && words[1] == NULL)
	{
		data->west = malloc(sizeof(t_Texture));
		if (data->west == NULL)
			print_error("Error\nallocation error\n", 1);
		data->west->path = ft_strdup(words[0]);
		ft_free_split(words);
	}
	else
		print_error("Error\nInvalid path format!\n", 1);
	fd = open(data->north->path, O_RDONLY);
	if (fd < 0)
		print_error("Error\nopen image (north)\n", 1);
	close(fd);
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

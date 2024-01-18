/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:09:52 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/18 17:14:18 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	nbr_of_lines(char *filename)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		print_error("Error: map open\n", 1);
		exit(EXIT_FAILURE); // wtf
	}
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

void	get_file_content(t_GlobaleData *ptr, char *filename)
{
	int	len;
	int	fd;
	int	i;

	i = 0;
	len = nbr_of_lines(filename);
	ptr->file_content = malloc((len + 1) * sizeof(char *));
	if (!ptr->file_content)
		print_error("Error: malloc\n", 1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		print_error("Error: map open\n", 1);
	while (i < len)
	{
		ptr->file_content[i] = get_next_line(fd);
		i++;
	}
	ptr->file_content[i] = NULL;
	close(fd);
}

void	add_to_list(t_GlobaleData *mapList, char *line)
{
	t_MapLine	*newline;
	t_MapLine	*current;

	newline = malloc(sizeof(t_MapLine));
	current = mapList->mapline;
	if (newline == NULL)
		print_error("Error:\nMemory allocation failed\n", 1);
	newline->content = ft_strdup(line);
	if (newline->content == NULL)
		print_error("Error:\nMemory allocation failed\n", 1);
	newline->next = NULL;
	if (mapList->mapline == NULL)
		mapList->mapline = newline;
	else
	{
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = newline;
	}
}

void	init_textures(t_GlobaleData *game)
{
	game->north = NULL;
	game->south = NULL;
	game->west = NULL;
	game->east = NULL;
	game->mapline = NULL;
	game->file_content = NULL;
	game->ceilcolor.red = -1;
	game->ceilcolor.blue = -1;
	game->ceilcolor.green = -1;
	game->floorcolor.red = -1;
	game->floorcolor.blue = -1;
	game->floorcolor.green = -1;
}

void	parse(int ac, char **av, t_GlobaleData *ptr)
{
	int	i;

	i = 0;
	init_textures(ptr);
	if (ac != 2 || !check_name_cub(av[1]))
		print_error("Error: map name\n", 1);
	get_file_content(ptr, av[1]);
	while (ptr->file_content[i] && (ptr->file_content[i][0] != ' '
		&& ptr->file_content[i][0] != '1'))
		fill_textures(ptr, ptr->file_content[i++]);
	while (ptr->file_content[i] && (ptr->file_content[i][0] == ' '
		|| ptr->file_content[i][0] == '1') && ptr->north && ptr->east
		&& ptr->south && ptr->west && (ptr->ceilcolor.red >= 0
		&& ptr->floorcolor.red >= 0 && (ptr->ceilcolor.blue >= 0
		&& ptr->floorcolor.blue >= 0) && (ptr->ceilcolor.green >= 0
		&& ptr->floorcolor.green >= 0)))
		add_to_list(ptr, ptr->file_content[i++]);
	// printf("line[%s]\n", ptr->file_content[i]);
	// printf("log_test: [%d]\n", ptr->file_content[i][0] != ' ');
	while (ptr->file_content[i] && (ptr->file_content[i][0] != ' '
		|| ptr->file_content[i][0] != '1' ))
	{
		print_error("error :\nbad argument\n", 1);
		i++;
	}
	ft_map(ptr);
}

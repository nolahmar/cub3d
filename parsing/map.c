/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:41:05 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/18 15:57:24 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	check_map_validity(t_Map map)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (map.data[i][j] == 'N' || map.data[i][j] == 'S'
				|| map.data[i][j] == 'E' || map.data[i][j] == 'W')
				n += 1;
			else if (map.data[i][j] != '0' && map.data[i][j] != '1'
				&& map.data[i][j] != ' ' && map.data[i][j] != '\n')
				print_error("Error: map\n", 1);
			j++;
		}
		i++;
	}
	if (n != 1)
		print_error("Error: map\n", 1);
}

int	check_map_delimited(t_Map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.height)
	{
		j = 0;
		while (j < map.width)
		{
			if (map.data[i][j] == '0' && (i == 0 || j == 0
				|| i == map.height - 1 || j == map.width - 1
				|| map.data[i - 1][j] == ' ' || map.data[i + 1][j] == ' '
				|| map.data[i][j - 1] == ' ' || map.data[i][j + 1] == ' '))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	check_player_pos_help(t_GlobaleData *gameMap, int x, int y)
{
	gameMap->playerposition.x = x;
	gameMap->playerposition.y = y;
	if (gameMap->map.data[y][x] == 'N')
		gameMap->playerposition.angle = 0;
	else if (gameMap->map.data[y][x] == 'S')
		gameMap->playerposition.angle = 180;
	else if (gameMap->map.data[y][x] == 'E')
		gameMap->playerposition.angle = 90;
	else if (gameMap->map.data[y][x] == 'W')
		gameMap->playerposition.angle = 270;
	gameMap->map.data[y][x] = '0'; // todo: remove this
}

void	check_player_pos(t_GlobaleData *gameMap)
{
	int	x;
	int	y;
	int	found;

	y = 0;
	found = 0;
	while (y < gameMap->map.height)
	{
		x = 0;
		while (x < gameMap->map.width)
		{
			if (gameMap->map.data[y][x] == 'N' || gameMap->map.data[y][x] == 'S'
				|| gameMap->map.data[y][x] == 'E'
				|| gameMap->map.data[y][x] == 'W')
			{
				found = 1;
				check_player_pos_help(gameMap, x, y);
				return ;
			}
			x++;
		}
		y++;
	}
	if (found == 0)
		print_error("ERROR: map\n", 1);
}

void	ft_map(t_GlobaleData *ptr)
{
	int			i;
	t_MapLine	*current;

	i = 0;
	current = ptr->mapline;
	ptr->map.width = getsize_largline(ptr->mapline);
	ptr->map.height = get_number_of_rows(ptr->mapline);
	ptr->map.data = (char **)malloc(sizeof(char *) * (ptr->map.height + 1));
	if (ptr->map.data == NULL)
		print_error("Error: map\n", 1);
	while (i < ptr->map.height)
	{
		ptr->map.data[i] = fixline(current->content, ptr->map.width);
		i++;
		current = current->next;
		if (current == NULL)
			break ;
	}
	ptr->map.data[i] = NULL;
	check_map_validity(ptr->map);
	check_player_pos(ptr);
	if (check_map_delimited(ptr->map) == 0)
		print_error("ERROR: map\n", 1);
}

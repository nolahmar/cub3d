/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:29:31 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/17 15:02:30 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	is_space(int c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	in_set(char c)
{
	if (c == '.' || c == '-' || c == ';' || c == ':'
		|| c == '\'' || c == '\"' || c == '`')
	{
		return (1);
	}
	return (0);
}

void	remove_extra_spaces(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (!is_space(str[i]) || (i > 0 && !is_space(str[i - 1])))
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
}

int	get_number_of_rows(t_MapLine *map)
{
	int	count;

	count = 0;
	while (map)
	{
		map = map->next;
		count++;
	}
	return (count);
}

int	getsize_largline(t_MapLine *map)
{
	size_t	max;

	if (map == NULL)
		return (0);
	max = ft_strlen(map->content);
	while (map->next)
	{
		if (ft_strlen(map->next->content) > max)
			max = ft_strlen(map->next->content);
		map = map->next;
	}
	return (max);
}

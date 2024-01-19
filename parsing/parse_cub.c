/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:55:15 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/19 11:18:28 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_name_cub(char *str)
{
	char	**split_result;

	if (str != NULL)
	{
		split_result = ft_split(str, '.');
		if (split_result == NULL)
			return (0);
		if (split_result[0] == NULL || split_result[1] == NULL)
		{
			free(split_result);
			return (0);
		}
		if (ft_strncmp(split_result[1], "cub", 3) != 0
			|| ft_strlen(split_result[1]) != 3)
		{
			free(split_result);
			return (0);
		}
		free(split_result);
	}
	return (1);
}

char	*fixline(char *line, int maxlen)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_calloc(sizeof(char), (maxlen + 1));
	if (!new)
		return (NULL);
	while (line[i] && line[i] != '\n')
	{
		new[i] = line[i];
		i++;
	}
	while (i < maxlen)
	{
		new[i] = ' ';
		i++;
	}
	new[i] = '\0';
	return (new);
}

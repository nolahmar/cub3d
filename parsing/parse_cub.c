/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:55:15 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/17 15:02:30 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_name_cub(char *str)
{
	if (str != NULL)
	{
		if (!ft_strchr(str, '.'))
			return (0);
		if (str[ft_strlen(str) - 4] != '.'
			|| str[ft_strlen(str) - 3] != 'c'
			|| str[ft_strlen(str) - 2] != 'u'
			|| str[ft_strlen(str) - 1] != 'b'
			|| str[ft_strlen(str) - 5] == 47)
			return (0);
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

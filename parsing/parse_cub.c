/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <bbendiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:55:15 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/25 10:37:37 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_split_result(char **split_result)
{
	size_t	i;

	i = 0;
	while (split_result[i] != NULL)
	{
		free(split_result[i]);
		i++;
	}
	free(split_result);
}

int	find_last_dot_index(char **spt_rs)
{
	int	last_dot_index;
	int	i;

	last_dot_index = -1;
	i = 0;
	while (spt_rs[i] != NULL)
	{
		last_dot_index = i;
		i++;
	}
	return (last_dot_index);
}

int	check_name_cub(char *str)
{
	char	**spt_rs;
	int		last_dot_index;

	if (str != NULL)
	{
		spt_rs = ft_split(str, '.');
		if (spt_rs == NULL)
			return (0);
		last_dot_index = find_last_dot_index(spt_rs);
		if (last_dot_index < 0 || last_dot_index == 0)
		{
			free_split_result(spt_rs);
			return (0);
		}
		if (ft_strncmp(spt_rs[last_dot_index], "cub", 3) != 0
			|| ft_strlen(spt_rs[last_dot_index]) != 3)
		{
			free_split_result(spt_rs);
			return (0);
		}
		free_split_result(spt_rs);
		return (1);
	}
	return (0);
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

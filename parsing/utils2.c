/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolahmar <nolahmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:22:56 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/17 15:02:30 by nolahmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**ft_split_and_trim(char *line)
{
	int		i;
	char	**split;
	char	*temp;

	i = 0;
	split = ft_split(line, ',');
	while (split[i])
	{
		temp = split[i];
		split[i] = ft_strtrim(split[i], " ");
		free(temp);
		i++;
	}
	return (split);
}

int	ft_count_words(const char *str, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			word++;
		i++;
	}
	if (str[0] != '\0')
		word++;
	return (word);
}

int	is_valid_rgb(int r, int g, int b)
{
	if (r >= 0 && r <= 255 && g >= 0 && g <= 255 && b >= 0 && b <= 255)
		return (1);
	return (0);
}

void	ft_free_concat(char *concat)
{
	if (concat)
		free(concat);
}

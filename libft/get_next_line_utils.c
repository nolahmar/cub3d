/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <bbendiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 11:52:10 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/16 09:37:31 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_checkc(char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strjoin_p(char *s1, char s2)
{
	size_t		n;
	int			i;
	char		*p;

	n = ft_strlen(s1);
	i = ft_strlen(s1);
	p = malloc(sizeof(char) * n + 2);
	if (!p)
		return (0);
	p[n + 1] = '\0';
	p[n] = s2;
	while (i--)
		p[i] = s1[i];
	free(s1);
	return (p);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 11:46:40 by bbendiou          #+#    #+#             */
/*   Updated: 2022/11/13 18:08:03 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while ((s1[i] != '\0' || s2[i] != '\0') && (i < n))
	{
		if (s1[i] > s2[i] || s1[i] < s2[i])
			return ((unsigned char )s1[i] - (unsigned char )s2[i]);
		i++;
	}
	return (0);
}

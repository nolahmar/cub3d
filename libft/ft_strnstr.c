/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:14:55 by bbendiou          #+#    #+#             */
/*   Updated: 2022/11/10 17:24:10 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen((char *)small) == 0)
		return ((char *)big);
	if (!big && len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == small[j] && i + j < len && small[j] && big[i + j])
		{
			j++;
		}
		if (small[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:54:23 by bbendiou          #+#    #+#             */
/*   Updated: 2022/11/03 14:00:46 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char		*srcc;
	unsigned char			*dest;
	size_t					i;

	dest = (unsigned char *)dst;
	srcc = (unsigned const char *)src;
	i = 0;
	if (!dst && !src)
		return (0);
	if (dst < src)
	{
		while (i < len)
		{
			dest[i] = srcc[i];
			i++;
		}
	}
	else
	{
		while (len--)
			dest[len] = srcc[len];
	}
	return (dst);
}

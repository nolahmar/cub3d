/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:48:47 by bbendiou          #+#    #+#             */
/*   Updated: 2022/11/08 11:24:15 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*csrc;
	char		*cdst;
	size_t		i;

	i = 0;
	csrc = (const char *)src;
	cdst = (char *)dst;
	if (csrc == cdst)
		return (cdst);
	if (csrc == NULL && cdst == NULL)
		return (NULL);
	while (i < n)
	{
		cdst[i] = csrc[i];
		i++;
	}
	return (dst);
}

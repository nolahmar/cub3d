/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:52:43 by bbendiou          #+#    #+#             */
/*   Updated: 2022/11/10 18:02:44 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*sub;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen((char *)s))
		return (ft_strdup(""));
	if (len > ft_strlen((char *)s + start))
		len = ft_strlen((char *)s + start);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			sub[j++] = s[i];
		i++;
	}
	sub[j] = '\0';
	return (sub);
}

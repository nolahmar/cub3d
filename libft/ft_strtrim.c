/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:50:12 by bbendiou          #+#    #+#             */
/*   Updated: 2022/11/10 14:40:08 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && (ft_strchr(set, *s1)))
		s1++;
	len = ft_strlen((char *)s1);
	while (len > 0 && (ft_strrchr(set, s1[len])))
		len--;
	return (ft_substr(s1, 0, len + 1));
}

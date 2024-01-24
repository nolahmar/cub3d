/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <bbendiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:53:39 by bbendiou          #+#    #+#             */
/*   Updated: 2024/01/02 14:48:29 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	char	*ptr;

	s2 = (char *)s1;
	ptr = malloc (ft_strlen(s2) + 1);
	if (ptr == NULL)
		return (NULL);
	ft_strcpy (ptr, s2);
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbendiou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:29:55 by bbendiou          #+#    #+#             */
/*   Updated: 2022/11/07 11:48:37 by bbendiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *c, size_t n)
{
	unsigned char	*p ;

	p = (unsigned char *)c;
	while (n > 0)
	{
		*p = '\0';
		p++;
		n--;
	}
}
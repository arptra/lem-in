/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:28:54 by bgerda            #+#    #+#             */
/*   Updated: 2019/04/28 20:59:57 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	value;
	unsigned char	*str;

	i = 0;
	value = (unsigned char)c;
	str = (unsigned char*)s;
	while (i < n)
	{
		if (str[i] == value)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

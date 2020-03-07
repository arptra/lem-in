/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:48:40 by bgerda            #+#    #+#             */
/*   Updated: 2019/05/08 16:46:01 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	value;
	unsigned char	*s1;
	unsigned char	*s2;

	i = 0;
	value = (unsigned char)c;
	s1 = (unsigned char*)src;
	s2 = (unsigned char*)dst;
	while (i < n)
	{
		s2[i] = s1[i];
		if (s1[i] == value)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}

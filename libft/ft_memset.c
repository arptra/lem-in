/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 17:19:37 by bgerda            #+#    #+#             */
/*   Updated: 2019/04/17 19:43:14 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	value;
	char			*str;

	value = (unsigned char)c;
	str = (char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = value;
		i++;
	}
	return (b);
}

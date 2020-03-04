/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:40:02 by bgerda            #+#    #+#             */
/*   Updated: 2019/04/28 21:46:10 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	sym;
	char			*str;
	int				i;

	sym = (unsigned char)c;
	str = (char*)s;
	i = ft_strlen(str);
	while (i != -1)
	{
		if (str[i] == sym)
			return (&str[i]);
		i--;
	}
	return (0);
}

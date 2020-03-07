/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:14:20 by bgerda            #+#    #+#             */
/*   Updated: 2019/05/08 17:20:33 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	sym;
	char	*str;
	int		i;

	sym = (char)c;
	str = (char*)s;
	i = 0;
	while (str[i] != '\0' && str[i] != sym)
		i++;
	if (str[i] != sym)
		return (NULL);
	else
		return (&str[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 17:25:15 by bgerda            #+#    #+#             */
/*   Updated: 2019/04/28 21:03:44 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		len;

	len = 0;
	while (s1[len] != '\0')
		len++;
	if (!(str = (char*)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	len = 0;
	while (s1[len] != '\0')
	{
		str[len] = s1[len];
		len++;
	}
	str[len] = '\0';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:05:58 by bgerda            #+#    #+#             */
/*   Updated: 2019/05/08 17:46:48 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	unsigned int	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char*)haystack);
	if (ft_strlen(haystack) < ft_strlen(needle) || len < ft_strlen(needle))
		return (NULL);
	while (haystack[i] != '\0' && i <= len - ft_strlen(needle))
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j] != '\0')
			j++;
		if (j == ft_strlen(needle))
			return ((char*)&haystack[i]);
		i++;
	}
	return (0);
}

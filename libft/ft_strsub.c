/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 18:47:23 by bgerda            #+#    #+#             */
/*   Updated: 2019/05/06 18:58:21 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (s == 0)
		return (NULL);
	if (!(str = ft_memalloc(len + 1)))
		return (NULL);
	return (ft_strncpy(str, &s[start], len));
}

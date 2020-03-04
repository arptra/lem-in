/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:23:29 by bgerda            #+#    #+#             */
/*   Updated: 2019/05/08 17:32:39 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strtrim(char const *s, char c)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (ft_strsub(s, 0, i));
}

static int	count_words(char const *s, char c)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			k++;
			while (s[i] != c && s[i] != '\0')
				i++;
			i--;
		}
		i++;
	}
	return (k);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	char	**str;

	if (s == 0)
		return (NULL);
	i = 0;
	str = (char**)malloc(sizeof(char*) * (count_words(s, c) + 1));
	if (str == NULL)
		return (NULL);
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			str[j] = strtrim(&s[i], c);
			while (s[i] != c && s[i] != '\0')
				i++;
			i--;
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

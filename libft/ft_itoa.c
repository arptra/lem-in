/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:33:00 by bgerda            #+#    #+#             */
/*   Updated: 2019/05/08 17:19:32 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(long n)
{
	int		i;

	i = 1;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*num;
	int		sign;
	int		i;

	sign = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		sign = 1;
	}
	if (!(num = ft_strnew(len(n) + sign)))
		return (NULL);
	i = len(n);
	while (i >= 0)
	{
		num[--i + sign] = n % 10 + '0';
		n = n / 10;
	}
	if (sign == 1)
		num[0] = '-';
	return (num);
}

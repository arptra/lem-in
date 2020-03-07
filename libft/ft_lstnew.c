/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:01:55 by bgerda            #+#    #+#             */
/*   Updated: 2019/05/10 21:26:53 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*data;

	if ((data = (t_list*)ft_memalloc(sizeof(t_list))))
	{
		if (!content)
		{
			content_size = 0;
			data->content = NULL;
		}
		else
		{
			if (!(data->content = ft_memalloc(content_size)))
			{
				free(data);
				return (NULL);
			}
			data->content_size = content_size;
			ft_memcpy(data->content, content, content_size);
		}
		data->next = NULL;
	}
	return (data);
}

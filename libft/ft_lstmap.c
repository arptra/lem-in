/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 20:13:05 by bgerda            #+#    #+#             */
/*   Updated: 2019/05/11 09:51:58 by bgerda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*list;
	t_list	*new;

	if ((list = f(lst)) == NULL)
		return (NULL);
	new = list;
	while (lst->next)
	{
		lst = lst->next;
		if ((new->next = f(lst)) == NULL)
			return (NULL);
		new = new->next;
	}
	return (list);
}

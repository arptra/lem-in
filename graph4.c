/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 01:50:32 by student           #+#    #+#             */
/*   Updated: 2020/03/28 01:50:34 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_vertice_node	*iter_graph(t_vertice_node *tmp, char *cmp)
{
	while (tmp && ft_strcmp(tmp->name, cmp) != 0)
		tmp = tmp->next;
	return (tmp);
}

t_vertice_node	*getnth(t_graph *graph, char *src,
							char *link, t_vertice_node **ref)
{
	t_vertice_node	*tmp;
	t_vertice_node	*save;
	int				s;
	int				l;

	s = 1;
	l = 1;
	tmp = graph->head;
	while (tmp && ((s = ft_strcmp(tmp->name, src)) != 0 &&
					(l = ft_strcmp(tmp->name, link)) != 0))
		tmp = tmp->next;
	save = tmp;
	if (s == 0 && l != 0)
	{
		iter_graph(tmp, link);
		*ref = tmp;
		return (save);
	}
	else if (l == 0 && s != 0)
	{
		iter_graph(tmp, src);
		*ref = save;
		return (tmp);
	}
	return (NULL);
}

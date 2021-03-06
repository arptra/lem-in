/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_disjoint_paths.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 01:10:46 by student           #+#    #+#             */
/*   Updated: 2020/03/28 01:10:51 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

t_adjacent	*find_self(t_vertice_node *vertex, t_adjacent *tmp)
{
	t_vertice_node	*self;

	self = vertex;
	while (tmp)
	{
		if (tmp->elem_in_main_list == self)
			return (tmp);
		tmp = tmp->next;
	}
	return (tmp);
}

void		add_niegh_dup(t_graph *graph, t_vertice_node *node)
{
	t_adjacent	*niegh;

	push_nieghbors(graph->tail, node->name, node, 0);
	niegh = node->neighbors_head;
	while (niegh)
	{
		if (niegh->elem_in_main_list != node->from &&
				niegh->elem_in_main_list != node->to &&
			niegh->elem_in_main_list->dup != 2)
		{
			push_nieghbors(graph->tail, niegh->elem_in_main_list->name,
					niegh->elem_in_main_list, 1);
		}
		niegh = niegh->next;
	}
}

void		reassign(t_adjacent *tmp, t_vertice_node *node)
{
	while (tmp)
	{
		if (node->from == tmp->elem_in_main_list && node->from->dup != 1)
		{
			tmp->weight = -1;
			tmp->visit = 1;
		}
		else if (tmp->elem_in_main_list->dup == 2)
			tmp->visit = 1;
		else
			tmp->visit = 0;
		tmp = tmp->next;
	}
}

void		vertex_dup(t_graph *graph, t_vertice_node *node)
{
	t_adjacent	*from;
	t_adjacent	*to;
	t_adjacent	*tmp;

	node->dup = 1;
	from = find_self(node, node->from->neighbors_head);
	from->visit = 0;
	to = find_self(node, node->to->neighbors_head);
	to->visit = 0;
	to->weight = -1;
	tmp = node->neighbors_head;
	reassign(tmp, node);
	add_vertex_dup(graph, node);
	push_nieghbors(node->to, graph->tail->name, graph->tail, -1);
	add_niegh_dup(graph, node);
}

int			connect_parents(t_vertice_node *vertex)
{
	t_vertice_node	*p;
	t_vertice_node	*r;
	t_vertice_node	*stop;
	int				check;

	stop = NULL;
	check = 1;
	while ((p = vertex->parent) != NULL)
	{
		if (p->neighbors_head->weight == 0)
		{
			r = p->neighbors_head->elem_in_main_list;
			if (r != vertex)
				vertex->parent = r;
			r->parent = p->parent;
			stop = r;
			check = 0;
		}
		if (stop == vertex->parent && check == 1)
			return (0);
		vertex = vertex->parent;
		check = 1;
	}
	return (1);
}

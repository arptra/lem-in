/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 18:57:05 by student           #+#    #+#             */
/*   Updated: 2020/03/27 18:57:07 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

int				add_niegh_and_link(t_graph *graph, char *src,
										char *dst, int weight)
{
	t_vertice_node	*from;
	t_vertice_node	*link;
	t_adjacent *tmp;

	if (ft_strcmp(src, dst) == 0)
		return (0);
	from = getnth(graph, src, dst, &link);
	if (from == NULL)
		return (0);
	tmp = from->neighbors_head;
	while (tmp)
	{
		if (tmp->name && ft_strcmp(tmp->name, dst) == 0)
			return (0);
		tmp = tmp->next;
	}
	push_nieghbors(from, dst, link, weight);
	return (1);
}

void			delete_graph(t_graph **graph)
{
	t_vertice_node	*tmp;
	t_vertice_node	*next;
	t_adjacent		*adj_tmp;
	t_adjacent		*adj_next;

	tmp = (*graph)->head;
	while (tmp)
	{
		next = tmp->next;
		adj_tmp = tmp->neighbors_head;
		while (adj_tmp)
		{
			adj_next = adj_tmp->next;
			free(adj_tmp->name);
			free(adj_tmp);
			adj_tmp = adj_next;
		}
		free(tmp->name);
		free(tmp);
		tmp = next;
	}
	free(*graph);
	(*graph) = NULL;
}

void			init_dup_value(t_vertice_node *tmp)
{
	tmp->dist = INT32_MAX;
	tmp->x = 0;
	tmp->y = 0;
	tmp->dup = 2;
	tmp->parent = NULL;
	tmp->from = NULL;
	tmp->to = NULL;
	tmp->next = NULL;
	tmp->neighbors_head = NULL;
	tmp->neighbors_tail = NULL;
}

int				add_vertex_dup(t_graph *graph, t_vertice_node *node)
{
	t_vertice_node	*tmp;

	tmp = (t_vertice_node *)malloc(sizeof(t_vertice_node));
	if (tmp == NULL)
		return (0);
	init_dup_value(tmp);
	tmp->neighbors_head = add_nieghbors(tmp);
	if (tmp->neighbors_head == NULL)
		return (0);
	tmp->name = ft_strjoin("L", node->name);
	tmp->prev = graph->tail;
	if (graph->tail)
		graph->tail->next = tmp;
	graph->tail = tmp;
	if (graph->head == NULL)
		graph->head = tmp;
	graph->size++;
	return (1);
}

t_vertice_node	*find_elem(t_graph *graph, t_room *input)
{
	t_vertice_node	*tmp;

	tmp = graph->head;
	while (tmp)
	{
		if (ft_strcmp(input->name, tmp->name) == 0)
			return (tmp);
		if (tmp->x == input->x && tmp->y == input->y)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

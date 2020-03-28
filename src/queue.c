/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 18:17:02 by student           #+#    #+#             */
/*   Updated: 2020/03/27 18:17:08 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "queue.h"

t_queue			*init_queue(void)
{
	t_queue	*tmp;

	tmp = (t_queue *)malloc(sizeof(t_node));
	tmp->head = NULL;
	tmp->tail = NULL;
	tmp->size = 0;
	return (tmp);
}

void			delete_queue(t_queue **queue)
{
	t_node	*tmp;
	t_node	*next;

	tmp = (*queue)->head;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*queue);
	(*queue) = NULL;
}

void			pushback(t_queue *queue, t_vertice_node *data)
{
	t_node	*tmp;

	tmp = (t_node *)malloc(sizeof(t_node));
	if (tmp == NULL)
		exit(3);
	tmp->data = data;
	tmp->next = NULL;
	tmp->prev = queue->tail;
	if (queue->tail)
		queue->tail->next = tmp;
	queue->tail = tmp;
	if (queue->head == NULL)
		queue->head = tmp;
	queue->size++;
}

void			delete_elem(t_queue *queue, t_node *elm)
{
	if (elm == NULL)
		exit(5);
	if (elm->prev)
		elm->prev->next = elm->next;
	if (elm->next)
		elm->next->prev = elm->prev;
	if (!elm->prev)
		queue->head = elm->next;
	if (!elm->next)
		queue->tail = elm->prev;
	free(elm);
	queue->size--;
}

t_vertice_node	*eject_min(t_queue *queue)
{
	t_node			*tmp;
	t_node			*del;
	t_vertice_node	*save;
	int				cur_min;

	tmp = queue->head;
	cur_min = tmp->data->dist;
	save = tmp->data;
	del = tmp;
	while (tmp)
	{
		if (tmp->data->dist < cur_min)
		{
			cur_min = tmp->data->dist;
			save = tmp->data;
			del = tmp;
		}
		tmp = tmp->next;
	}
	delete_elem(queue, del);
	return (save);
}

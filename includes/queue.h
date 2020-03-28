/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 02:49:34 by student           #+#    #+#             */
/*   Updated: 2020/03/28 02:49:36 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_QUEUE_H
# define LEM_IN_QUEUE_H
# include "graph.h"

typedef struct		s_node
{
	t_vertice_node	*data;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct		s_queue
{
	int				size;
	t_node			*head;
	t_node			*tail;
}					t_queue;

t_queue				*init_queue(void);
void				delete_queue(t_queue **queue);
void				pushback(t_queue *queue, t_vertice_node *data);
t_vertice_node		*eject_min(t_queue *queue);
void				delete_elem(t_queue *queue, t_node *elm);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 01:55:54 by student           #+#    #+#             */
/*   Updated: 2020/03/28 01:55:56 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_H
# define GRAPH_H

# include <stdlib.h>

typedef struct s_vertice_node	t_vertice_node;
typedef struct s_adjacent		t_adjacent;

struct							s_adjacent
{
	char						*name;
	int							weight;
	int							visit;
	t_vertice_node				*elem_in_main_list;
	t_adjacent					*next;
	t_adjacent					*prev;
};

struct							s_vertice_node
{
	char						*name;
	int							x;
	int							y;
	int							dist;
	int							dup;
	t_vertice_node				*from;
	t_vertice_node				*to;
	t_vertice_node				*save;
	t_vertice_node				*parent;
	t_adjacent					*neighbors_head;
	t_adjacent					*neighbors_tail;
	t_vertice_node				*next;
	t_vertice_node				*prev;
};

typedef struct					s_graph
{
	int							size;
	int							ants;
	t_vertice_node				*head;
	t_vertice_node				*tail;
	t_vertice_node				*start;
	t_vertice_node				*end;
}								t_graph;

typedef struct					s_data
{
	char						*str;
	struct s_data				*next;
}								t_data;

typedef struct					s_room
{
	int							fd;
	int							i;
	int							x;
	int							y;
	char						*src;
	char						*dst;
	char						*name;
	int							start;
	int							end;
	t_graph						*graph;
	t_data						*data;
	char						*line;
}								t_room;

t_graph							*init_graph(void);
t_adjacent						*add_nieghbors(t_vertice_node *node);
int								add_vertex_node(t_graph *graph, t_room *room);
void							push_nieghbors(t_vertice_node *vertex,\
												char *name,\
												t_vertice_node *ref,\
												int weight);
t_vertice_node					*getnth(t_graph *graph, char *src,\
												char *link,\
												t_vertice_node **ref);
int								add_niegh_and_link(t_graph *graph, char *src,\
													char *dst, int weight);
int								add_vertex_dup(t_graph *graph,\
													t_vertice_node *node);
t_vertice_node					*find_elem(t_graph *graph, t_room *input);
void							reset_dijkstra(t_graph *graph);
void							stick_toghether(t_graph *graph);
void							delete_graph(t_graph **graph);
void							init_value(t_vertice_node *tmp);
void							init_dup_value(t_vertice_node *tmp);
void							popneigh(t_vertice_node *vertex);
void							popvertex(t_graph *graph);
void							tail_pop(t_graph *graph);
t_vertice_node					*iter_graph(t_vertice_node *tmp, char *cmp);
t_adjacent						*find_self(t_vertice_node *vertex,\
													t_adjacent *tmp);
void							add_niegh_dup(t_graph *graph,\
													t_vertice_node *node);
void							reassign(t_adjacent *tmp, t_vertice_node *node);
void							vertex_dup(t_graph *graph,\
													t_vertice_node *node);
int								connect_parents(t_vertice_node *vertex);
void							combine_paths(t_vertice_node *start,\
													t_vertice_node *end);
void							divide_vertex(t_graph *graph);
t_data							*init_data(void);
t_data							*add_data(t_data *data, char *str);
void							print_data(t_data *head);
void							delete_data(t_data **data);
#endif

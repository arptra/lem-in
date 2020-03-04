//
// Created by Bears Gerda on 02/03/2020.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "lem-in.h"

/*
 * A structure to represent an adjacency list node
 */
typedef struct				s_adjlistnode
{
	int						dest;
	struct s_adjlistnode	*next;
}							t_adjlistnode;

/*
 * A structure to represent an adjacency list
 */
typedef struct			s_adjlist
{
	char 				*name;
	t_adjlistnode		*head;
}						t_adjlist;

/*
 * A structure to represent a graph. A graph
 * is an array of adjacency lists.
 * Size of array will be V (number of vertices in graph)
 */
typedef struct		s_graph
{
	int				V;
	t_adjlist		*array;
}					t_graph;

t_adjlistnode	*new_adj_list_node(int dest);
// A utility function that creates a graph of V vertices
t_graph			*create_graph(int V);
// Adds an edge to an undirected graph
void			add_edge(t_graph *graph, int src, int dest);
// A utility function to print the adjacency list
// representation of graph
void			print_graph(t_graph	*graph);

#endif //GRAPH_H

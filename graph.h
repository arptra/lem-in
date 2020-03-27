//
// Created by Bears Gerda on 02/03/2020.
//
#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

/*
 * A structure to represent an adjacency list node
 */

typedef struct s_vertice_node   t_vertice_node;
typedef struct s_adjacent       t_adjacent;
typedef struct s_names       	t_names;
typedef struct s_crdnts      	t_crdnts;

struct s_names
{
	char			*name;
	t_names			*next;
};

struct s_crdnts
{
	int				*x;
	int				*y;
	t_crdnts		*next;
};


struct s_adjacent
{
    char            *name;
    int             weight;
    int             visit;
    t_vertice_node  *elem_in_main_list;
    t_adjacent      *next;
    t_adjacent      *prev;
};

struct s_vertice_node
{
    char 			*name;
    int 			x;
    int 			y;
    int             dist;
    int             dup;
    t_vertice_node  *from;
    t_vertice_node  *to;
    t_vertice_node  *save;
    t_vertice_node  *parent;
    t_adjacent      *neighbors_head;
    t_adjacent      *neighbors_tail;
    t_vertice_node  *next;
    t_vertice_node  *prev;
};

typedef struct		s_graph
{
    int 			size;
    int             ants;
    t_vertice_node	*head;
    t_vertice_node	*tail;
    t_vertice_node	*start;
    t_vertice_node	*end;
	t_names			*names;
	t_crdnts		*crdnts;
}					t_graph;

typedef struct      s_data
{
    char            *str;
    struct s_data   *next;
}                   t_data;

typedef struct 		s_room
{
    int             fd;
    int             i;
    int 			x;
    int 			y;
    char            *src;
    char            *dst;
    char 			*name;
    int				start;
    int 			end;
    t_graph         *graph;
    t_data          *data;
    char            *line;
}					t_room;



t_graph             *init_graph();
t_adjacent          *add_nieghbors(t_vertice_node *node);
int                 add_vertex_node(t_graph *graph, t_room *room);
void                push_nieghbors(t_vertice_node *vertex, char *name, t_vertice_node *ref, int weight);
t_vertice_node      *getnth(t_graph *graph, char *src, char *link, t_vertice_node **ref);
int add_niegh_and_link (t_graph *graph, char *src, char *dst, int weight);
int                 add_vertex_dup(t_graph *graph, t_vertice_node *node);
t_vertice_node      *find_elem(t_graph *graph, t_room *input);
void                reset_dijkstra(t_graph *graph);
void                stick_toghether(t_graph *graph);

void                print_graph(t_graph *graph);
void	            delete_graph(t_graph **graph);

/* ************************************************************************** */
/*   written by: klekisha                                                     */
/* ************************************************************************** */
t_names				*ft_nw_name(const char *name);
t_crdnts			*ft_nw_crdnts(const int x, const int y);
#endif

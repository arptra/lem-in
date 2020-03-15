//
// Created by Bears Gerda on 02/03/2020.
//

#ifndef GRAPH_H
#define GRAPH_H

/*
 * A structure to represent an adjacency list node
 */

typedef struct s_vertice_node   t_vertice_node;
typedef struct s_adjacent       t_adjacent;

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
}					t_graph;
/*
 *  struct for parse map's file
 */
typedef struct 		s_room
{
    int 			x;
    int 			y;
    char 			*name;
    int				start;
    int 			end;
}					t_room;


t_graph             *init_graph();
t_adjacent          *add_nieghbors(t_vertice_node *node);
int                 add_vertex_node(t_graph *graph, t_room *room);
void                push_nieghbors(t_vertice_node *vertex, char *name, t_vertice_node *ref, int weight);
t_vertice_node      *getnth(t_graph *graph, char *src, char *link, t_vertice_node **ref);
int add_niegh_and_link (t_graph *graph, char *src, char *dst, int weight);
int                 add_vertex_dup(t_graph *graph, t_vertice_node *node);
t_vertice_node      *find_elem(t_graph *graph, char *name);
void                reset_dijkstra(t_graph *graph);
void                stick_toghether(t_graph *graph);

void                print_graph(t_graph *graph);
void	            delete_graph(t_graph **graph);

#endif

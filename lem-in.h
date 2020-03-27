#ifndef LEM_IN_H
#define LEM_IN_H

#include "libft/libft.h"
#include "graph.h"
#include "queue.h"
#include "path.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define FILL_BUFF 100

/*
 *  struct for parse map's file
 */


int	    fill_graph(t_room *input);
t_data  *init_data();
t_data  *add_data(t_data *data, char *str);
void    print_data(t_data *head);
void    delete_data(t_data **data);

int     ssp_finder(t_graph *graph, t_vertice_node *node);
void    print_ssp(t_graph *graph);
void    backward_path(t_graph *graph);

t_adjacent      *find_self(t_vertice_node *vertex, t_adjacent *tmp);
void    add_niegh_dup(t_graph *graph, t_vertice_node *node);
void    vertex_dup(t_graph *graph, t_vertice_node *node);
int connect_parents(t_vertice_node *vertex);
void    combine_paths(t_vertice_node *start, t_vertice_node *end);
void    divide_vertex(t_graph *graph);
t_path *merge_sort(t_path *head);
void    exitfree(t_graph *graph, int i);

void	ft_error(t_room *input, int err);
int     int_checker(char *str, int *flag);
int     digit_checker(char *str);
int     chck_ant(t_room *input);

void    moves(t_paths *paths);
void    output(t_paths *paths, t_data *head);
void    print_ant(int ant, char *name);
t_paths    *solver(t_graph *graph, t_paths *paths);
void    last_check(t_graph *graph, t_room *input);


#endif //LEM_IN_H

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

void	fill_graph(int fd, t_graph *graph);

int    ssp_finder(t_graph *graph, t_vertice_node *node);
void    print_ssp(t_graph *graph);
void    backward_path(t_graph *graph);

t_adjacent      *find_self(t_vertice_node *vertex, t_adjacent *tmp);
void    add_niegh_dup(t_graph *graph, t_vertice_node *node);
void    vertex_dup(t_graph *graph, t_vertice_node *node);
void	connect_parents(t_vertice_node *vertex);
void    combine_paths(t_vertice_node *start, t_vertice_node *end);
void    divide_vertex(t_graph *graph);
t_path *merge_sort(t_path *head);
void    exitfree(t_graph *graph, int i);

void    print_paths(t_vertice_node *from);

/* ************************************************************************** */
/*   written by: klekisha                                                     */
/* ************************************************************************** */

void	ft_error();
int		ft_chck_arg(int intgr, const char *strng);
int		ft_chck_nm_w_crdnts(t_room *input, t_graph *graph);
int		ft_chk_name(const char *name, t_graph *graph);
void	ft_del_crdnts(t_crdnts **crdnts);
void	ft_del_names(t_names **names);

#endif //LEM_IN_H

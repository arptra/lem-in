#include "lem-in.h"

void	delete_graph(t_graph **graph)
{
    t_vertice_node  *tmp;
    t_vertice_node  *next;
    t_adjacent      *adj_tmp;
    t_adjacent      *adj_next;

    tmp = (*graph)->head;
    next = NULL;
    while (tmp)
    {
        next = tmp->next;
        adj_tmp = tmp->neigbors;
        adj_next = NULL;
        while (adj_tmp)
        {
            adj_next = adj_tmp->next;
            free(adj_tmp);
            adj_tmp = adj_next;
        }
        free(tmp);
        tmp = next;
    }
    free(*graph);
    (*graph) = NULL;
}

void    print_graph(t_graph *graph)
{
    t_vertice_node *tmp;
    t_adjacent *niegh;

    tmp = graph->head;
    ft_putendl("Adjacency list of vertex");
    while (tmp)
    {
        ft_putstr(tmp->name);
        ft_putstr(" -> [ ");
        niegh = tmp->neigbors;
        while (niegh)
        {
            ft_putstr(niegh->name);
            ft_putstr(" ");
            niegh = niegh->next;
        }
        ft_putendl("]");
        tmp = tmp->next;
    }
}




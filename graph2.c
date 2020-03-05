#include "lem-in.h"

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


#include "lem-in.h"

void    relabele_vertices(t_vertice_node *start, t_queue *queue)
{
    t_adjacent		    *links;
    int		            w;
    t_vertice_node		*dst;
    int			        new_dist;

    links = start->neigbors;
    while (links != NULL)
    {
        w = links->weight;
        dst = links->elem_in_main_list;
        new_dist = start->dist + w;
        if (new_dist < dst->dist)
        {
            dst->dist = new_dist;
            dst->parent = start;
            pushback(queue, dst);
        }
        links = links->next;
    }
}

void    ssp_finder(t_graph *graph)
{
    t_vertice_node  *start;
    t_vertice_node  *end;
    t_queue         *queue;

    start = graph->start;
    end = graph->end;
    queue = init_queue();
    start->dist = 0;
    while (start != NULL && start != end)
    {
        relabele_vertices(start, queue);
        start = eject_min(queue);
    }
    delete_queue(&queue);
}

void    print_ssp(t_graph *graph)
{
    t_vertice_node *tmp;

    tmp = graph->end;
    ft_putstr("\nSSP from END to START = ");
    ft_putstr(tmp->name);
    ft_putstr(" -> ");
    while (tmp->parent)
    {
        ft_putstr(tmp->parent->name);
        if (tmp->parent->parent)
            ft_putstr(" -> ");
        tmp = tmp->parent;
    }
}
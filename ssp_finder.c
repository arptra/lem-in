#include "lem-in.h"

void    reset_dijkstra(t_graph *graph)
{
    t_vertice_node *tmp;

    tmp = graph->head;
    while (tmp)
    {
        tmp->dist = INT32_MAX;
        tmp->parent = NULL;
        tmp = tmp->next;
    }
}

void    relabele_vertices(t_vertice_node *start, t_queue *queue)
{
    t_adjacent		    *niegh;
    int		            w;
    t_vertice_node		*dst;
    int			        new_dist;

    niegh = start->neigbors;
    while (niegh != NULL )
    {
        w = niegh->weight;
        dst = niegh->elem_in_main_list;
        new_dist = start->dist + w;
        if (niegh->visit == 1 && new_dist < dst->dist)
        {
            dst->dist = new_dist;
            dst->parent = start;
            pushback(queue, dst);
        }
        niegh = niegh->next;
    }
}

int    ssp_finder(t_graph *graph, t_vertice_node *node)
{
    t_vertice_node  *start;
    t_vertice_node  *end;
    t_queue         *queue;

    start = node;
    end = graph->end;
    queue = init_queue();
    start->dist = 0;
    while (start != NULL && start != end)
    {
        relabele_vertices(start, queue);
        if(queue->size != 0)
            start = eject_min(queue);
        else
            return(0);
    }
    delete_queue(&queue);
    return (1);
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
    ft_putchar('\n');
}
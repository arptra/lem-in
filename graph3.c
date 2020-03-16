#include "graph.h"
#include "lem-in.h"

void		popneigh(t_vertice_node *vertex)
{
    t_adjacent	*next;
    t_adjacent  *neigh;

    neigh = vertex->neighbors_tail;
    if (neigh == NULL)
        exit(1);
    next = vertex->neighbors_tail;
    vertex->neighbors_tail = vertex->neighbors_tail->prev;
    if (vertex->neighbors_tail)
        vertex->neighbors_tail->next = NULL;
    if (next == vertex->neighbors_head)
        vertex->neighbors_head = NULL;
    free(next->name);
    free(next);
}

void		popvertex(t_graph *graph)
{
    t_vertice_node	*next;
    t_vertice_node	*tmp;

    tmp = graph->tail;
    if (tmp == NULL)
        exit(1);
    next = graph->tail;
    graph->tail =graph->tail->prev;
    if (graph->tail)
        graph->tail->next = NULL;
    if (next == graph->head)
        graph->head = NULL;
    graph->size--;
    free(next->name);
    free(next);
}

void        stick_toghether(t_graph *graph)
{
    t_vertice_node  *tmp;
    t_adjacent      *neigh;

    tmp = graph->head;
    while (tmp && tmp->name[0] != 'L')
    {
        neigh = tmp->neighbors_tail;
        while (neigh)
        {
            neigh->visit = 1;
            neigh->weight = 1;
            if (neigh->name && neigh->name[0] == 'L')
            {
                popneigh(tmp);
                neigh = tmp->neighbors_tail;
            }
            else
                neigh = neigh->prev;
        }
        tmp = tmp->next;
    }
    while(graph->tail->name[0] == 'L')
    {
        tmp = graph->tail;
        while (tmp->neighbors_head)
            popneigh(tmp);
        popvertex(graph);
    }
}

void    formater(char *name, int stop)
{
    int i;

    i = 0;
    if (ft_strlen(name) < stop)
    {
        while (i++ < stop - ft_strlen(name))
            ft_putchar(' ');

    }
}

void    print_room(t_graph *graph, int stop)
{
    t_vertice_node  *tmp;

    tmp = graph->head;
    ft_putstr("\nroom  |");
    while (tmp)
    {
        ft_putstr(tmp->name);
        formater(tmp->name, stop);
        ft_putstr("|");
        tmp = tmp->next;
    }
    tmp = graph->head;
    ft_putstr("\nparent|");
    while (tmp)
    {
        if (tmp->parent)
        {
            ft_putstr(tmp->parent->name);
            formater(tmp->parent->name, stop);
        }
        else
            ft_putstr("   ");
        ft_putstr("|");
        tmp = tmp->next;
    }
    tmp = graph->head;
    ft_putstr("\nfrom  |");
    while (tmp)
    {
        if (tmp->from)
        {
            ft_putstr(tmp->from->name);
            formater(tmp->from->name, stop);
        }
        else
            ft_putstr("   ");
        ft_putstr("|");
        tmp = tmp->next;
    }
    tmp = graph->head;
    ft_putstr("\nto    |");
    while (tmp)
    {
        if (tmp->to)
        {
            ft_putstr(tmp->to->name);
            formater(tmp->to->name, stop);
        }
        else
            ft_putstr("   ");
        ft_putstr("|");
        tmp = tmp->next;
    }
    ft_putchar('\n');
}

void    exitfree(t_graph *graph, int i)
{
    delete_graph(&graph);
    exit(i);
}

#include "graph.h"
#include "lem-in.h"

void    backward_path(t_graph *graph)
{
    t_vertice_node  *tmp;

    tmp = graph->end;
    tmp->to = NULL;
    tmp->dist = INT32_MAX;
    while (tmp->parent)
    {
        tmp->from = tmp->parent;
        tmp->from->dist = INT32_MAX;
        tmp->parent->to = tmp;
        tmp->parent = NULL;
        tmp = tmp->from;
    }
    graph->start->to = NULL;
}

t_adjacent      *find_self(t_vertice_node *vertex, t_adjacent *tmp)
{
    t_vertice_node *self;

    self = vertex;
    while (tmp)
    {
        if (tmp->elem_in_main_list == self)
            return (tmp);
        tmp = tmp->next;
    }
    return (tmp);
}

void    add_niegh_dup(t_graph *graph, t_vertice_node *node)
{
    t_adjacent  *niegh;

    add_niegh_and_link(graph, graph->tail->name, node->name, 0);

}

void    vertex_dup(t_graph *graph, t_vertice_node *node)
{
    t_adjacent  *from;
    t_adjacent  *to;
    t_adjacent  *tmp;

    from = find_self(node, node->from->neigbors);
    from->visit = 0;
    from->weight = -1;
    to = find_self(node, node->to->neigbors);
    to->visit = 0;
    to->weight = -1;
    tmp = node->neigbors;
    while (tmp)
    {
        if (node->from != tmp->elem_in_main_list)
            tmp->weight = -1;
        tmp->visit = 0;
        tmp = tmp->next;
    }
    add_vertex_dup(graph, node);
    add_niegh_dup(graph, node);
}

void    print_paths(t_vertice_node *from)
{
    t_adjacent *niegh;
    t_vertice_node  *tmp;
    int         i;

    i = 0;
    niegh = from->neigbors;
    while (niegh)
    {
        tmp = niegh->elem_in_main_list;
        if (tmp->to)
        {
            ft_putstr("\npath #");
            ft_putnbr(++i);
            ft_putstr(": ");
        }
        while (tmp->to)
        {
            ft_putstr(tmp->name);
            if (tmp->to->to)
                ft_putstr(" -> ");
            tmp = tmp->to;
        }
        niegh = niegh->next;
    }
    ft_putchar('\n');
}
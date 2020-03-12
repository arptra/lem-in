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

    //add_niegh_and_link(graph, graph->tail->name, node->name, 0);
    push_nieghbors(graph->tail, node->name, node, 0);
    niegh = node->neighbors_head;
    while (niegh)
    {
        if (niegh->elem_in_main_list != node->from &&
                niegh->elem_in_main_list != node->to
                && niegh->elem_in_main_list->dup != 2)
        {
            //add_niegh_and_link(graph, graph->tail->name, niegh->elem_in_main_list->name, 1);
            push_nieghbors(graph->tail, niegh->elem_in_main_list->name, niegh->elem_in_main_list, 1);
        }
        niegh = niegh->next;
    }

}

void    vertex_dup(t_graph *graph, t_vertice_node *node)
{
    t_adjacent  *from;
    t_adjacent  *to;
    t_adjacent  *tmp;

    node->dup = 1;
    from = find_self(node, node->from->neighbors_head);
    from->visit = 0;
    to = find_self(node, node->to->neighbors_head);
    to->visit = 0;
    to->weight = -1;
    tmp = node->neighbors_head;
    while (tmp)
    {
        if (node->from == tmp->elem_in_main_list && node->from->dup != 1)
        {
            tmp->weight = -1;
            tmp->visit = 1;
        }
        else if ( tmp->elem_in_main_list->dup == 2)
            tmp->visit = 1;
        else
            tmp->visit = 0;
        tmp = tmp->next;
    }
    add_vertex_dup(graph, node);
    push_nieghbors(node->to, graph->tail->name, graph->tail, -1);
    add_niegh_dup(graph, node);
}

void    print_paths(t_vertice_node *from)
{
    t_adjacent *niegh;
    t_vertice_node  *tmp;
    int         i;

    i = 0;
    niegh = from->neighbors_head;
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

void	connect_parents(t_vertice_node *vertex)
{
    t_vertice_node		*p;
    t_vertice_node		*r;

    while ((p = vertex->parent) != NULL)
    {
        if (p->neighbors_head->weight == 0)
        {
            r = p->neighbors_head->elem_in_main_list;
            if (r != vertex)
                vertex->parent = r;
            r->parent = p->parent;
        }
        vertex = vertex->parent;
    }
}

void	combine_paths(t_vertice_node *start, t_vertice_node *end)
{
    t_vertice_node		*a;
    t_vertice_node		*b;

    b = end;
    while ((a = b->parent) != NULL)
    {
        if (a->from != b && b->to != a)
        {
            if (a != start)
                a->to = b;
            if (b != end)
                b->from = a;
        }
        else
        {
            if (a->from == b)
                a->from = NULL;
            if (b->to == a)
                b->to = NULL;
        }
        b = a;
    }
}

void    divide_vertex(t_graph *graph)
{
    t_vertice_node *tmp;
    t_adjacent *cur_vertex;

    cur_vertex = graph->start->neighbors_head;
    while (cur_vertex)
    {
        tmp = cur_vertex->elem_in_main_list;
        while (tmp->to && tmp != graph->end)
        {
            vertex_dup(graph,tmp);
            tmp = tmp->to;
        }
        cur_vertex = cur_vertex->next;
    }

}
#include "lem-in.h"

int     add_niegh_and_link (t_graph *graph, char *src, char *dst, int weight)
{
    t_vertice_node  *from;
    t_vertice_node  *link;

    from = getnth(graph, src, dst, &link);
    if (from == NULL)
        return (0);
    push_nieghbors(from, dst, link, weight);
    return (1);
}

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
        adj_tmp = tmp->neighbors_head;
        adj_next = NULL;
        while (adj_tmp)
        {
            adj_next = adj_tmp->next;
            free(adj_tmp->name);
            free(adj_tmp);
            adj_tmp = adj_next;
        }
        free(tmp->name);
        free(tmp);
        tmp = next;
    }
    free(*graph);
    (*graph) = NULL;
}

int     add_vertex_dup(t_graph *graph, t_vertice_node *node)
{
    t_vertice_node  *tmp;

    tmp = (t_vertice_node *)malloc(sizeof(t_vertice_node));
    if (tmp == NULL)
        return (0);
    tmp->neighbors_head = NULL;
    tmp->neighbors_tail = NULL;
    tmp->neighbors_head = add_nieghbors(tmp);
    if (tmp->neighbors_head == NULL)
        return (0);
    tmp->dist = INT32_MAX;
    tmp->name = 0;
    tmp->x = 0;
    tmp->y = 0;
    tmp->dup = 2;
    tmp->name = ft_strjoin("L", node->name);
    tmp->parent = NULL;
    tmp->from = NULL;
    tmp->to = NULL;
    tmp->next = NULL;
    tmp->prev = graph->tail;
    if (graph->tail)
        graph->tail->next = tmp;
    graph->tail = tmp;
    if (graph->head == NULL)
        graph->head = tmp;
    graph->size++;
    return (1);
}

t_vertice_node  *find_elem(t_graph *graph, char *name)
{
    t_vertice_node *tmp;

    tmp = graph->head;
    while (tmp && ft_strcmp(name, tmp->name) != 0)
        tmp = tmp->next;
    return (tmp);
}

void    print_graph(t_graph *graph)
{
    t_vertice_node *tmp;
    t_adjacent *niegh;

    tmp = graph->head;
    ft_putendl("Adjacency list of vertex with weight");
    while (tmp)
    {
        ft_putstr(tmp->name);
        ft_putstr(" -> [ ");
        niegh = tmp->neighbors_head;
        while (niegh)
        {
            ft_putstr("(");
            ft_putstr(niegh->name);
            ft_putstr("; w=");
            ft_putnbr(niegh->weight);
            ft_putstr("; v=");
            ft_putnbr(niegh->visit);
            ft_putstr(") ");
            niegh = niegh->next;
        }
        ft_putendl("]");
        tmp = tmp->next;
    }
    ft_putendl("\nSTART ROOM");
    ft_putstr(graph->start->name);
    ft_putendl("\nEND ROOM");
    ft_putstr(graph->end->name);
    ft_putchar('\n');
}




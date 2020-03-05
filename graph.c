#include "lem-in.h"

t_graph         *init_graph()
{
    t_graph *tmp;

    tmp = (t_graph *) malloc(sizeof(t_vertice_node));
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->size = 0;
    return (tmp);
}

t_adjacent      *add_nieghbors()
{
    t_adjacent *tmp;

    tmp = (t_adjacent*)malloc(sizeof(t_adjacent));
    if (tmp == NULL)
        return (NULL);
    tmp->next = NULL;
    tmp->name = NULL;
    tmp->elem_in_main_list = NULL;
    return (tmp);
}

int             add_vertice_node(t_graph *graph, t_room *room)
{
    t_vertice_node  *tmp;

    tmp = (t_vertice_node *)malloc(sizeof(t_vertice_node));
    if (tmp == NULL)
        return (0);
    tmp->neigbors = add_nieghbors();
    if (tmp->neigbors == NULL)
        return (0);
    tmp->name = room->name;
    tmp->x = room->x;
    tmp->y = room->y;
    tmp->name = room->name;
    tmp->start = room->start;
    tmp->end = room->end;
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

void            push_nieghbors(t_vertice_node *vertice, char *name, t_vertice_node *ref)
{
    t_adjacent *cur;

    cur = vertice->neigbors;
    if (cur->name == NULL)
    {
        cur->name = name;
        cur->elem_in_main_list = ref;
        cur->next = NULL;
    }
    else
    {
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = (t_adjacent *) malloc(sizeof(t_adjacent));
        cur->next->name = name;
        cur->next->elem_in_main_list = ref;
        cur->next->next = NULL;
    }
}

t_vertice_node *getnth(t_graph *graph, char *src, char *link, t_vertice_node **ref)
{
    t_vertice_node *tmp;
    t_vertice_node *save;
    int             s;
    int             l;

    s = 1;
    l = 1;
    tmp = graph->head;
    while (tmp && ((s = ft_strcmp(tmp->name, src)) != 0 &&
                    (l = ft_strcmp(tmp->name, link)) != 0))
            tmp = tmp->next;
    save = tmp;
    if (s == 0 && l != 0)
    {
        while (tmp && ft_strcmp(tmp->name, link) != 0 )
            tmp = tmp->next;
        *ref = tmp;
        return (save);
    }
    else if (l == 0 && s != 0)
    {
        while (tmp && ft_strcmp(tmp->name, src) != 0 )
            tmp = tmp->next;
        *ref = save;
        return (tmp);
    }
    return (NULL);
}

void            add_niegh_and_link (t_graph *graph, char *src, char *dst)
{
    t_vertice_node  *from;
    t_vertice_node  *link;

    from = getnth(graph, src, dst, &link);
    push_nieghbors(from, dst, link);
}

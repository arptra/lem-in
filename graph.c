#include "lem-in.h"

t_graph         *init_graph()
{
    t_graph *tmp;

    tmp = (t_graph *) malloc(sizeof(t_vertice_node));
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->start = NULL;
    tmp->end = NULL;
    tmp->size = 0;
    tmp->ants = 0;
    return (tmp);
}

t_adjacent      *add_nieghbors()
{
    t_adjacent *tmp;

    tmp = (t_adjacent*)malloc(sizeof(t_adjacent));
    if (tmp == NULL)
        return (NULL);
    tmp->weight = 0;
    tmp->visit = 0;
    tmp->next = NULL;
    tmp->name = NULL;
    tmp->elem_in_main_list = NULL;
    return (tmp);
}

int             add_vertex_node(t_graph *graph, t_room *room)
{
    t_vertice_node  *tmp;

    tmp = (t_vertice_node *)malloc(sizeof(t_vertice_node));
    if (tmp == NULL)
        return (0);
    tmp->neigbors = add_nieghbors();
    if (tmp->neigbors == NULL)
        return (0);
    tmp->dist = INT32_MAX;
    tmp->name = room->name;
    tmp->x = room->x;
    tmp->y = room->y;
    tmp->name = room->name;
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
    if (room->start == 1)
        graph->start = tmp;
    if (room->end == 1)
        graph->end = tmp;
    return (1);
}

void            push_nieghbors(t_vertice_node *vertice, char *name, t_vertice_node *ref, int weight)
{
    t_adjacent *cur;

    cur = vertice->neigbors;
    if (cur->name == NULL)
    {
        cur->name = name;
        cur->weight = weight;
        cur->visit = 1;
        cur->elem_in_main_list = ref;
        cur->next = NULL;
    }
    else
    {
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = (t_adjacent *) malloc(sizeof(t_adjacent));
        cur->next->name = name;
        cur->next->weight = weight;
        cur->next->visit = 1;
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

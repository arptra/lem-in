#include "path.h"
#include <stdlib.h>

void    moves(t_paths *paths)
{
    t_path  *tmp;
    int     sum;

    tmp = paths->head;
    sum = 0;
    while (tmp)
    {
        tmp->moves = paths->num_moves - tmp->length;
        sum = sum + tmp->moves;
        tmp = tmp->next;
    }
    tmp = paths->head;
    sum = paths->ants - sum;
    while (sum--)
    {
        tmp->moves += 1;
        tmp = tmp->next;
    }
}

int     cur_moves(t_graph *graph)
{
    t_adjacent *tmp;
    int         amt;
    int         i;

    tmp = graph->start->neighbors_head;
    amt = 0;
    i = 0;
    while (tmp)
    {
        if (tmp->elem_in_main_list->from)
        {
            amt += path_len(tmp->elem_in_main_list);
            i++;
        }
        if (tmp->elem_in_main_list == graph->end)
        {
            amt += 1;
            i++;
        }
        tmp = tmp->next;
    }
    amt = (graph->ants + amt - 1) / i;
    return (amt);
}

t_ants *init_ants()
{
    t_ants	*tmp;

    tmp = (t_ants *)malloc(sizeof(t_ant));
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->size = 0;
    return (tmp);
}

void    delete_ants(t_ants **ants)
{
    t_ant  *tmp;
    t_ant  *next;

    tmp = (*ants)->head;
    next = NULL;
    while (tmp)
    {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*ants);
    (*ants) = NULL;
}

void    addant(t_ants *ants, t_vertice_node *data, int number)
{
    t_ant *tmp;

    tmp = (t_ant*) malloc(sizeof(t_ant));
    if (tmp == NULL)
        exit(3);
    tmp->node = data;
    tmp->number = number;
    tmp->next = NULL;
    tmp->prev = ants->tail;
    if (ants->tail)
        ants->tail->next = tmp;
    ants->tail = tmp;
    if (ants->head == NULL)
        ants->head = tmp;
    ants->size++;
}
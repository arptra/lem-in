#include "queue.h"
#include "stdlib.h"

t_queue	            *init_queue()
{
    t_queue	*tmp;

    tmp = (t_queue *)malloc(sizeof(t_node));
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->size = 0;
    return (tmp);
}

void	            delete_queue(t_queue **queue)
{
    t_node  *tmp;
    t_node  *next;

    tmp = (*queue)->head;
    next = NULL;
    while (tmp)
    {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*queue);
    (*queue) = NULL;
}

void	            pushfront(t_queue *queue, t_vertice_node  *data)
{
    t_node *tmp;

    tmp = (t_node*) malloc(sizeof(t_node));
    if (tmp == NULL)
        exit(1);
    tmp->data = data;
    tmp->next = queue->head;
    tmp->prev = NULL;
    if (queue->head)
        queue->head->prev = tmp;
    queue->head = tmp;
    if (queue->tail == NULL)
        queue->tail = tmp;
    queue->size++;
}

t_vertice_node		*popfront(t_queue *queue)
{
    t_node          *prev;
    t_vertice_node  *tmp;

    if (queue->head == NULL)
        exit(2);
    prev = queue->head;
    queue->head = queue->head->next;
    if (queue->head)
        queue->head->prev = NULL;
    if (prev == queue->tail)
        queue->tail = NULL;
    tmp = prev->data;
    free(prev);
    queue->size--;
    return (tmp);
}

void	            pushback(t_queue *queue, t_vertice_node *data)
{
    t_node *tmp;

    tmp = (t_node*) malloc(sizeof(t_node));
    if (tmp == NULL)
        exit(3);
    tmp->data = data;
    tmp->next = NULL;
    tmp->prev = queue->tail;
    if (queue->tail)
        queue->tail->next = tmp;
    queue->tail = tmp;
    if (queue->head == NULL)
        queue->head = tmp;
    queue->size++;
}

t_vertice_node		*popback(t_queue *queue)
{
    t_node *next;
    t_vertice_node *tmp;

    if (queue->tail == NULL)
        exit(4);
    next = queue->tail;
    queue->tail = queue->tail->prev;
    if (queue->tail)
        queue->tail->next = NULL;
    if (next == queue->head)
        queue->head = NULL;
    tmp = next->data;
    free(next);
    queue->size--;
    return (tmp);
}

void		        delete_elem(t_queue *queue, t_node *elm)
{
    if (elm == NULL)
        exit(5);
    if (elm->prev)
        elm->prev->next = elm->next;
    if (elm->next)
        elm->next->prev = elm->prev;
    if (!elm->prev)
        queue->head = elm->next;
    if (!elm->next)
        queue->tail = elm->prev;
    free(elm);
    queue->size--;
}

t_vertice_node      *eject_min(t_queue *queue)
{
    t_node          *tmp;
    t_node          *del;
    t_vertice_node  *save;
    int             cur_min;

    tmp = queue->head;
    cur_min = tmp->data->dist;
    save = tmp->data;
    del = tmp;
    while (tmp)
    {
        if (tmp->data->dist < cur_min)
        {
            cur_min = tmp->data->dist;
            save = tmp->data;
            del = tmp;
        }
        tmp = tmp->next;
    }
    delete_elem(queue, del);
    return (save);
}


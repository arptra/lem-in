#include "dllutils.h"

t_dllist	*init_dllist()
{
	t_dllist	*tmp;
	
	tmp = (t_dllist *)malloc(sizeof(t_node));
	tmp->head = NULL;
	tmp->tail = NULL;
	tmp->size = 0;
	return (tmp);
}

void	delete_dllist(t_dllist **dllist)
{
	t_node  *tmp;
	t_node  *next;
	
	tmp = (*dllist)->head;
	next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->data);
		free(tmp);
		tmp = next;
	}
	free(*dllist);
    (*dllist) = NULL;
}

void	pushfront(t_dllist *dllist, t_room *value)
{
	t_node *tmp;
	
	tmp = (t_node*) malloc(sizeof(t_node) + sizeof(t_room));
	tmp->data = (t_room *)malloc((sizeof(t_room)));
	if (tmp == NULL)
		exit(1);
	tmp->data = value;
	tmp->next = dllist->head;
	tmp->prev = NULL;
	if (dllist->head)
		dllist->head->prev = tmp;
	dllist->head = tmp;
	if (dllist->tail == NULL)
		dllist->tail = tmp;
	dllist->size++;
}

t_room		*popfront(t_dllist *dllist)
{
	t_node *prev;
	t_room *tmp;

	if (dllist->head == NULL)
		exit(2);
	prev = dllist->head;
	dllist->head = dllist->head->next;
	if (dllist->head)
		dllist->head->prev = NULL;
	if (prev == dllist->tail)
		dllist->tail = NULL;
	tmp = prev->data;
	free(prev);
	dllist->size--;
	return (tmp);
}

void	pushback(t_dllist *dllist, t_room *value)
{
	t_node *tmp;
	
	tmp = (t_node*) malloc(sizeof(t_node));
	if (tmp == NULL)
		exit(3);
	tmp->data = value;
	tmp->next = NULL;
	tmp->prev = dllist->tail;
	if (dllist->tail)
		dllist->tail->next = tmp;
	dllist->tail = tmp;
	if (dllist->head == NULL)
		dllist->head = tmp;
	dllist->size++;
}

t_room		*popback(t_dllist *dllist)
{
	t_node *next;
	t_room	*tmp;
	
	if (dllist->tail == NULL)
		exit(4);
	next = dllist->tail;
	dllist->tail = dllist->tail->prev;
	if (dllist->tail)
		dllist->tail->next = NULL;
	if (next == dllist->head)
		dllist->head = NULL;
	tmp = next->data;
	free(next);
	dllist->size--;
	return (tmp);
}
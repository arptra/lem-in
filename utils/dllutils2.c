#include "dllutils.h"

t_node*	getnth(t_dllist *dllist, size_t index)
{
	t_node *tmp;
	
	tmp = NULL;
	size_t i;
	if (index < dllist->size / 2)
	{
		i = 0;
		tmp = dllist->head;
		while (tmp && i < index) {
			tmp = tmp->next;
			i++;
		}
	}
	else
		{
		i = dllist->size - 1;
		tmp = dllist->tail;
		while (tmp && i > index)
		{
			tmp = tmp->prev;
			i--;
		}
	}
	return tmp;
}

void	insert(t_dllist *dllist, size_t index, t_room *value)
{
	t_node *elm = NULL;
	t_node *ins = NULL;
	
	elm = getnth(dllist, index);
	if (elm == NULL)
		exit(5);
	ins = (t_node*)malloc(sizeof(t_node));
	ins->data = value;
	ins->prev = elm;
	ins->next = elm->next;
	if (elm->next)
		elm->next->prev = ins;
	elm->next = ins;
	if (!elm->prev)
		dllist->head = elm;
	if (!elm->next)
		dllist->tail = elm;
	dllist->size++;
}

t_room		*deletenth(t_dllist *dllist, size_t index)
{
	t_node	*elm;
	t_room 	*tmp;

	elm = getnth(dllist, index);
	if (elm == NULL)
		exit(5);
	if (elm->prev)
		elm->prev->next = elm->next;
	if (elm->next)
		elm->next->prev = elm->prev;
	tmp = elm->data;
	if (!elm->prev)
		dllist->head = elm->next;
	if (!elm->next)
		dllist->tail = elm->prev;
	free(elm);
	dllist->size--;
	return (tmp);
}


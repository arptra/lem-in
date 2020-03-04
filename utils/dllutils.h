#ifndef PUSH_SWAP_PUSH_SWAP_H
#define PUSH_SWAP_PUSH_SWAP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../lem-in.h"

typedef struct		s_node
{
	t_room			*data;
	struct s_node	*next;
	struct s_node	*prev;
}					t_node;

typedef struct		s_dllist
{
	size_t 			size;
	t_node			*head;
	t_node			*tail;
}					t_dllist;

t_dllist			*init_dllist();
void				delete_dllist(t_dllist **dllist);
void				pushfront(t_dllist *dllist, t_room *value);
t_room				*popfront(t_dllist *dllist);
void				pushback(t_dllist *dllist, t_room *value);
t_room				*popback(t_dllist *dllist);
t_node*				getnth(t_dllist *dllist, size_t index);
void				insert(t_dllist *dllist, size_t index, t_room *value);
t_room				*deletenth(t_dllist *dllist, size_t index);

#endif //PUSH_SWAP_PUSH_SWAP_H
#ifndef LEM_IN_H
#define LEM_IN_H

#include "libft/libft.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>


#define FILL_BUFF 100
typedef struct 		s_room
{
	int 			x;
	int 			y;
	char 			*name;
	int				start;
	int 			end;
}					t_room;

int		test();
void	fill_graph(int	fd);
#endif //LEM_IN_H

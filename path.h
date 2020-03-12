#ifndef PATH_H
#define PATH_H

#include "graph.h"

typedef struct      s_path
{
    t_vertice_node  *node;
    int             length;
    int             moves;
    struct s_path	*next;
    struct s_path	*prev;
}					t_path;

typedef struct		s_paths
{
    int             ants;
    int 			amt_paths;
    int             paths_len;
    int             num_moves;
    t_path		    *head;
    t_path		    *tail;
}					t_paths;

t_paths             *init_paths();
void                delete_paths(t_paths **paths);
void                addback(t_paths *paths, t_vertice_node  *data);
void                add_paths(t_graph *graph, t_paths *paths);

#endif //PATH_H

#include "path.h"

int     series(t_path *path)
{
    t_path *tmp;
    int     s;

    tmp = path;
    s = 0;
    while(tmp->prev)
    {
        s = s + (path->length - path->prev->length);
        tmp = tmp->prev;
    }
    return (s);
}

void    moves(t_paths *paths)
{
    t_path  *tmp;
    int     ants;
    int     moves;

    tmp = paths->head;
    ants = paths->ants;
    while (ants)
    {
        while (tmp)
        {
            if (ants > series(tmp))
                tmp->moves++;
            ants--;
            tmp = tmp->next;
        }
        tmp = paths->head;
        paths->num_moves++;
    }
    tmp = paths->head;
    /*
    while(tmp)
    {
        moves = (tmp->length - 1) + (tmp->length - tmp->moves);
        if (moves > paths->num_moves)
            paths->num_moves = moves;
        tmp = tmp->next;
    }
     */
}
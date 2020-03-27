#include "lem-in.h"

void    last_check(t_graph *graph, t_room *input)
{
    int flag;

    if ((flag = fill_graph(input)) < 0)
        ft_error(input, flag);
    else if (graph->start == NULL || graph->end == NULL || graph->start == graph->end)
        ft_error(input, -8);
    else if (ssp_finder(graph, graph->start) == 0)
        ft_error(input, -9);
}

t_paths    *save_paths(t_paths *paths, t_graph *graph, int *prev_moves)
{
    delete_paths(&paths);
    paths = init_paths();
    add_paths(graph, paths);
    paths->head = merge_sort(paths->head);
    *prev_moves = (paths->ants + paths->paths_len - 1) / paths->amt_paths;
    paths->num_moves = *prev_moves;
    return (paths);
}

t_paths    *solver(t_graph *graph, t_paths *paths)
{
    int start_to_end;
    int prev_moves;

    prev_moves = INT32_MAX;
    start_to_end = 0;
    while (1)
    {
        reset_dijkstra(graph);
        divide_vertex(graph);
        if (ssp_finder(graph, graph->start) == 0)
            break;
        if (connect_parents(graph->end) == 0)
            break;
        stick_toghether(graph);
        combine_paths(graph->start, graph->end);
        if (graph->end->parent == graph->start)
            start_to_end++;
        if (start_to_end > 1)
            break;
        if (cur_moves(graph) < prev_moves)
            paths = save_paths(paths, graph, &prev_moves);
    }
    return (paths);
}
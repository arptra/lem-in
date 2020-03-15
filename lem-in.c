#include "lem-in.h"

int	main(int argc, char **argv)
{
	int     fd;
    t_graph *graph;
    t_paths *paths;
    int     prev_moves;

    if (argc > 1)
        fd = open(argv[1], O_RDONLY);
    else
        fd = 0;

    graph = init_graph();
	fill_graph(fd, graph);
    if (graph->start == NULL && graph->end == NULL)
        ft_error(graph);
    if (ssp_finder(graph, graph->start) == 0)
        ft_error(graph);
    connect_parents(graph->end);

    prev_moves = INT32_MAX;
    paths = init_paths();
    while (1)
    {
        reset_dijkstra(graph);
        divide_vertex(graph);
        if (ssp_finder(graph, graph->start) == 0)
            break;
        connect_parents(graph->end);
        stick_toghether(graph);
        combine_paths(graph->start, graph->end);
        if (cur_moves(graph) < prev_moves)
        {
            delete_paths(&paths);
            paths = init_paths();
            add_paths(graph, paths);
            paths->head = merge_sort(paths->head);
            prev_moves = (paths->ants + paths->paths_len - 1) / paths->amt_paths;
            paths->num_moves = prev_moves;
        }
    }
    output(paths, graph);
    delete_paths(&paths);
	delete_graph(&graph);
	return (0);
}
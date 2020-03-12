#include "lem-in.h"

int	main(int argc, char **argv)
{
	int     fd;
    t_graph *graph;
    t_paths *paths;
    int     i;


    fd = open(argv[1], O_RDONLY);

    graph = init_graph();
	fill_graph(fd, graph);

    ssp_finder(graph, graph->start);
    connect_parents(graph->end);

    i = 3;
    while (1)
    {
        reset_dijkstra(graph);
        divide_vertex(graph);
        if (ssp_finder(graph, graph->start) == 0)
            break;
        connect_parents(graph->end);
        combine_paths(graph->start, graph->end);
        stick_toghether(graph);
    }

    paths = init_paths();
    add_paths(graph, paths);
    paths->head = merge_sort(paths->head);
    moves(paths);
    delete_paths(&paths);


    print_paths(graph->start);
	delete_graph(&graph);
	return (0);
}
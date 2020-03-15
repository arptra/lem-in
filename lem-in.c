#include "lem-in.h"

int	main(int argc, char **argv)
{
	int     fd;
    t_graph *graph;
    t_paths *paths;
    int     prev_moves;

	fd = open(argv[1], O_RDONLY);

    graph = init_graph();
	fill_graph(fd, graph);

    ssp_finder(graph, graph->start);
    // connect_parents(graph->end);
	graph->end->parent ? 1 : ft_error();
    backward_path(graph);
    //print_ssp(graph);
    print_paths(graph->start);
    /*
	test = find_elem(graph, "11");
	//devide vertex that pass on find path
	vertex_dup(graph, test);
    print_graph(graph);
	
    vertex_dup(graph, test->to);
    print_graph(graph);
	*/
    // i = 10;
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
    //print_paths(graph->start);
    delete_paths(&paths);
	delete_graph(&graph);
	return (0);
}
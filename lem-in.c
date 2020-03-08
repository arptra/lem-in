#include "lem-in.h"

int	main(int argc, char **argv)
{
	int     fd;
	t_vertice_node  *test;
    t_graph *graph;

    fd = open(argv[1], O_RDONLY);

    graph = init_graph();
	fill_graph(fd, graph);
	print_graph(graph);

    ssp_finder(graph, graph->start);
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

    vertex_dup(graph, test->to->to);
    print_graph(graph);
    //
    reset_dijkstra(graph);
    ssp_finder(graph, graph->start);
    backward_path(graph);
    print_paths(graph->start);
     */
	delete_graph(&graph);
	return (0);
}
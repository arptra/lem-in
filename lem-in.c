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
	graph->end->parent ? 1 : ft_error();
    backward_path(graph);
    /*
    print_ssp(graph);


	test = find_elem(graph, "11");
	vertex_dup(graph, test);
    print_graph(graph);
     */

    print_paths(graph->start);
	delete_graph(&graph);
	return (0);
}
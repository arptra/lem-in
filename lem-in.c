#include "lem-in.h"

int	main(int argc, char **argv)
{
	int     fd;
    t_graph *graph;

    fd = open(argv[1], O_RDONLY);

    graph = init_graph();
	fill_graph(fd, graph);
	print_graph(graph);

    ssp_finder(graph);
    print_ssp(graph);
	delete_graph(&graph);
	return (0);
}
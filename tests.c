#include "lem-in.h"

/*
 *
 * 		    0 ---- 1 ----
 *			|     /|      \
 *			|    / |       \
 *          |   /  |        2
 *          |  /   |       /
 * 		    | /    |      /
 *          4 ---- 3 ----
 */

// Driver program to test graph functions
int test()
{
	// create the graph given in above fugure
	int		V;
	t_graph	*graph;
	
	V = 5;
	graph = create_graph(V);
	add_edge(graph, 0, 1);
	add_edge(graph, 0, 4);
	add_edge(graph, 1, 2);
	add_edge(graph, 1, 3);
	add_edge(graph, 1, 4);
	add_edge(graph, 2, 3);
	add_edge(graph, 3, 4);
	
	// print the adjacency list representation of the above graph
	print_graph(graph);
	return (0);
}
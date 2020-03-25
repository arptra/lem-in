#include "lem-in.h"

int	main(int argc, char **argv)
{
	int     fd;
	int     flag;
	int     start_to_end;
    t_graph *graph;
    t_paths *paths;
    t_data  *data;
    t_room  *input;
    int     prev_moves;

    if (argc > 1)
        fd = open(argv[1], O_RDONLY);
    else
        fd = 0;

    graph = init_graph();
    data = init_data();

    /* init input */

    input = (t_room *)malloc(sizeof(t_room));
    input->graph = graph;
    input->data = data;
    input->line = NULL;
    input->src = NULL;
    input->dst = NULL;
    input->name = NULL;
    input->start = 0;
    input->end = 0;
    input->x = 0;
    input->y = 0;
    input->fd = fd;
    input->i = 0;

    /*************/



	if ((flag = fill_graph(input)) < 0)
        ft_error(input, flag);
	else if (graph->start == NULL || graph->end == NULL || graph->start == graph->end)
        ft_error(input, -8);
	else if (ssp_finder(graph, graph->start) == 0)
        ft_error(input, -9);



	connect_parents(graph->end);
    prev_moves = INT32_MAX;
    start_to_end = 0;
    paths = init_paths();
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
        {
            delete_paths(&paths);
            paths = init_paths();
            add_paths(graph, paths);
            paths->head = merge_sort(paths->head);
            prev_moves = (paths->ants + paths->paths_len - 1) / paths->amt_paths;
            paths->num_moves = prev_moves;
        }
    }
    output(paths, input->data);
    delete_data(&data);
    delete_paths(&paths);
	delete_graph(&graph);
	free(input);
	return (0);
}
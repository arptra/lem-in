#include "lem-in.h"

int	main(int argc, char **argv)
{
	int     fd;
    t_graph *graph;
    t_paths *paths;
    t_data  *data;
    t_data  *head;
    t_room  *input;
    int     prev_moves;

    if (argc > 1)
        fd = open(argv[1], O_RDONLY);
    else
        fd = 0;

    graph = init_graph();
    data = init_data();
    head = data;

    /* init input */

    input = (t_room *)malloc(sizeof(t_room));
    input->graph = graph;
    input->data = data;
    input->line = NULL;
    input->name = NULL;
    input->start = 0;
    input->end = 0;
    input->x = 0;
    input->y = 0;
    input->fd = fd;

    /*************/

	if (fill_graph(input) < 0)
    {
        ft_putstr_fd("ERROR",(int)STDERR_FILENO);
        //ft_putstr("ERROR\n");
        delete_data(&data);
        delete_graph(&graph);
        free(input);
        return (0);
    }
	else if (graph->start == NULL || graph->end == NULL || graph->start == graph->end)
    {
        //ft_putstr("ERROR\n");
        ft_putstr_fd("ERROR",(int)STDERR_FILENO);
        delete_data(&data);
        delete_graph(&graph);
        free(input);
        return (0);
    }
	else if (ssp_finder(graph, graph->start) == 0)
    {
        //ft_putstr("ERROR\n");
        ft_putstr_fd("ERROR",(int)STDERR_FILENO);
        delete_data(&data);
        delete_graph(&graph);
        free(input);
        return (0);
    }

	connect_parents(graph->end);

    prev_moves = INT32_MAX;
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
    output(paths, head);
    delete_data(&data);
    delete_paths(&paths);
	delete_graph(&graph);
	free(input);
	return (0);
}
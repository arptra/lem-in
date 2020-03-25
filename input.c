#include "lem-in.h"

void   buf_clr(char buf[], int size)
{
    int i;

    i = -1;
    while (++i < size)
        buf[i] = 0;
}

static int 	get_coord(const char *line, int *numb, int *check)
{
	int i;
	int j;
	int flag;
	char buf[FILL_BUFF];
	
	i = 0;
	j = 0;
	flag = 0;
	while (line[i] && line[i] == ' ')
		i++;
    buf_clr(buf, FILL_BUFF);
	while (line[i] != '\0' && line[i] != ' ')
		buf[j++] = line[i++];
	buf[i] = '\0';
    *numb = int_checker(buf, &flag);
    if (flag || digit_checker(buf) < 0)
        *check = -1;
	return (i);
}

static void	reset_input(t_room *input)
{
	input->x = 0;
	input->y = 0;
	input->name = NULL;
	input->start = 0;
	input->end = 0;
}

static int	parse_line(t_room *input)
{
	int		i;
	int     j;
	int     flag;
	char	buf[FILL_BUFF];
	char    *line;

	i = -1;
	flag = 0;
	line = input->line;
	buf_clr(buf, FILL_BUFF);
	while (line[++i] != '\0' && line[i] != ' ' && line[i] != '-')
		buf[i] = line[i];
	buf[i] = '\0';
	if (line[i] == ' ')
	{
	    if (buf[0] == 'L' || buf[0] == '#')
            ft_error(input, -10);
        input->name = ft_strdup(buf);
        i = i + get_coord(&line[i], &input->x,  &flag);
        if (flag < 0)
            ft_error(input, -1);
        i = i + get_coord(&line[i], &input->y,  &flag);
        if (flag < 0)
            ft_error(input, -1);
        while (line[i] && line[i] == ' ')
            i++;
        if (line[i] != '\0')
            ft_error(input, -2);
        if (find_elem(input->graph, input) != NULL)
            ft_error(input, -3);
        add_vertex_node(input->graph, input);
    }
	else if (line[i] == '-')
    {
	    j = 0;
	    input->src = ft_strdup(buf);
        if (buf[0] == 'L')
            ft_error(input, -11);
        buf_clr(buf, FILL_BUFF);
	    while (line[++i] != '\0')
	        buf[j++] = line[i];
	    input->dst = ft_strdup(buf);
        if (buf[0] == 'L')
            ft_error(input, -12);
        if (add_niegh_and_link(input->graph, input->src, input->dst, 1) == 0)
            ft_error(input, -4);
        if (add_niegh_and_link(input->graph, input->dst, input->src, 1) == 0)
            ft_error(input, -4);
        free(input->src);
        free(input->dst);
    }
	else
        return (-1);
    return (1);
}

int	    fill_graph(t_room *input)
{
	t_data  *data;
	t_graph *graph;
	int      fd;
	int      i;
	int      flag;

	i = 0;
	flag = 0;
	fd = input->fd;
	data = input->data;
	graph = input->graph;
	reset_input(input);
	while(get_next_line(fd, &input->line) > 0)
	{
        if (i == 0)
            graph->ants = chck_ant(input);
        else if (input->line[0] == '\0')
            flag = -7;
        else if (!ft_strcmp("##start", input->line) && graph->start == NULL)
			input->start = 1;
        else if (!ft_strcmp("##start", input->line) && graph->start != NULL)
		    flag = -5;
        else if (!ft_strcmp("##end", input->line) && graph->end == NULL)
			input->end = 1;
        else if (!ft_strcmp("##end", input->line) && graph->end != NULL)
            flag = -5;
        else if (input->line[0] == '#' && input->line[1] == '#' &&
                (input->start != 0 || input->end != 0))
            flag = -6;
        else if (input->line[0] == '#')
            ;
        else
		{
			flag = parse_line(input);
			reset_input(input);
		}
		data = add_data(data, input->line);
		free(input->line);
		input->i = ++i;
        if (flag < 0 || graph->ants < 0)
            return(flag);
	}
    if (flag < 0 || graph->ants < 0)
        return(flag);
    return (1);
}

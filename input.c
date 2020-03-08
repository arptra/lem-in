#include "lem-in.h"

void   buf_clr(char buf[], int size)
{
    int i;

    i = -1;
    while (++i < size)
        buf[i] = 0;
}

static int 	get_coord(const char *line, int *numb)
{
	int i;
	int j;
	char buf[FILL_BUFF];
	
	i = 0;
	j = 0;
	while (line[i] && line[i] == ' ')
		i++;
    buf_clr(buf, FILL_BUFF);
	while (line[i] != '\0' && line[i] != ' ')
		buf[j++] = line[i++];
	buf[i] = '\0';
	*numb = ft_atoi(buf);
	ft_chck_arg((*numb = ft_atoi(buf)), buf) ? ft_error() : *numb;
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

static void	parse_line(char *line, t_room *input, t_graph *graph)
{
	int		i;
	int     j;
	char	buf[FILL_BUFF];
	char    *src;
	char    *dst;

	i = -1;
	buf_clr(buf, FILL_BUFF);
	while (line[++i] != '\0' && line[i] != ' ' && line[i] != '-')
		buf[i] = line[i];
	buf[i] = '\0';
	if (line[i] == ' ')
	{
        (buf[0] != 'L' && buf[0] != '\0' && !ft_strchr(buf,'-')) ?
			(input->name = ft_strdup(buf)) : ft_error();
        i = i + get_coord(&line[i], &input->x);
        i = i + get_coord(&line[i], &input->y);
		ft_chck_nm_w_crdnts(input, graph) ? ft_error() : 1;
        add_vertex_node(graph, input); // add new vertex in graph
    }
	else if (line[i] == '-')
    {
		(!graph->start || !graph->end) ? ft_error() : 1;
	    j = 0;
	    src = ft_strdup(buf);
        buf_clr(buf, FILL_BUFF);
	    while (line[++i] != '\0')
	        buf[j++] = line[i];
	    dst = ft_strdup(buf);
		(!ft_chk_name(dst, graph) || !ft_chk_name(src, graph)) ? ft_error() : 1;
		// (ft_chk_name(dst, graph) && ft_chk_name(src, graph)) ? 1 : ft_error();
        add_niegh_and_link(graph, src, dst, 1); // add new link between SRC and DST
        add_niegh_and_link(graph, dst, src, 1); // and vice verse
        free(src);
        free(dst);
    }
}

void	    fill_graph(int fd, t_graph *graph)
{
	char	*line;
	t_room	*input;
	int      i;

	i = 0;
	input = (t_room *)malloc(sizeof(t_room));
	reset_input(input);
	get_next_line(fd, &line);
	(ft_chck_arg((graph->ants = ft_atoi(line)), line) || graph->ants < 0) ?
		ft_error() : free(line);
	while(get_next_line(fd, &line))
	{
		ft_putendl(line);
		if (!ft_strcmp("##start", line))
			graph->start ? (input->start = 1) : ft_error();
		else if (!ft_strcmp("##end", line))
			graph->end ? (input->end = 1) : ft_error();
			(!graph->start && !input->end) ? (input->start = 1) : ft_error();
		else if (!ft_strcmp("##end", line))
			(!graph->end && !input->start) ? (input->end = 1) : ft_error();
		else if (line[0] == '#')
			;
		else if (i == 0)
            graph->ants = ft_atoi(line);
		else
		{
			parse_line(line, input, graph);
			reset_input(input);
		}
		free(line);
		i++;
	}
	free(input);
}
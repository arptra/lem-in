#include "lem-in.h"

static int 	get_coord(const char *line, int *numb)
{
	int i;
	int j;
	char buf[FILL_BUFF];
	
	i = 0;
	j = 0;
	while (line[i] && line[i] == ' ')
		i++;
	ft_strclr(buf);
	while (line[i] != '\0' && line[i] != ' ')
		buf[j++] = line[i++];
	buf[i] = '\0';
	*numb = ft_atoi(buf);
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
	ft_strclr(buf);
	while (line[++i] != '\0' && line[i] != ' ' && line[i] != '-')
		buf[i] = line[i];
	buf[i] = '\0';
	if (line[i] == ' ')
	{
        input->name = ft_strdup(buf);
        i = i + get_coord(&line[i], &input->x);
        i = i + get_coord(&line[i], &input->y);
        add_vertice_node(graph, input);
    }
	else if (line[i] == '-')
    {
	    j = 0;
	    src = ft_strdup(buf);
	    ft_strclr(buf);
	    while (line[++i] != '\0')
	        buf[j++] = line[i];
	    dst = ft_strdup(buf);
        add_niegh_and_link(graph, src, dst);
    }
}

void	    fill_graph(int fd, t_graph *graph)
{
	char	*line;
	t_room	*input;

	input = (t_room *)malloc(sizeof(t_room));
	reset_input(input);
	while(get_next_line(fd, &line))
	{
		ft_putendl(line);
		if (!ft_strcmp("##start", line))
			input->start = 1;
		else if (!ft_strcmp("##end", line))
			input->end = 1;
		else if (line[0] == '#')
			;
		else
		{
			parse_line(line, input, graph);
			reset_input(input);
		}
		free(line);
	}
	free(input);
}
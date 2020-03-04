#include "lem-in.h"
#include "utils/dllutils.h"

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

static void	parse_line(char *line, t_room *input)
{
	int		i;
	char	buf[FILL_BUFF];
	
	i = -1;
	ft_strclr(buf);
	while (line[++i] != '\0' && line[i] != ' ')
		buf[i] = line[i];
	buf[i] = '\0';
	input->name = ft_strdup(buf);
	i = i + get_coord(&line[i], &input->x);
	i = i + get_coord(&line[i], &input->y);
}

void	fill_graph(int fd)
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
			parse_line(line, input);
			reset_input(input);
		}
		free(line);
	}
}
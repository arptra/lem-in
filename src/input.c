/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 18:01:42 by student           #+#    #+#             */
/*   Updated: 2020/03/27 18:02:09 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	buf_clr(char buf[], int size)
{
	int	i;

	i = -1;
	while (++i < size)
		buf[i] = 0;
}

int		parse_line(t_room *input)
{
	int		i;
	char	buf[FILL_BUFF];
	char	*line;

	i = -1;
	line = input->line;
	buf_clr(buf, FILL_BUFF);
	while (line[++i] != '\0' && line[i] != ' ' && line[i] != '-')
		buf[i] = line[i];
	buf[i] = '\0';
	if (line[i] == ' ')
		create_vertex(input, i, buf);
	else if (line[i] == '-')
		create_link(input, i, buf);
	else
		return (-1);
	return (1);
}

void	get_ant(t_room *input)
{
	int	ants;

	ants = chck_ant(input);
	if (input->graph->ants == 0 && ants > 0)
		input->graph->ants = ants;
	else if (input->graph->ants == 0 && ants < 0)
	{
		ft_putstr_fd("ERROR at line ", (int)STDERR_FILENO);
		ft_putnbr_fd(input->i, (int)STDERR_FILENO);
		ft_putstr_fd(" bad ants", (int)STDERR_FILENO);
		free(input->line);
        delete_data(&input->data);
        delete_graph(&input->graph);
        free(input);
        exit(-1);
	}
}

void	check_and_parse(t_room *input, int *flag)
{
	t_graph	*graph;

	graph = input->graph;
	if (input->start == 0 && graph->start == NULL && input->line[0] != '#'
			&& graph->ants == 0)
		get_ant(input);
	else if (input->line[0] == '\0')
		*flag = -7;
	else if (!ft_strcmp("##start", input->line) && graph->start == NULL)
		input->start = 1;
	else if (!ft_strcmp("##start", input->line) && graph->start != NULL)
		*flag = -5;
	else if (!ft_strcmp("##end", input->line) && graph->end == NULL)
		input->end = 1;
	else if (!ft_strcmp("##end", input->line) && graph->end != NULL)
		*flag = -6;
	else if (input->line[0] == '#')
		;
	else
	{
		*flag = parse_line(input);
		reset_input(input);
	}
}

int		fill_graph(t_room *input)
{
	t_data	*data;
	t_graph	*graph;
	int		flag;

	flag = 0;
	data = input->data;
	graph = input->graph;
	reset_input(input);
	while (get_next_line(input->fd, &input->line) > 0)
	{
		check_and_parse(input, &flag);
		data = add_data(data, input->line);
		free(input->line);
		input->i++;
		if (flag < 0 || ((flag = graph->ants) <= 0 && input->start == 1))
			return (flag);
	}
	if (flag < 0 || graph->ants < 0)
		return (flag);
	return (1);
}

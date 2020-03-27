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

#include "lem-in.h"

void	buf_clr(char buf[], int size)
{
	int	i;

	i = -1;
	while (++i < size)
		buf[i] = 0;
}

int		get_coord(const char *line, int *numb, int *check)
{
	int		i;
	int		j;
	int		flag;
	char	buf[FILL_BUFF];

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

void	reset_input(t_room *input)
{
	input->x = 0;
	input->y = 0;
	input->name = NULL;
	input->start = 0;
	input->end = 0;
}

void	create_vertex(t_room *input, int i, char buf[])
{
	int		flag;
	char	*line;

	flag = 0;
	line = input->line;
	if (buf[0] == 'L' || buf[0] == '#')
		ft_error(input, -10);
	input->name = ft_strdup(buf);
	i = i + get_coord(&line[i], &input->x, &flag);
	if (flag < 0)
		ft_error(input, -1);
	i = i + get_coord(&line[i], &input->y, &flag);
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

void	create_link(t_room *input, int i, char buf[])
{
	int		j;
	char	*line;

	j = 0;
	line = input->line;
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

void	check_and_parse(t_room *input, int *flag)
{
	t_graph	*graph;

	graph = input->graph;
	if (input->start == 0 && graph->start == NULL && input->line[0] != '#')
		graph->ants = chck_ant(input);
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

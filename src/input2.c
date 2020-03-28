/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 01:50:21 by student           #+#    #+#             */
/*   Updated: 2020/03/28 01:50:23 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

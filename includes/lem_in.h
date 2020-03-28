/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 02:40:45 by student           #+#    #+#             */
/*   Updated: 2020/03/28 02:40:47 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "graph.h"
# include "queue.h"
# include "path.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

# define FILL_BUFF 100

int		get_coord(const char *line, int *numb, int *check);
void	reset_input(t_room *input);
void	create_vertex(t_room *input, int i, char buf[]);
void	create_link(t_room *input, int i, char buf[]);
void	buf_clr(char buf[], int size);
int		parse_line(t_room *input);
void	get_ant(t_room *input);
void	check_and_parse(t_room *input, int *flag);
int		fill_graph(t_room *input);
int		ssp_finder(t_graph *graph, t_vertice_node *node);
void	relabele_vertices(t_vertice_node *start, t_queue *queue);
void	ft_error(t_room *input, int err);
int		int_checker(char *str, int *flag);
int		digit_checker(char *str);
int		chck_ant(t_room *input);
void	error_type(int err);
void	output(t_paths *paths, t_data *head);
void	print_ant(int ant, char *name);
int		put_ant(t_paths *paths, t_ants *ants, int i);
void	print_line(t_ants *ants);
void	last_check(t_graph *graph, t_room *input);
t_paths	*save_paths(t_paths *paths, t_graph *graph, int *prev_moves);
t_paths	*solver(t_graph *graph, t_paths *paths);
#endif

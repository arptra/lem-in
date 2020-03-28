/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/28 02:45:50 by student           #+#    #+#             */
/*   Updated: 2020/03/28 02:45:53 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H
# include "graph.h"

typedef struct		s_path
{
	t_vertice_node	*node;
	int				length;
	int				moves;
	struct s_path	*next;
	struct s_path	*prev;
}					t_path;

typedef struct		s_paths
{
	int				ants;
	int				amt_paths;
	int				paths_len;
	int				num_moves;
	t_path			*head;
	t_path			*tail;
}					t_paths;

typedef struct		s_ant
{
	t_vertice_node	*node;
	int				number;
	struct s_ant	*next;
	struct s_ant	*prev;
}					t_ant;

typedef struct		s_ants
{
	int				size;
	t_ant			*head;
	t_ant			*tail;
}					t_ants;

t_paths				*init_paths(void);
void				delete_paths(t_paths **paths);
void				addback(t_paths *paths, t_vertice_node *data);
void				add_paths(t_graph *graph, t_paths *paths);
int					path_len(t_vertice_node *node);
int					cur_moves(t_graph *graph);
void				save_path(t_vertice_node *node);
t_ants				*init_ants();
void				delete_ants(t_ants **ants);
void				addant(t_ants *ants, t_vertice_node *data, int number);
void				moves(t_paths *paths);
t_path				*split(t_path *head);
t_path				*merge(t_path *first, t_path *second);
t_path				*merge_sort(t_path *head);
#endif

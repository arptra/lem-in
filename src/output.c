/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 18:31:44 by student           #+#    #+#             */
/*   Updated: 2020/03/27 18:31:47 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_ant(int ant, char *name)
{
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(name);
}

int		put_ant(t_paths *paths, t_ants *ants, int i)
{
	t_path	*tmp;
	t_ant	*ant;

	tmp = paths->head;
	ant = ants->head;
	while (ant)
	{
		if (ant->node)
			ant->node = ant->node->save;
		ant = ant->next;
	}
	while (tmp && tmp->moves > 0)
	{
		addant(ants, tmp->node, i++);
		tmp->moves--;
		tmp = tmp->next;
	}
	return (i);
}

void	print_line(t_ants *ants)
{
	t_ant	*tmp;
	char	*name;

	tmp = ants->head;
	while (tmp)
	{
		if (tmp->node)
		{
			name = tmp->node->name;
			print_ant(tmp->number, name);
			if (tmp->next == NULL)
				ft_putchar('\n');
			else
				ft_putchar(' ');
		}
		tmp = tmp->next;
	}
}

void	output(t_paths *paths, t_data *head)
{
	t_ants	*ants;
	int		i;

	i = 1;
	print_data(head);
	ants = init_ants();
	moves(paths);
	ft_putchar('\n');
	while (paths->num_moves--)
	{
		i = put_ant(paths, ants, i);
		print_line(ants);
	}
	delete_ants(&ants);
}

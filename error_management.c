/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 18:44:07 by student           #+#    #+#             */
/*   Updated: 2020/03/27 18:44:09 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

void	error_type(int err)
{
	if (err == -1)
		ft_putstr_fd(" bad coordinates", (int)STDERR_FILENO);
	else if (err == -2)
		ft_putstr_fd(" too many parameters", (int)STDERR_FILENO);
	else if (err == -3)
		ft_putstr_fd(" vertex already exist or duplicate coordinates",
				(int)STDERR_FILENO);
	else if (err == -4)
		ft_putstr_fd(" link already exist or vertex doesn't exist",
				(int)STDERR_FILENO);
	else if (err == -5)
		ft_putstr_fd(" start or end already exist", (int)STDERR_FILENO);
	else if (err == -6)
		ft_putstr_fd(" duplicate start or end", (int)STDERR_FILENO);
	else if (err == -7)
		ft_putstr_fd(" empty line", (int)STDERR_FILENO);
	else if (err == -8)
		ft_putstr_fd(" no start or end", (int)STDERR_FILENO);
	else if (err == -9)
		ft_putstr_fd(" path from to start to end not found",
				(int)STDERR_FILENO);
	else if (err < -9)
		ft_putstr_fd(" name start with L", (int)STDERR_FILENO);
}

void	ft_error(t_room *input, int err)
{
	ft_putstr_fd("ERROR at line ", (int)STDERR_FILENO);
	ft_putnbr_fd(input->i, (int)STDERR_FILENO);
	error_type(err);
	ft_putstr_fd("\n", (int)STDERR_FILENO);
	if (err > -4)
		free(input->name);
	else if (err == -4)
	{
		free(input->src);
		free(input->dst);
	}
	else if (err == -11)
		free(input->src);
	else if (err == -12)
	{
		free(input->src);
		free(input->dst);
	}
	delete_data(&input->data);
	delete_graph(&input->graph);
	free(input);
	exit(-1);
}

int		int_checker(char *str, int *flag)
{
	int	check;

	check = ft_atoi(str);
	*flag = 0;
	if (check == 0)
		if (ft_strcmp(str, "0\0") != 0)
			*flag = 1;
	return (check);
}

int		digit_checker(char *str)
{
	int	i;
	int	sign;

	i = -1;
	sign = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '-' && i == 0)
			sign++;
		else if (!ft_isdigit(str[i]))
			return (-1);
	}
	if (sign > 1)
		return (-2);
	return (1);
}

int		chck_ant(t_room *input)
{
	int	flag;
	int	value;

	value = int_checker(input->line, &flag);
	if (flag || digit_checker(input->line) < 0 || value < 0)
		return (-1);
	return (value);
}

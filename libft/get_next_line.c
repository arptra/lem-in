/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgerda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 17:35:34 by bgerda            #+#    #+#             */
/*   Updated: 2020/03/28 22:02:37 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		line_copy(t_list **list, char *buf, int i)
{
	char	*str;
	t_list	*cur;

	cur = *list;
	if (!(str = ft_strnew(ft_strlen(cur->content))))
		return (-1);
	ft_strncpy(str, cur->content, ft_strlen(cur->content));
	free(cur->content);
	buf[i] = '\0';
	if (!(cur->content = ft_strjoin(str, buf)))
		return (-1);
	free(str);
	return (1);
}

static	t_list	*getfd(t_list **list, int fd)
{
	t_list	*cur;

	cur = *list;
	fd = fd + 1;
	while (cur != NULL)
	{
		if ((int)cur->content_size == fd)
			return (cur);
		cur = cur->next;
	}
	ft_lstadd(list, ft_lstnew("\0", fd));
	cur = *list;
	return (cur);
}

static int		get_line(t_list **list, char ***line)
{
	char	*tmp;
	char	*save;
	t_list	*cur;
	int		i;

	i = 0;
	cur = *list;
	tmp = (char*)cur->content;
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i++;
	if (!(save = ft_strnew(i)))
		return (-1);
	if (!(**line = ft_strjoin(ft_strncpy(save, tmp, i), "\0")))
		return (-1);
	free(save);
	if (tmp[i] == '\n')
		++i;
	if (!(save = ft_strnew(ft_strlen(&tmp[i]))))
		return (-1);
	ft_strncpy(save, &tmp[i], ft_strlen(&tmp[i]));
	if (!(cur->content = ft_strjoin(save, "\0")))
		return (-1);
	free(save);
	free(tmp);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*list;
	t_list			*cur;
	int				flag;
	int				i;

	flag = 0;
	i = 0;
	if (fd < 0 || (read(fd, buf, 0) < 0) || !line || !(cur = getfd(&list, fd)))
		return (-1);
	while (flag == 0)
	{
		if (ft_strchr(cur->content, '\n') == NULL)
			if ((i = read(fd, buf, BUFF_SIZE)) < 0
					|| line_copy(&cur, buf, i) == -1)
				return (-1);
		if ((ft_strchr(cur->content, '\n') == NULL && (i > 0 && i < BUFF_SIZE))
				|| (ft_strchr(cur->content, '\n') != NULL)
				|| (i == 0 && ft_strlen(cur->content) != 0))
			flag = get_line(&cur, &line);
		else if (ft_strlen(cur->content) == 0)
			return (ft_content_free(list));
	}
	return (flag);
}

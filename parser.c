//
// Created by Bears Gerda on 14/03/2020.
//
#include "graph.h"
#include "libft/libft.h"

t_data    *init_data()
{
    t_data  *tmp;

    tmp = (t_data *)malloc(sizeof(t_data));
    tmp->str = NULL;
    tmp->next = NULL;
    return (tmp);
}

t_data    *add_data(t_data *data, char *str)
{
    t_data *tmp;

    tmp = data;
    if (tmp->str == NULL)
        tmp->str = ft_strdup(str);
    else
    {
        tmp = (t_data *)malloc(sizeof(t_data));
        tmp->str = ft_strdup(str);
        tmp->next = NULL;
        data->next = tmp;
    }
    return (tmp);
}

void      print_data(t_data *head)
{
    while (head)
    {
        ft_putendl(head->str);
        head = head->next;
    }
}

void      delete_data(t_data **data)
{
    t_data  *tmp;
    t_data  *next;

    tmp = *data;
    next = NULL;
    while (tmp)
    {
        next = tmp->next;
        free(tmp->str);
        free(tmp);
        tmp = next;
    }
    *data = NULL;
}

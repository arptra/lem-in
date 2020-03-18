#include "lem-in.h"

void	ft_error(t_room *input)
{
    delete_graph(&input->graph);
    delete_data(&input->data);
    if (input->name)
        free(input->name);
    free(input);
    //ft_putstr_fd("ERROR",(int)STDERR_FILENO);
    ft_putstr("ERROR\n"); //for script test;
    exit (-1);
}

int     int_checker(char *str, int *flag)
{
    int check;

    check = ft_atoi(str);
    *flag = 0;
    if (check == 0)
        if (ft_strcmp(str, "0\0") != 0)
            *flag = 1;
    return (check);
}

int     digit_checker(char *str)
{
    int i;
    int sign;

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

int     chck_ant(t_room *input)
{
    int flag;
    int value;

    value = int_checker(input->line, &flag);
    if (flag || digit_checker(input->line) < 0 || value < 0)
        //ft_error(input);
        return (-1);
    return (value);
}
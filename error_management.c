#include "lem-in.h"

int			ft_chck_arg(int intgr, const char *strng)
{
	return (ft_strcmp(ft_itoa(intgr),strng));
}

void		ft_error()
{
	ft_putstr_fd("ERROR",(int)STDERR_FILENO);
	exit (-1);
}

int			ft_chck_nm_w_crdnts(t_room *input, t_graph *graph)
{
	while (graph->names->next && graph->crdnts->next)
	{
		if (!ft_strcmp(input->name, graph->names->name) || (
			input->x == graph->crdnts->x &&
			input->y == graph->crdnts->y))
			return (1);
		graph->names = graph->names->next;
		graph->crdnts = graph->crdnts->next;
	}
	if (graph->names->next || graph->crdnts->next)
		return (1);
	if (!ft_strcmp(input->name, graph->names->name) || (
		input->x == graph->crdnts->x &&
		input->y == graph->crdnts->y))
		return (1);
	graph->names->next = ft_nw_name(input->name);
	graph->crdnts->next = ft_nw_crdnts(input->x, input->y);
	return (0);
}

int			ft_chk_name(const char *name, t_graph *graph)
{
	while (graph->names)
	{
		if (!ft_strcmp(name, graph->names->name))
			return (1);
		graph->names = graph->names->next;
	}
	return (0);	
}

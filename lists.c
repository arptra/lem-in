#include "lem-in.h"

t_names			*ft_nw_name(const char *name)
{
	t_names			*nw;

	if ((nw = (t_names*)ft_memalloc(sizeof(t_names))))
	{
		if (!name)
			nw->name = NULL;
		else
		{
			if (!(nw->name = (char*)ft_memalloc(ft_strlen(name))))
			{
				free(nw);
				return (NULL);
			}
			ft_strcpy(nw->name, name);
		}
		nw->next = NULL;
	}
	return (nw);
}

t_crdnts		*ft_nw_crdnts(const int x, const int y)
{
	t_crdnts		*nw;

	if ((nw = (t_crdnts*)ft_memalloc(sizeof(t_crdnts))))
	{
		nw->x = x;
		nw->y = y;
		nw->next = NULL;
	}
	return (nw);
}

void		ft_del_names(t_names **names)
{
	t_names			*tmp1;
	t_names			*tmp2;

	tmp1 = *names;
	while (tmp1)
	{
		tmp2 = tmp1;
		free(tmp1->name);
		tmp1 = tmp2->next;
		free(tmp2);
	}
	*names = NULL;
}

void		ft_del_crdnts(t_crdnts **crdnts)
{
	t_crdnts		*tmp1;
	t_crdnts		*tmp2;

	tmp1 = *crdnts;
	while(tmp1)
	{
		tmp2 = tmp1;
		tmp1 = tmp2->next;
		free(tmp2);
	}
	*crdnts = NULL;
}

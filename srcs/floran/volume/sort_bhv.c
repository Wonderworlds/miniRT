/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bhv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:54:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/25 19:16:34 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"

static t_list *get_furthest_vol(const t_pos *pos, t_list *vols)
{
	double	dst;
	double	tmp;
	t_list	*ret;
	t_list	*index;

	if (!vols)
		return (NULL);
	index = vols;
	dst = dist_ab(pos, &(((t_vol *)(index->content))->box.center));
	ret = index;
	while (index)
	{
		tmp = dist_ab(pos, &(((t_vol *)(index->content))->box.center));
		if (tmp < dst)
		{
			dst = tmp;
			ret = index;
		}
		index = index->next;
	}
	return (ret);
}

static int tab_fill(t_list **vols, t_list origin)
{
	unsigned int	index;
	unsigned int	j;
	unsigned int	i;
	double			dist;
	t_vol			*tmp;

		return (1);
	index = 0;
	while (index < size)
	{
		dist = dist_ab(&origin, &(*vols)[index].box.center);
		j = 0;
		while (j <= index)
		{
			if (j == index)
				tab[index] = vols[index];
			else if (dist > dist_ab(&origin, &(*tab)[j].box.center))
			{
				i = index + 1;
				while (--i > j)
					tab[i] = tab[i - 1];
				tab[i] = vols[index];
				break ;
			}
			else
				j++;
		}
		index++;
	}
	return (0);
}

void new_lst_start(t_list **vols, t_list *new_start)
{
	t_list	*index;

	index = *vols;
	while (index && index->next != new_start)
		index = index->next;
	if (index)
	{
		index->next = NULL;
		index = new_start;
		while (index)
			index = index->next;
		index->next = *vols;
		*vols = new_start;
	}
}

int sort_vols(t_list **vols ,const t_box *box)
{
	t_list	*new_start;
	int		index;

	new_start = get_furthest_vol(&(box->center), vols);
	new_lst_start(vols, new_start);
	
	return (index);
}
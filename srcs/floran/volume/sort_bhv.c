/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bhv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:54:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/25 17:26:51 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"

static t_vol *get_furthest_vol(const t_pos *pos, t_vol **vols, int size)
{
	double			dst;
	double			tmp;
	t_vol			*ret;
	unsigned int	index;

	ret = NULL;
	index = 0;
	dst = dist_ab(pos, &(*vols)[index].box.center);
	ret = &(*vols)[index++];
	while (index < size)
	{
		tmp = dist_ab(pos, &(*vols)[index].box.center);
		if (tmp < dst)
		{
			dst = tmp;
			ret = &(*vols)[index];
		}
		index++;
	}
	return (ret);
}

static int tab_fill(t_vol **vols, int size, t_vol **tab, t_pos origin)
{
	unsigned int	index;
	unsigned int	j;
	unsigned int	i;
	double			dist;
	t_vol			*tmp;

	*tab = ft_calloc(sizeof(t_vol), size);
	if (!*tab)
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

int sort_vols(t_vol **vols, int size, const t_box *box)
{
	t_vol	*left_vol;
	t_vol	*tab_sorted;
	int		index;

	if (size < 2)
		return (0);
	else if (size == 2)
		return (1);
	left_vol = get_furthest_vol(&(box->center), vols, size);
	if (tab_fill(vols, size, &tab_sorted, left_vol->box.center))
		return (-1);
	index = 1;
	while (index < size - 1)
	{
		if (!(dist_ab(&tab_sorted[0].box.center, &tab_sorted[index].box.center)
			< dist_ab(&tab_sorted[size - 1].box.center, &tab_sorted[index].box.center)))
			break ;
		index++;
	}
	//need to returb the good sorted vols
	return (index);
}
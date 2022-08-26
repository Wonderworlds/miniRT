/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:54:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/26 13:54:44 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"

static t_list	*get_furthest_vol(const t_pos *pos, t_list *vols)
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

static void	new_lst_start(t_list **vols, t_list *new_start)
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

unsigned int	sort_vols(t_list **vols, const t_box *box)
{
	t_list			*new_start;
	t_list			*index;
	unsigned int	m;

	new_start = get_furthest_vol(&(box->center), *vols);
	new_lst_start(vols, new_start);
	sort_list_custom(&(*vols)->next,
		&((t_vol *)new_start->content)->box.center);
	m = 0;
	index = new_start;
	while (index)
	{
		if (cmp_nearest_vol((t_vol *)new_start->content,
				(t_vol *)ft_lstlast(new_start)->content,
				&((t_vol *)index->content)->box.center))
			m++;
		index = index->next;
	}
	return (m);
}

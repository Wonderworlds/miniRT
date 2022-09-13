/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bvh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:54:41 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/13 17:26:57 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"

static t_list	*get_furthest_vol(const t_pos *pos, t_list *vols,
					unsigned int begin, unsigned int end)
{
	double	dst;
	double	tmp;
	t_list	*ret;
	t_list	*index;

	index = ft_lst_at(vols, begin);
	dst = dist_ab(pos, &(((t_vol *)(index->content))->box.center));
	ret = index;
	index = index->next;
	while (end-- > begin)
	{
		tmp = dist_ab(pos, &(((t_vol *)(index->content))->box.center));
		if (tmp > dst)
		{
			dst = tmp;
			ret = index;
		}
		index = index->next;
	}
	return (ret);
}

static void	set_variable(t_list **vols, t_list **prev, t_list **index,
	unsigned int begin)
{
	*prev = *vols;
	*index = *vols;
	if (begin != 0)
	{
		*prev = ft_lst_at(*vols, begin - 1);
		*index = (*prev)->next;
	}
}

static void	new_lst_start(t_list **vols, t_list *new_start,
				unsigned int begin, unsigned int end)
{
	t_list	*index;
	t_list	*prev;
	t_list	*next;

	set_variable(vols, &prev, &index, begin);
	next = ft_lst_at(*vols, end)->next;
	while (index != next && index->next != new_start)
		index = index->next;
	if (index != next)
	{
		index->next = next;
		index = new_start;
		while (index->next != next)
			index = index->next;
		if (begin == 0)
		{
			index->next = *vols;
			*vols = new_start;
		}
		else
		{
			index->next = prev->next;
			prev->next = new_start;
		}
	}
}

unsigned int	sort_vols(t_list **vols, const t_box *box,
					unsigned int begin, unsigned int end)
{
	t_list			*new_start;
	t_list			*index;
	t_vol			*start_end[2];
	int				compare[3];

	new_start = get_furthest_vol(&(box->center), *vols, begin, end);
	new_lst_start(vols, new_start, begin, end);
	sort_list_custom(&(*vols)->next,
		&((t_vol *)new_start->content)->box.center, begin, end);
	compare[2] = 0;
	compare[1] = 0;
	index = new_start;
	start_end[0] = (t_vol *)(new_start->content);
	start_end[1] = (t_vol *)(ft_lst_at(*vols, end)->content);
	while (end-- > begin)
	{
		compare[0] = cmp_nearest_vol(start_end[0], start_end[1],
				&((t_vol *)index->content)->box.center);
		if (compare[0] >= 0)
			compare[2]++;
		if (compare[0] == 0)
			compare[1]++;
		index = index->next;
	}
	return (compare[2] + begin - (compare[1] / 2));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds_total.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:54:16 by amahla            #+#    #+#             */
/*   Updated: 2022/08/26 19:45:24 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>

void	init_pos_axe(t_vol *vol, t_box *box)
{
	box->min.x = vol->box.min.x;
	box->min.y = vol->box.min.y;
	box->min.z = vol->box.min.z;
	box->max.x = vol->box.max.x;
	box->max.y = vol->box.max.y;
	box->min.z = vol->box.max.z;
}

void	axe_value(t_vol *vol, t_box *box)
{
	if (vol->box.min.x < box->min.x)
		box->min.x = vol->box.min.x;
	if (vol->box.min.y < box->min.y)
		box->min.y = vol->box.min.y;
	if (vol->box.min.z < box->min.z)
		box->min.z = vol->box.min.z;
	if (vol->box.max.x > box->max.x)
		box->max.x = vol->box.max.x;
	if (vol->box.max.y > box->max.y)
		box->max.y = vol->box.max.y;
	if (vol->box.max.z > box->max.z)
		box->max.z = vol->box.max.z;
}

void	bounds_total(t_list *vols, t_box *box, unsigned int begin, unsigned int end)
{
	t_vol				*vol;

	vols = ft_lst_at(vols, begin);
	vol = (t_vol *)(vols->content);
	init_pos_axe(vol, box);
	if (end == begin)
	{
		vector_equal(vol->box.center, &box->center);
		box->expend = vol->box.expend;
		return ;
	}
	while (vols && begin <= end)
	{
		vol = (t_vol *)(vols->content);
		axe_value(vol, box);
		vols = vols->next;
		begin++;
	}
	bbox_center(box, &box->center);
	box->expend = bbox_expend(box);
}

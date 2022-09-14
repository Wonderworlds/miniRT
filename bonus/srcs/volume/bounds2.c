/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:28:59 by amahla            #+#    #+#             */
/*   Updated: 2022/09/14 23:02:07 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"

static void	init_pos_tr(t_vol *vol)
{
	vol->box.min.x = vol->tr[0].x;
	vol->box.min.y = vol->tr[0].y;
	vol->box.min.z = vol->tr[0].z;
	vol->box.max.x = vol->tr[0].x;
	vol->box.max.y = vol->tr[0].y;
	vol->box.max.z = vol->tr[0].z;
}

static void	set_value(t_vol *vol, size_t i)
{
	if (vol->box.min.x > vol->tr[i].x)
		vol->box.min.x = vol->tr[i].x;
	if (vol->box.min.y > vol->tr[i].y)
		vol->box.min.y = vol->tr[i].y;
	if (vol->box.min.z > vol->tr[i].z)
		vol->box.min.z = vol->tr[i].z;
	if (vol->box.max.x < vol->tr[i].x)
		vol->box.max.x = vol->tr[i].x;
	if (vol->box.max.y < vol->tr[i].y)
		vol->box.max.y = vol->tr[i].y;
	if (vol->box.max.z < vol->tr[i].z)
		vol->box.max.z = vol->tr[i].z;
}

void	triangle_bounds_and_set(t_vol *tr)
{
	size_t	i;

	i = 1;
	init_pos_tr(tr);
	while (i < 3)
		set_value(tr, i++);
	bbox_center(&tr->box, &tr->box.center);
	tr->box.expend = bbox_expend(&tr->box);
	tr->pos = tr->box.center;
}



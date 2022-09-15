/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 13:28:59 by amahla            #+#    #+#             */
/*   Updated: 2022/09/15 18:58:48 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <math.h>

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

static void	calcul_err_add(t_pos *tmp, t_pos vec_e, double r, t_pos co)
{
	vector_equal(vec_e, tmp);
	vector_scale(r, tmp);
	vector_add(co, *tmp, tmp);
}

static void	calcul_err_sub(t_pos *tmp, t_pos vec_e, double r, t_pos co)
{
	vector_equal(vec_e, tmp);
	vector_scale(r, tmp);
	vector_sub(co, *tmp, tmp);
}

void	cone_bounds(t_vol *co)
{
	t_pos	co_top;
	t_pos	vec_a;
	t_pos	vec_e;
	t_pos	tmp[2];

	co_top.x = co->pos.x + (co->h * co->vec3.x);
	co_top.y = co->pos.y + (co->h * co->vec3.y);
	co_top.z = co->pos.z + (co->h * co->vec3.z);
	vector_ab(co->pos, co_top, &vec_a);
	vector_multi(vec_a, vec_a, tmp);
	vec_e.x = sqrtf(1.f - tmp[0].x / dot_product(vec_a, vec_a));
	vec_e.y = sqrtf(1.f - tmp[0].y / dot_product(vec_a, vec_a));
	vec_e.z = sqrtf(1.f - tmp[0].z / dot_product(vec_a, vec_a));
	calcul_err_add(tmp, vec_e, co->d / 2, co->pos);
	calcul_err_add(tmp + 1, vec_e, 0.f, co_top);
	set_vector(fmaxf(tmp[0].x, tmp[1].x), fmaxf(tmp[0].y, tmp[1].y),
		fmaxf(tmp[0].z, tmp[1].z), &co->box.max);
	calcul_err_sub(tmp, vec_e, co->d / 2, co->pos);
	calcul_err_sub(tmp + 1, vec_e, 0.f, co_top);
	set_vector(fminf(tmp[0].x, tmp[1].x), fminf(tmp[0].y, tmp[1].y),
		fminf(tmp[0].z, tmp[1].z), &co->box.min);
	bbox_center(&co->box, &co->box.center);
	co->box.expend = bbox_expend(&co->box);
}

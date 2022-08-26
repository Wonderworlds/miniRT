/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds_volumes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:54:16 by amahla            #+#    #+#             */
/*   Updated: 2022/08/26 21:18:54 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>


void    sphere_bounds(t_vol *sp)
{
    float    r = sp->d / 2;

    set_vector(-r, -r, -r, &sp->box.min);
    set_vector(r, r, r, &sp->box.max);
    vector_add(sp->pos, sp->box.min, &sp->box.min);
    vector_add(sp->pos, sp->box.max, &sp->box.max);
    sp->box.expend = bbox_expend(&sp->box);
    vector_equal(sp->pos, &sp->box.center);
}

/*void	cylinder_bounds(t_vol *cy)
{
	float	r;

	r = sqrtf(powf(cy->h / 2, 2) + powf(cy->d / 2, 2));
	set_vector(-r, -r, -r, &cy->box.min);
	set_vector(r, r, r, &cy->box.max);
	cy->box.center.x = cy->pos.x + (cy->h / 2 * cy->vec3.x);
	cy->box.center.y = cy->pos.y + (cy->h / 2 * cy->vec3.y);
	cy->box.center.z = cy->pos.z + (cy->h / 2 * cy->vec3.z);
	vector_add(cy->box.center, cy->box.min, &cy->box.min);
	vector_add(cy->box.center, cy->box.max, &cy->box.max);
	cy->box.expend = bbox_expend(&cy->box);
}*/

void	cylinder_bounds(t_vol *cy)
{
	t_pos	cy_top;
	t_pos	vec_a;
	t_pos	vec_e;
	t_pos	tmp[2];
	
	cy_top.x = cy->pos.x + (cy->h * cy->vec3.x);
	cy_top.y = cy->pos.y + (cy->h * cy->vec3.y);
	cy_top.z = cy->pos.z + (cy->h * cy->vec3.z);
	vector_ab(cy->pos, cy_top, &vec_a);
	vector_multi(vec_a, vec_a, tmp);
	vec_e.x = (cy->d / 2) * sqrtf(1.f - tmp[0].x / dot_product(vec_a, vec_a));
	vec_e.y = (cy->d / 2) * sqrtf(1.f - tmp[0].y / dot_product(vec_a, vec_a));
	vec_e.z = (cy->d / 2) * sqrtf(1.f - tmp[0].z / dot_product(vec_a, vec_a));
	vector_add(cy->pos, vec_e, tmp);
	vector_add(cy_top, vec_e, tmp + 1);
	set_vector(fmaxf(tmp[0].x, tmp[1].x), fmaxf(tmp[0].x, tmp[1].x),
		fmaxf(tmp[0].x, tmp[1].x), &cy->box.max);
	vector_sub(cy->pos, vec_e, tmp);
	vector_sub(cy_top, vec_e, tmp + 1);
	set_vector(fminf(tmp[0].x, tmp[1].x), fminf(tmp[0].x, tmp[1].x),
		fminf(tmp[0].x, tmp[1].x), &cy->box.min);
	bbox_center(&cy->box, &cy->box.center);
	cy->box.expend = bbox_expend(&cy->box);
}

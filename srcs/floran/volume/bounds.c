/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:54:16 by amahla            #+#    #+#             */
/*   Updated: 2022/08/26 17:59:53 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>

void	sphere_bounds(t_vol *sp)
{
	float	r = sp->d / 2;

	set_vector(-r, -r, -r, &sp->box.min);
	set_vector(r, r, r, &sp->box.max);
	vector_add(sp->pos, sp->box.min, &sp->box.min);
	vector_add(sp->pos, sp->box.max, &sp->box.max);
	sp->box.expend = bbox_expend(&sp->box);
	vector_equal(sp->pos, &sp->box.center);
}

// void	cylinder_bounds(t_vol *cy)
// {
// 	float	rayon;

// 	rayon = sqrtf(powf(cy->h / 2, 2) + powf(cy->d / 2, 2));
// 	cy->box.center.x = cy->pos.x + (cy->h / 2 * cy->vec3.x);
// 	cy->box.center.y = cy->pos.y + (cy->h / 2 * cy->vec3.y);
// 	cy->box.center.z = cy->pos.z + (cy->h / 2 * cy->vec3.z);
// 	cy->box.rayon = rayon;
// }

// t_bool	plane_intersect(t_vol pl, t_vol vol)
// {
// 	float	d;
// 	float	distance;

// 	d = -1 * (pl.vec3.x * pl.pos.x + pl.vec3.y * pl.pos.y
// 		+ pl.vec3.z * pl.pos.z);
// 	distance = (pl.vec3.x * vol.box.center.x + pl.vec3.y * vol.box.center.y
// 			+ pl.vec3.z * vol.box.center.z + d) / sqrtf(powf(pl.vec3.x, 2)
// 			+ powf(pl.vec3.y, 2) + powf(pl.vec3.z, 2));
// 	if (distance < 0)
// 		distance *= -1;
// 	if (vol.box.rayon > distance)
// 		return (true);
// 	return (false);
// }

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:54:16 by amahla            #+#    #+#             */
/*   Updated: 2022/08/25 14:16:58 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>

void	sphere_bounds(t_vol *sp)
{
	float	rayon;

	rayon = sp->d / 2;
	sp->box.center.x = sp->pos.x;
	sp->box.center.y = sp->pos.y;
	sp->box.center.z = sp->pos.z;
	sp->box.rayon = rayon;
}

void	cylinder_bounds(t_vol *cy)
{
	float	rayon;

	rayon = sqrtf(powf(cy->h / 2, 2) + powf(cy->d / 2, 2));
	cy->box.center.x = cy->pos.x + (cy->h / 2 * cy->vec3.x);
	cy->box.center.y = cy->pos.y + (cy->h / 2 * cy->vec3.y);
	cy->box.center.z = cy->pos.z + (cy->h / 2 * cy->vec3.z);
	cy->box.rayon = rayon;
}

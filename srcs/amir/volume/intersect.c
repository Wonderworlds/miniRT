/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:54:16 by amahla            #+#    #+#             */
/*   Updated: 2022/08/26 15:37:47 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>

t_bool	plane_and_sphere_intersect(t_vol pl, t_vol vol)
{
	float	d;
	float	distance;

	d = -1 * (pl.vec3.x * pl.pos.x + pl.vec3.y * pl.pos.y
		+ pl.vec3.z * pl.pos.z);
	distance = (pl.vec3.x * vol.box.center.x + pl.vec3.y * vol.box.center.y
			+ pl.vec3.z * vol.box.center.z + d) / sqrtf(powf(pl.vec3.x, 2)
			+ powf(pl.vec3.y, 2) + powf(pl.vec3.z, 2));
	if (distance < 0)
		distance *= -1;
	if (vol.box.rayon > distance)
		return (true);
	return (false);
}

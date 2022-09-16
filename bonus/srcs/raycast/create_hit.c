/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:39:27 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/16 01:37:50 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"
#include "libft.h"
#include <math.h>

static void	create_hit2(t_hit *hit, t_vol *vol, t_plane *pl)
{
	if (vol)
	{
		col_cpy(&vol->col, &hit->col);
		if (vol->type == SPHERE)
			hit_sphere(vol, hit);
		else if (vol->type == CYLINDER)
			hit_cylinder(vol, hit);
		else if (vol->type == TRIANGLE)
			hit_triangle(vol, hit);
		else if (vol->type == CONE)
			hit_cone(vol, hit);
		hit->vol = vol;
	}
	else if (pl)
		hit_plane(pl, hit);
}

void	create_hit(float t, t_vol *vol, t_plane *pl, t_ray *ray)
{
	t_hit	hit;
	t_pos	offset;

	hit.dst_origin = t;
	vector_equal(ray->dir, &hit.pos);
	vector_scale(t, &hit.pos);
	vector_add(hit.pos, ray->origin, &hit.pos);
	create_hit2(&hit, vol, pl);
	if (dot_product(hit.normal, ray->dir) > 0)
		vector_scale(-1, &hit.normal);
	vector_equal(hit.normal, &offset);
	vector_scale(0.02f, &offset);
	vector_add(hit.pos, offset, &hit.pos);
	update_hit(&hit);
}

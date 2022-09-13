/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:39:27 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/13 21:47:38 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"
#include "libft.h"
#include <math.h>

static void	hit_triangle(t_vol *vol, t_hit *hit)
{
	col_cpy(&vol->col, &hit->col);
	pos_cpy(&vol->vec3, &hit->normal);
	hit->spec.size = vol->spec.size;
	hit->spec.intensity = vol->spec.intensity;
	hit->vol_type = TRIANGLE;
}

static void	hit_sphere(t_vol *vol, t_hit *hit)
{
	vector_ab(vol->pos, hit->pos, &hit->normal);
	unit_vector(&hit->normal);
	hit->spec.size = vol->spec.size;
	hit->spec.intensity = vol->spec.intensity;
	hit->vol_type = SPHERE;
}

static void	hit_cylinder(t_vol *vol, t_hit *hit)
{
	double	d;
	t_pos	vec3;

	d = sqrt(powf(dist_ab(&vol->pos, &hit->pos), 2) - vol->d / 2 * vol->d / 2);
	set_vector(vol->h * vol->vec3.x, vol->h * vol->vec3.y,
		vol->h * vol->vec3.z, &vec3);
	unit_vector(&vec3);
	vector_scale(d, &vec3);
	vector_add(vol->pos, vec3, &hit->normal);
	vector_ab(hit->normal, hit->pos, &hit->normal);
	unit_vector(&hit->normal);
	hit->spec.size = vol->spec.size;
	hit->spec.intensity = vol->spec.intensity;
	hit->vol_type = CYLINDER;
}

static void	hit_plane(t_plane *pl, t_hit *hit)
{
	col_cpy(&pl->col, &hit->col);
	pos_cpy(&pl->vec3, &hit->normal);
	hit->spec.size = pl->spec.size;
	hit->spec.intensity = pl->spec.intensity;
	hit->vol_type = PLANE;
	hit->vol = pl;
}

void	create_hit(float t, t_vol *vol, t_plane *pl, t_ray *ray)
{
	t_hit	hit;
	t_pos	offset;

	hit.dst_origin = t;
	vector_equal(ray->dir, &hit.pos);
	vector_scale(t, &hit.pos);
	vector_add(hit.pos, ray->origin, &hit.pos);
	if (vol)
	{
		col_cpy(&vol->col, &hit.col);
		if (vol->type == SPHERE)
			hit_sphere(vol, &hit);
		else if (vol->type == CYLINDER)
			hit_cylinder(vol, &hit);
		else if (vol->type == TRIANGLE)
			hit_triangle(vol, &hit);
		hit.vol = vol;
	}
	else if (pl)
		hit_plane(pl, &hit);
	if (dot_product(hit.normal, ray->dir) > 0)
		vector_scale(-1, &hit.normal);
	vector_equal(hit.normal, &offset);
	vector_scale(0.02f, &offset);
	vector_add(hit.pos, offset, &hit.pos);
	update_hit(&hit);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_hit2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:39:27 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/16 01:37:30 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"
#include "libft.h"
#include <math.h>

void	hit_triangle(t_vol *vol, t_hit *hit)
{
	col_cpy(&vol->col, &hit->col);
	pos_cpy(&vol->vec3, &hit->normal);
	hit->spec.size = vol->spec.size;
	hit->spec.intensity = vol->spec.intensity;
	hit->vol_type = TRIANGLE;
}

void	hit_cone(t_vol *vol, t_hit *hit)
{
	t_pos	vec3;
	t_pos	co_top;

	set_vector(vol->pos.x + vol->h * vol->vec3.x, vol->pos.y
		+ vol->h * vol->vec3.y, vol->pos.z + vol->h * vol->vec3.z, &co_top);
	vector_ab(co_top, hit->pos, &vec3);
	vector_equal(vec3, &hit->normal);
	vector_scale(dot_product(vol->vec3, vec3), &hit->normal);
	vector_div(hit->normal, dot_product(vec3, vec3), &hit->normal);
	vector_sub(hit->normal, vol->vec3, &hit->normal);
	unit_vector(&hit->normal);
	hit->spec.size = vol->spec.size;
	hit->spec.intensity = vol->spec.intensity;
	hit->vol_type = CONE;
}

void	hit_sphere(t_vol *vol, t_hit *hit)
{
	vector_ab(vol->pos, hit->pos, &hit->normal);
	unit_vector(&hit->normal);
	hit->spec.size = vol->spec.size;
	hit->spec.intensity = vol->spec.intensity;
	hit->vol_type = SPHERE;
}

void	hit_cylinder(t_vol *vol, t_hit *hit)
{
	float	d;
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

void	hit_plane(t_plane *pl, t_hit *hit)
{
	col_cpy(&pl->col, &hit->col);
	pos_cpy(&pl->vec3, &hit->normal);
	hit->spec.size = pl->spec.size;
	hit->spec.intensity = pl->spec.intensity;
	hit->vol_type = PLANE;
	hit->vol = pl;
}

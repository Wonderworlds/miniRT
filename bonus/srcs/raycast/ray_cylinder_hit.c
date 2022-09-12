/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:39:27 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/12 23:48:27 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"
#include "libft.h"
#include <math.h>

static float	set_t(t_pos *e, t_pos cy, t_ray *ray, t_pos cy_vec3)
{
	vector_ab(ray->origin, cy, e);
	vector_equal(cy, e + 1);
	return (dot_product(e[0], cy_vec3));
}

static float	set_t2(float dot, float denom, t_bool *dir, t_bool sign)
{
	*dir = sign;
	return (dot / denom);
}

static void	set_extremity_hitpos(t_ray *ray, t_hit *hit, float t)
{
	vector_equal(ray->dir, &hit->pos);
	vector_scale(t, &hit->pos);
	vector_add(hit->pos, ray->origin, &hit->pos);
}

static void	set_extremity_hit(t_vol *cy, t_hit *hit, t_bool dir, t_ray *ray)
{
	t_pos	offset;

	col_cpy(&cy->col, &hit->col);
	vector_equal(cy->vec3, &hit->normal);
	if (dir == true)
		vector_scale(-1, &hit->normal);
	if (dot_product(hit->normal, ray->dir) > 0)
		vector_scale(-1, &hit->normal);
	vector_equal(hit->normal, &offset);
	vector_scale(0.02f, &offset);
	vector_add(hit->pos, offset, &hit->pos);
	hit->spec.size = cy->spec.size;
	hit->spec.intensity = cy->spec.intensity;
	update_hit(hit);
}

void	check_cylinder_extremity(t_vol *cy, t_pos cy_top, t_ray *ray)
{
	float	denom;
	t_bool	dir;
	float	t;
	t_pos	e[2];
	t_hit	hit;

	denom = dot_product(cy->vec3, ray->dir);
	if (fabsf(denom) > 0.0001f)
	{
		t = set_t2(set_t(e, cy->pos, ray, cy->vec3), denom, &dir, true);
		if (t < 0.00001f || (t >= 0.00001f
				&& dist_ab(&cy->pos, &ray->origin)
				> dist_ab(&cy_top, &ray->origin)))
			t = set_t2(set_t(e, cy_top, ray, cy->vec3), denom, &dir, false);
		if (t >= 0.00001f)
		{
			set_extremity_hitpos(ray, &hit, t);
			if (dist_ab(&hit.pos, e + 1) <= cy->d / 2)
			{
				hit.dst_origin = t;
				set_extremity_hit(cy, &hit, dir, ray);
			}
		}
	}
}

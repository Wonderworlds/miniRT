/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cone_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:42:24 by amahla            #+#    #+#             */
/*   Updated: 2022/09/17 15:43:53 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"
#include "libft.h"
#include <math.h>

static void	set_extremity_hit(t_vol *co, t_hit *hit, t_bool dir, t_ray *ray)
{
	t_pos	offset;

	(void)dir;
	col_cpy(&co->col, &hit->col);
	vector_equal(co->vec3, &hit->normal);
	if (dir == true)
		vector_scale(-1, &hit->normal);
	if (dot_product(hit->normal, ray->dir) > 0)
		vector_scale(-1, &hit->normal);
	vector_equal(hit->normal, &offset);
	vector_scale(0.02f, &offset);
	vector_add(hit->pos, offset, &hit->pos);
	hit->spec.size = co->spec.size;
	hit->spec.intensity = co->spec.intensity;
	hit->vol_type = CONE;
	hit->vol = co;
	update_hit(hit);
}

void	check_cone_extremity(t_vol *co, t_ray *ray)
{
	float	denom;
	float	t;
	t_bool	dir;
	t_pos	e[2];
	t_hit	hit;

	denom = dot_product(co->vec3, ray->dir);
	if (fabsf(denom) > 0.0001f)
	{
		t = set_t2(set_t(e, co->pos, ray, co->vec3), denom, &dir, true);
		if (t >= 0.00001f)
		{
			vector_equal(ray->dir, &hit.pos);
			vector_scale(t, &hit.pos);
			vector_add(hit.pos, ray->origin, &hit.pos);
			if (dist_ab(&hit.pos, e + 1) <= co->d / 2)
			{
				hit.dst_origin = t;
				set_extremity_hit(co, &hit, dir, ray);
			}
		}
	}
}

static void	create_cone_hit(t_ray *ray, t_vol *co, t_pos co_top, float t)
{
	t_pos	h;
	t_pos	temp[2];

	vector_equal(ray->dir, &h);
	vector_scale(t, &h);
	vector_add(ray->origin, h, &h);
	vector_ab(co->pos, h, &temp[0]);
	vector_ab(co_top, h, &temp[1]);
	if (dot_product(temp[0], co->vec3) > 0
		&& dot_product(temp[1], co->vec3) < 0)
		create_hit(t, co, NULL, ray);
}

static t_bool	set_cone_hit(float *abc, t_ray *ray, t_vol *co, t_pos co_top)
{
	t_hit	hit;
	float	d;
	float	t;

	d = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (d < 0.f)
		return (false);
	d = sqrtf(d);
	t = (-1 * abc[1] - d) / (2 * abc[0]);
	create_cone_hit(ray, co, co_top, t);
	t = (-1 * abc[1] + d) / (2 * abc[0]);
	create_cone_hit(ray, co, co_top, t);
	check_cone_extremity(co, ray);
	if (get_hit(&hit) != -1)
		return (true);
	return (false);
}

t_bool	is_cone_hit(t_ray *ray, t_vol *co)
{
	float	abc[3];
	float	mvw[3];
	t_pos	va_rao[2];
	t_pos	temp[2];
	t_pos	co_top;

	set_vector(co->pos.x + co->h * co->vec3.x, co->pos.y
		+ co->h * co->vec3.y, co->pos.z + co->h * co->vec3.z, &co_top);
	cross_product(co->vec3, ray->dir, &temp[0]);
	cross_product(temp[0], co->vec3, &va_rao[0]);
	mvw[0] = powf((co->d / 2), 2) / powf(dist_ab(&co->pos, &co_top), 2);
	mvw[1] = dot_product(ray->dir, co->vec3);
	abc[0] = dot_product(va_rao[0], va_rao[0]) - powf(mvw[1], 2) * mvw[0];
	mvw[2] = dist_ab(&co->pos, &co_top);
	vector_ab(co->pos, ray->origin, &temp[1]);
	mvw[2] -= dot_product(temp[1], co->vec3);
	cross_product(co->vec3, temp[1], &temp[0]);
	cross_product(temp[0], co->vec3, &va_rao[1]);
	abc[1] = 2 * dot_product(va_rao[1], va_rao[0])
		+ 2 * mvw[2] * mvw[1] * mvw[0];
	abc[2] = dot_product(va_rao[1], va_rao[1]) - powf(mvw[2], 2) * mvw[0];
	if (set_cone_hit(abc, ray, co, co_top) == false)
		return (false);
	return (true);
}

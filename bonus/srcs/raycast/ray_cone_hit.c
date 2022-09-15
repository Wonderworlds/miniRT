/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cone_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:42:24 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 00:53:12 by fmauguin         ###   ########.fr       */
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

float	solve_quadratic_cone(float a, float b, float c)
{
	float	discriminant;
	float	t0;
	float	t1;

	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1);
	t0 = (-b - sqrtf(discriminant)) / (2 * a);
	t1 = (-b + sqrtf(discriminant)) / (2 * a);
	if (t0 > t1 || (t0 < 0 && t1 >= 0))
		return (t1);
	return (t0);
}

t_bool	check_extremity_cone(float t, t_pos h_norm, t_ray *ray, t_pos h,
	t_pos co_top)
{
	t_pos	hit;
	float	dot;

	vector_equal(ray->dir, &hit);
	vector_scale(t, &hit);
	vector_add(hit, ray->origin, &hit);
	vector_sub(hit, co_top, &hit);
	dot = dot_product(hit, h_norm);
	if (dot < 0 || dot > vector_norm(h))
		return (false);
	return (true);
}

t_bool	is_cone_hit(t_ray *ray, t_vol *co)
{
	t_pos	h;
	t_pos	w;
	t_pos	h_norm;
	float	m;
	t_pos	co_top;
	float	abc[3];
	float	t;
	float	d;

	set_vector(co->pos.x + co->h * co->vec3.x, co->pos.y
		+ co->h * co->vec3.y, co->pos.z + co->h * co->vec3.z, &co_top);
	vector_sub(co->pos, co_top, &h);
	vector_sub(co->pos, co_top, &h_norm);
	unit_vector(&h_norm);
	m = powf((co->d / 2), 2) / dot_product(h, h);
	vector_sub(ray->origin, co_top, &w);
	abc[0] = dot_product(ray->dir, ray->dir)
		- m * powf(dot_product(ray->dir, h_norm), 2)
		- powf(dot_product(ray->dir, h_norm), 2);
	abc[1] = 2 * (dot_product(ray->dir, w)
		- m * dot_product(ray->dir, h_norm) * dot_product(w, h_norm)
		- dot_product(ray->dir, h_norm) * dot_product(w, h_norm));
	abc[2] = dot_product(w, w) - m * powf(dot_product(w, h_norm), 2)
		- powf(dot_product(w, h_norm), 2);
	

	d = (abc[1] * abc[1]) - (4 * abc[0] * abc[2]);
	if (d < 0)
		return (false);
	t = (-1 * abc[1] - sqrtf(d)) / (2 * abc[0]);
	if (check_extremity_cone(t, h_norm, ray, h, co_top))
		create_hit(t, co, NULL, ray);
	t = (-1 * abc[1] + sqrtf(d)) / (2 * abc[0]);
	if (check_extremity_cone(t, h_norm, ray, h, co_top))
		create_hit(t, co, NULL, ray);
	check_cone_extremity(co, ray);

	return (true);
}



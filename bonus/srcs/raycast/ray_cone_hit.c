/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cone_hit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:42:24 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 01:52:06 by fmauguin         ###   ########.fr       */
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

// float	solve_quadratic_cone(float a, float b, float c)
// {
// 	float	discriminant;
// 	float	t0;
// 	float	t1;

// 	discriminant = (b * b) - (4 * a * c);
// 	if (discriminant < 0)
// 		return (-1);
// 	t0 = (-b - sqrtf(discriminant)) / (2 * a);
// 	t1 = (-b + sqrtf(discriminant)) / (2 * a);
// 	if (t0 > t1 || (t0 < 0 && t1 >= 0))
// 		return (t1);
// 	return (t0);
// }

t_bool	check_extremity_cone(t_h_conehit *h_cohit, t_ray *ray)
{
	t_pos	hit;
	float	dot;

	vector_equal(ray->dir, &hit);
	vector_scale(h_cohit->t, &hit);
	vector_add(hit, ray->origin, &hit);
	vector_sub(hit, h_cohit->co_top, &hit);
	dot = dot_product(hit, h_cohit->h_norm);
	if (dot < 0 || dot > vector_norm(h_cohit->h))
		return (false);
	return (true);
}

void	is_cone_hit2(t_ray *ray, t_vol *co, t_h_conehit *h_cohit)
{
	set_vector(co->pos.x + co->h * co->vec3.x, co->pos.y
		+ co->h * co->vec3.y, co->pos.z + co->h * co->vec3.z, &h_cohit->co_top);
	vector_sub(co->pos, h_cohit->co_top, &h_cohit->h);
	vector_sub(co->pos, h_cohit->co_top, &h_cohit->h_norm);
	unit_vector(&h_cohit->h_norm);
	h_cohit->m = powf((co->d / 2), 2) / dot_product(h_cohit->h, h_cohit->h);
	vector_sub(ray->origin, h_cohit->co_top, &h_cohit->w);
	h_cohit->abc[0] = dot_product(ray->dir, ray->dir)
		- h_cohit->m * powf(dot_product(ray->dir, h_cohit->h_norm), 2)
		- powf(dot_product(ray->dir, h_cohit->h_norm), 2);
	h_cohit->abc[1] = 2 * (dot_product(ray->dir, h_cohit->w)
			- h_cohit->m * dot_product(ray->dir, h_cohit->h_norm)
			* dot_product(h_cohit->w, h_cohit->h_norm)
			- dot_product(ray->dir, h_cohit->h_norm)
			* dot_product(h_cohit->w, h_cohit->h_norm));
	h_cohit->abc[2] = dot_product(h_cohit->w, h_cohit->w)
		- h_cohit->m * powf(dot_product(h_cohit->w, h_cohit->h_norm), 2)
		- powf(dot_product(h_cohit->w, h_cohit->h_norm), 2);
	h_cohit->d = (h_cohit->abc[1] * h_cohit->abc[1])
		- (4 * h_cohit->abc[0] * h_cohit->abc[2]);
}

t_bool	is_cone_hit(t_ray *ray, t_vol *co)
{
	t_h_conehit	h_cohit;

	is_cone_hit2(ray, co, &h_cohit);
	if (h_cohit.d < 0)
		return (false);
	h_cohit.t = (-1 * h_cohit.abc[1] - sqrtf(h_cohit.d)) / (2 * h_cohit.abc[0]);
	if (check_extremity_cone(&h_cohit, ray))
		create_hit(h_cohit.t, co, NULL, ray);
	h_cohit.t = (-1 * h_cohit.abc[1] + sqrtf(h_cohit.d)) / (2 * h_cohit.abc[0]);
	if (check_extremity_cone(&h_cohit, ray))
		create_hit(h_cohit.t, co, NULL, ray);
	check_cone_extremity(co, ray);
	return (true);
}

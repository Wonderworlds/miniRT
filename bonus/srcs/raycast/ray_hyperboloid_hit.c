/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hyperboloid_hit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:42:24 by amahla            #+#    #+#             */
/*   Updated: 2022/09/14 21:54:11 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"
#include "libft.h"
#include <math.h>

/*static t_bool	set_cone_hit(double *abcdef, double *hty,
	t_ray *ray, t_vol *co)
{
	hty[0] = abcdef[9] * abcdef[9] - abcdef[8] * abcdef[10];
	if (hty[0] < 0.0f)
		return (false);
	hty[0] = sqrtf(hty[0]);
	hty[1] = (-1 * abcdef[9] - hty[0]) / abcdef[8];
	hty[2] = abcdef[1] + hty[1] * abcdef[3];
	if (hty[2] > 0.0 && hty[2] < abcdef[0])
		create_hit(hty[1], co, NULL, ray);
	hty[1] = (-1 * abcdef[9] + hty[0]) / abcdef[8];
	hty[3] = abcdef[1] + hty[1] * abcdef[3];
	if (hty[3] > 0.f && hty[3] < abcdef[0])
		create_hit(hty[1], co, NULL, ray);
	return (true);
}

t_bool	is_cone_hit(t_ray *ray, t_vol *co)
{
	t_pos	vec3_co;
	t_pos	vec3[3];
	double	abcdef[11];
	double	hty[4];
	t_hit	hit;

	set_vector(co->pos.x + co->h * co->vec3.x, co->pos.y
		+ co->h * co->vec3.y, co->pos.z + co->h * co->vec3.z, &vec3_co);
	vector_ab(co->pos, vec3_co, &vec3[0]);
	vector_ab(co->pos, ray->origin, &vec3[1]);
	vector_ab(vec3_co, ray->origin, &vec3[2]);
	abcdef[0] = dot_product(vec3[0], vec3[0]);
	abcdef[1] = dot_product(vec3[0], vec3[1]);
	abcdef[2] = dot_product(vec3[0], vec3[2]);
	abcdef[3] = dot_product(vec3[0], ray->dir);

	abcdef[4] = dot_product(ray->dir, vec3[1]);
	abcdef[5] = dot_product(vec3[1], vec3[1]);
	abcdef[6] = co->d / 2 - co->d_co / 2;
	abcdef[7] = abcdef[0] - abcdef[6] * abcdef[6];

	abcdef[8] = abcdef[0] * abcdef[0] - abcdef[3] * abcdef[3] * abcdef[7];

	abcdef[9] = abcdef[0] * abcdef[0] * abcdef[4]
		- abcdef[1] * abcdef[3] * abcdef[7]
		+ abcdef[0] * (co->d / 2) * abcdef[6] * abcdef[3];

	abcdef[10] = abcdef[0] * abcdef[0] * abcdef[5]
		- abcdef[1] * abcdef[1] * abcdef[7]
		+ abcdef[0] * (co->d / 2) * (abcdef[6] * abcdef[1] * 2
			- abcdef[0] * co->d / 2);
	if (set_cone_hit(abcdef, hty, ray, co) == false)
		return (false);
	check_cylinder_extremity(co, vec3_co, ray);
	if (get_hit(&hit) != -1)
		return (true);
	return (false);
}*/

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
	if (dot <= 0 || dot > vector_norm(h))
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
//	t_pos	vec3[3];
	float	abc[3];
	float	t;
//	float	d;
//	t_hit	hit;

	set_vector(co->pos.x + co->h * co->vec3.x, co->pos.y
		+ co->h * co->vec3.y, co->pos.z + co->h * co->vec3.z, &co_top);
	vector_sub(co->pos, co_top, &h);
	vector_sub(co->pos, co_top, &h_norm);
	unit_vector(&h_norm);
	m = (co->d / 2) / dot_product(h, h);
	vector_sub(ray->origin, co_top, &w);
	abc[0] = dot_product(ray->dir, ray->dir)
		- m * powf(dot_product(ray->dir, h_norm), 2)
		- powf(dot_product(ray->dir, h_norm), 2);
	abc[1] = 2 * (dot_product(ray->dir, w)
		- m * dot_product(ray->dir, h_norm) * dot_product(w, h_norm)
		- dot_product(ray->dir, h_norm) * dot_product(w, h_norm));
	abc[2] = dot_product(w, w) - m * powf(dot_product(w, h_norm), 2)
		- powf(dot_product(w, h_norm), 2);
	
	t = solve_quadratic(abc[0], abc[1], abc[2]);
	if (t < 0)
		return (false);
	if (check_extremity_cone(t, h_norm, ray, h, co_top))
		create_hit(t, co, NULL, ray);
	

/*	d = (abc[1] * abc[1]) - (4 * abc[0] * abc[2]);
	if (d < 0)
		return (false);
	t = (-1 * abc[1] - sqrtf(d)) / (2 * abc[0]);
	if (check_extremity_cone(t, h_norm, ray, h, co_top))
		create_hit(t, co, NULL, ray);
	t = (-1 * abc[1] + sqrtf(d)) / (2 * abc[0]);
	if (check_extremity_cone(t, h_norm, ray, h, co_top))
		create_hit(t, co, NULL, ray);*/
	return (true);
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_volume_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:39:27 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/05 20:31:51 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"
#include "libft.h"
#include <math.h>

t_bool	is_aabb_hit(t_ray ray, t_box aabb)
{
	float	t[6];
	float	tmin;
	float	tmax;

	t[0] = (aabb.min.x - ray.origin.x) / ray.dir.x;
	t[1] = (aabb.max.x - ray.origin.x) / ray.dir.x;
	t[2] = (aabb.min.y - ray.origin.y) / ray.dir.y;
	t[3] = (aabb.max.y - ray.origin.y) / ray.dir.y;
	t[4] = (aabb.min.z - ray.origin.z) / ray.dir.z;
	t[5] = (aabb.max.z - ray.origin.z) / ray.dir.z;
	tmin =  fmaxf(fmaxf(fminf(t[0], t[1]), fminf(t[2], t[3])),
			fminf(t[4], t[5]));
	tmax = fminf(fminf(fmaxf(t[0], t[1]), fmaxf(t[2], t[3])),
			fmaxf(t[4], t[5]));
	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0 && tmin > tmax)
		return (true);
	if (tmin > 0 && tmin > tmax)
		return (true);
	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
		return (false);
	return (true);
}

float	solve_quadratic(float a, float b, float c)
{
	float	discriminant;
	float	t0;
	float	t1;

	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1);
	t0 = (-b - sqrtf(discriminant)) / (2 * a);
	t1 = (-b + sqrtf(discriminant)) / (2 * a);
	if (t0 > t1)
		return (t1);
	return (t0);
}

void	create_hit(float t, t_vol *vol, t_plane *pl, t_ray *ray)
{
	t_hit	hit;
	t_pos	vec3;
	double	d;

	hit.dst_origin = t;
	vector_equal(ray->dir, &hit.pos);
	vector_scale(t, &hit.pos);
	vector_add(hit.pos, ray->origin, &hit.pos);
	if (vol)
	{
		col_cpy(&vol->col, &hit.col);
		if (vol->type == SPHERE)
		{
			vector_ab(vol->pos, hit.pos, &hit.normal);
			// vector_add(hit.normal, hit.pos, &hit.normal);
			unit_vector(&hit.normal);
		}
		if (vol->type == CYLINDER)
		{
			d = sqrt(powf(dist_ab(&vol->pos, &hit.pos), 2) - vol->d / 2 * vol->d / 2);
			set_vector(vol->h * vol->vec3.x, vol->h * vol->vec3.y,
					vol->h * vol->vec3.z, &vec3);
			unit_vector(&vec3);
			vector_scale(d, &vec3);
			vector_add(vol->pos, vec3, &hit.normal);
			vector_ab(hit.normal, hit.pos, &hit.normal);
			unit_vector(&hit.normal);
		}
	}
	else if (pl)
	{
		col_cpy(&pl->col, &hit.col);
		pos_cpy(&pl->vec3, &hit.normal);
	}
	update_hit(&hit);
}

t_bool	is_sphere_hit(t_ray *ray, t_vol *sp)
{
	t_pos	e;
	float	abc[3];
	float	t;

	vector_ab(sp->pos, ray->origin, &e);
	abc[0] = dot_product(ray->dir, ray->dir);
	abc[1] = 2.0 * dot_product(e, ray->dir);
	abc[2] = dot_product(e, e) - powf(sp->d / 2, 2);
	t = solve_quadratic(abc[0], abc[1], abc[2]);
	if (t == -1)
		return (false);
	create_hit(t, sp, NULL, ray);
	return (true);
}

t_bool is_plane_hit(t_ray *ray, t_plane *pl)
{
	float	denom;
	float	t;
	t_pos	e;

	denom = dot_product(pl->vec3, ray->dir);
	if (fabsf(denom) > 0.0001f) // your favorite epsilon
	{
		vector_ab(ray->origin, pl->pos, &e);
		t = dot_product(e, pl->vec3) / denom;
		if (t >= 0.0001f)
		{
			create_hit(t, NULL, pl, ray);
			return (true); // you might want to allow an epsilon here too
		}
	}
	return (false);
}

void	check_cylinder_extremity(t_vol *cy, t_pos cy_top, t_ray *ray)
{
	float	denom;
	t_pos	hit;	
	t_pos	cy_pl;
	t_bool	normal_minus;
	float	t;
	t_pos	e;
	t_hit	h;

	denom = dot_product(cy->vec3, ray->dir);
	normal_minus = false;
	if (fabsf(denom) > 0.0001f)
	{
		if (dist_ab(&cy->pos, &ray->origin) < dist_ab(&cy_top, &ray->origin))
		{
			vector_ab(ray->origin, cy->pos, &e);
			vector_equal(cy->pos, &cy_pl);
			normal_minus = true;
		}
		else
		{
			vector_ab(ray->origin, cy_top, &e);
			vector_equal(cy_top, &cy_pl);
		}
		t = dot_product(e, cy->vec3) / denom;
		if (t >= 0.00001f)
		{
			vector_equal(ray->dir, &hit);
			vector_scale(t, &hit);
			vector_add(hit, ray->origin, &hit);
			if (dist_ab(&hit, &cy_pl) <= cy->d / 2)
			{
				h.dst_origin = t;
				vector_equal(ray->dir, &h.pos);
				vector_scale(t, &h.pos);
				vector_add(h.pos, ray->origin, &h.pos);
				col_cpy(&cy->col, &h.col);
				vector_equal(cy->vec3, &h.normal); 
				if (normal_minus == true)
					vector_scale(-1, &h.normal);
				update_hit(&h);
			}
		}
	}
}


t_bool	is_cylinder_hit(t_ray *ray, t_vol *cy)
{
	t_pos	vec3_cy;
	t_pos	vec3[2];
	float	abcdef[6];
	float	hty[4];
	t_hit	hit;

	set_vector(cy->pos.x + cy->h * cy->vec3.x, cy->pos.y + cy->h * cy->vec3.y,
			cy->pos.z + cy->h * cy->vec3.z, &vec3_cy);
	vector_ab(cy->pos, vec3_cy, vec3);
	vector_ab(cy->pos, ray->origin, vec3 + 1);

	abcdef[0] = dot_product(vec3[0], vec3[0]);
	abcdef[1] = dot_product(vec3[0], ray->dir);
	abcdef[2] = dot_product(vec3[0], vec3[1]);

	abcdef[3] = abcdef[0] - abcdef[1] * abcdef[1];
	abcdef[4] = abcdef[0] * dot_product(vec3[1], ray->dir) - abcdef[2] * abcdef[1];
	abcdef[5] = abcdef[0] * dot_product(vec3[1], vec3[1]) - abcdef[2] * abcdef[2]
			- cy->d / 2 * cy->d / 2 * abcdef[0];

	hty[0] = abcdef[4] * abcdef[4] -  abcdef[3] * abcdef[5];
	if (hty[0] < 0.0f)
		return (false);
	hty[0] = sqrtf(hty[0]);

	hty[1] = (-1 * abcdef[4] - hty[0]) / abcdef[3];
	hty[2] = abcdef[2] + hty[1] * abcdef[1];
	if (hty[2] > 0.0 && hty[2] < abcdef[0])
		create_hit(hty[1], cy, NULL, ray);	
	
	hty[1] = (-1 * abcdef[4] + hty[0]) / abcdef[3];
	hty[3] = abcdef[2] + hty[1] * abcdef[1];
	if (hty[3] > 0.f && hty[3] < abcdef[0])
		create_hit(hty[1], cy, NULL, ray);	

/*
	hty[1] = abcdef[0] * (hty[2] >= 0) - abcdef[2] / abcdef[1];
	if (fabsf(abcdef[4] + abcdef[3] * hty[1]) < hty[2])
		create_hit(hty[1], cy, NULL, ray);
*/
	check_cylinder_extremity(cy, vec3_cy, ray);
	if (get_hit(&hit) != -1)
		return (true);
	return (false);
}

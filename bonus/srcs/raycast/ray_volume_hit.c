/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_volume_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:39:27 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 18:19:19 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"
#include "libft.h"
#include <math.h>

t_bool	is_aabb_hit(t_ray ray, t_box aabb)
{
	double	t[6];
	double	tmin;
	double	tmax;

	t[0] = (aabb.min.x - ray.origin.x) / ray.dir.x;
	t[1] = (aabb.max.x - ray.origin.x) / ray.dir.x;
	t[2] = (aabb.min.y - ray.origin.y) / ray.dir.y;
	t[3] = (aabb.max.y - ray.origin.y) / ray.dir.y;
	t[4] = (aabb.min.z - ray.origin.z) / ray.dir.z;
	t[5] = (aabb.max.z - ray.origin.z) / ray.dir.z;
	tmin = maxd(maxd(mind(t[0], t[1]), mind(t[2], t[3])),
			mind(t[4], t[5]));
	tmax = mind(mind(maxd(t[0], t[1]), maxd(t[2], t[3])),
			maxd(t[4], t[5]));
	if (tmin > tmax)
		return (false);
	return (true);
}

double	solve_quadratic(double a, double b, double c)
{
	double	discriminant;
	double	t0;
	double	t1;

	discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0)
		return (-1);
	t0 = (-b - sqrtf(discriminant)) / (2 * a);
	t1 = (-b + sqrtf(discriminant)) / (2 * a);
	if (t0 > t1 || (t0 < 0 && t1 >= 0))
		return (t1);
	return (t0);
}

t_bool	is_sphere_hit(t_ray *ray, t_vol *sp)
{
	t_pos	e;
	double	abc[3];
	double	t;

	vector_ab(sp->pos, ray->origin, &e);
	abc[0] = dot_product(ray->dir, ray->dir);
	abc[1] = 2.0 * dot_product(e, ray->dir);
	abc[2] = dot_product(e, e) - powf(sp->d / 2, 2);
	t = solve_quadratic(abc[0], abc[1], abc[2]);
	if (t == -1)
		return (false);
	if (t < 0)
		return (false);
	create_hit(t, sp, NULL, ray);
	return (true);
}

t_bool	is_plane_hit(t_ray *ray, t_plane *pl)
{
	double	denom;
	double	t;
	t_pos	e;

	denom = dot_product(pl->vec3, ray->dir);
	if (fabs(denom) > 0.0001f)
	{
		vector_ab(ray->origin, pl->pos, &e);
		t = dot_product(e, pl->vec3) / denom;
		if (t >= 0.0001f)
		{
			create_hit(t, NULL, pl, ray);
			return (true);
		}
	}
	return (false);
}

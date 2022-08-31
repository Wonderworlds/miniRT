/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_volume_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:39:27 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/31 14:12:10 by fmauguin         ###   ########.fr       */
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
	t[1] = (aabb.min.y - ray.origin.y) / ray.dir.y;
	t[2] = (aabb.min.z - ray.origin.z) / ray.dir.z;
	t[3] = (aabb.max.x - ray.origin.x) / ray.dir.x;
	t[4] = (aabb.max.y - ray.origin.y) / ray.dir.y;
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

/*t_bool	is_sphere_hit(t_ray *ray, t_vol *sp)
{
	t_pos	e;
	float	r;
	float	a;
	float	b;
	float	f;
	float	len_squared;
	t_hit	hit;

	vector_ab(ray->origin, sp->pos, &e);
	r = sp->d / 2;
	len_squared = powf(dist_ab(&ray->origin, &sp->pos), 2);
	a = dot_product(e, ray->dir);
	b = sqrtf(len_squared - (a * a));
	f = sqrtf((r * r) - (b * b));

	// No collision
	if (r * r - len_squared + a * a < 0)
	   return false;
	else if (len_squared < r * r)
		hit.dst_origin = a + f;
	else
		hit.dst_origin = a - f;
	col_cpy(&sp->col, &hit.col);
	update_hit(&hit);
	return (true);
}*/

t_bool	is_sphere_hit(t_ray *ray, t_vol *sp)
{
	t_pos	e;
	t_hit	hit;
	float	rabc[4];
	float	discriminant;

	vector_ab(sp->pos, ray->origin, &e);
	rabc[0] = sp->d / 2;
	rabc[1] = dot_product(ray->dir, ray->dir);
	rabc[2] = 2.0 * dot_product(e, ray->dir);
	rabc[3] = dot_product(e, e) - rabc[0] * rabc[0];
	discriminant = (rabc[2] * rabc[2]) - (4 * rabc[1] * rabc[3]);
	if (discriminant > 0)
	{
		hit.dst_origin = dist_ab(&sp->pos, &ray->origin) - rabc[0];
		col_cpy(&sp->col, &hit.col);
		update_hit(&hit);
	}
	return (discriminant > 0);
}
#include <stdio.h>
t_bool is_plane_hit(t_ray *ray, t_plane *pl)
{
	float	denom;
	float	t;
	t_pos	e;
	t_hit	hit;

	denom = dot_product(pl->vec3, ray->dir);
	if (fabsf(denom) > 0.0001f) // your favorite epsilon
	{
		vector_ab(ray->origin, pl->pos, &e);
		t = dot_product(e, pl->vec3) / denom;
		if (t >= 0.0001f)
		{
			hit.dst_origin = t;
			col_cpy(&pl->col, &hit.col);
			update_hit(&hit);
			return (true); // you might want to allow an epsilon here too
		}
	}
	return (false);
}

// t_bool is_plane_hit(t_ray *ray, t_plane *pl)
// {
// 	t_hit	hit;
// 	float	d;
// 	float	div;
// 	float	distance;

// 	d = -1 * (pl->vec3.x * pl->pos.x + pl->vec3.y * pl->pos.y
// 		+ pl->vec3.z * pl->pos.z);
// 	div = sqrtf(powf(pl->vec3.x, 2) + powf(pl->vec3.y, 2) + powf(pl->vec3.z, 2));
// 	if (div > 0.0001f)
// 	{
// 		distance = (pl->vec3.x * ray->origin.x + pl->vec3.y * ray->origin.y
// 				+ pl->vec3.z *ray->origin.z + d) / div;
// 		if (distance < 0)
// 			distance *= -1;
// 		printf("distance = %f\n", distance);
// 		hit.dst_origin = distance;
// 		col_cpy(&pl->col, &hit.col);
// 		update_hit(&hit);
// 		return (true); // you might want to allow an epsilon here too
// 	}
// 	return (false);
// }
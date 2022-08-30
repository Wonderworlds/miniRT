/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_volume_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:39:27 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/29 20:04:00 by fmauguin         ###   ########.fr       */
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

    tmin =  fmaxf(fmaxf(fminf(t[0], t[1]), fminf(t[2], t[3])), fminf(t[4], t[5]));
    tmax = fminf(fminf(fmaxf(t[0], t[1]), fmaxf(t[2], t[3])), fmaxf(t[4], t[5]));
    // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
    if (tmax < 0)
        return false;
    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
        return false;
    return true;
}

t_bool	is_sphere_hit(t_ray *ray, t_vol *sp)
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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_volume_hit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:39:27 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/29 18:55:57 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "libft.h"
#include <math.h>

t_bool is_aabb_hit(t_ray ray, t_box aabb) {
    float	t[6];
    float	tmin;
    float	tmax;

	t[0] = (aabb.min.x - ray.origin.x) / ray.dir.x;
    t[1] = (aabb.min.y - ray.origin.y) / ray.dir.y;
    t[2] = (aabb.min.y - ray.origin.z) / ray.dir.z;
    t[3] = (aabb.max.x - ray.origin.x) / ray.dir.x;
    t[4] = (aabb.max.y - ray.origin.y) / ray.dir.y;
    t[5] = (aabb.max.z - ray.origin.z) / ray.dir.z;

    tmin =  maxf(maxf(minf(t[0], t[1]), minf(t[2], t[3])), minf(t[4], t[5]));
    tmax = minf(minf(maxf(t[0], t[1]), maxf(t[2], t[3])), maxf(t[4], t[5]));

    // if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
    if (tmax < 0)
        return false;
    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax)
        return false;
    return true;
}
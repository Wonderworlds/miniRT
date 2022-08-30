/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:56:07 by amahla            #+#    #+#             */
/*   Updated: 2022/08/30 16:53:16 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "mlx_data.h"
#include <math.h>

// =================== test_color ====================
t_rgb	ray_color(t_ray ray)
{
    t_pos	vec3;
	float	t;
	t_rgb	color;

	//	ray_trace....
	vec3.x = ray.dir.x / vector_norm(ray.dir);
	vec3.y = ray.dir.y / vector_norm(ray.dir);
	vec3.z = ray.dir.z / vector_norm(ray.dir);
    t = 0.5*(vec3.y + 1.0);
	color.r = 255.999 * ((1.0-t) * 1.0 + t * 0.5);
	color.g = 255.999 * ((1.0-t) * 1.0 + t * 0.7);
	color.b = 255.999 * ((1.0-t) * 1.0 + t * 1.0);
    return (color);
}
// ===================================================

t_rgb	ray_render(int y, int x, t_cam cam)
{
	t_ray	ray;
	double	u;
	double	v;

	u = (double)x / (WIN_WIDTH - 1);
	v = (double)y / (WIN_HEIGHT - 1);
	vector_equal(cam.origin, &ray.origin);
	ray.dir.x = cam.lower_left_corner.x + u * cam.horizontal.x + v * cam.vertical.x - cam.origin.x;
	ray.dir.y = cam.lower_left_corner.y + u * cam.horizontal.y + v * cam.vertical.y - cam.origin.y;
	ray.dir.z = cam.lower_left_corner.z + u * cam.horizontal.z + v * cam.vertical.z - cam.origin.z;
	return (ray_color(ray));
}



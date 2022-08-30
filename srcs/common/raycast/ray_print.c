/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:56:07 by amahla            #+#    #+#             */
/*   Updated: 2022/08/30 19:54:16 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "mlx_data.h"
#include "minirt.h"
#include <math.h>

int	find_volume(t_bvh *root, t_ray ray, t_vol **vol)
{
	if (is_aabb_hit(ray, root->box) == true)
	{
		if (root->vol)
		{
			if (root->vol->type == SPHERE)
			{
				if (is_sphere_hit(&ray, root->vol) == true)
				{
					*vol = root->vol;
					return (1);
				}
			}
		}
		else
		{
			if (root->left)
				find_volume(root->left, ray, vol);
			if (root->right)
				find_volume(root->right, ray, vol);
		}
	}
	return (0);
}

t_rgb	ray_color(t_ray ray, t_scene *scene)
{
	t_pos	vec3;
	float	t;
	t_rgb	color;
	t_vol	*vol;
	int		is_set;

	//	ray_cast...
	is_set = 0;
	vol = NULL;
	find_volume(scene->bvh, ray, &vol);
	if (vol)
		return (vol->col);
	vec3.x = ray.dir.x / vector_norm(ray.dir);
	vec3.y = ray.dir.y / vector_norm(ray.dir);
	vec3.z = ray.dir.z / vector_norm(ray.dir);
    t = 0.5*(vec3.y + 1.0);
// =================== test_color ====================
	color.r = 255.999 * ((1.0-t) * 1.0 + t * 0.5);
	color.g = 255.999 * ((1.0-t) * 1.0 + t * 0.7);
	color.b = 255.999 * ((1.0-t) * 1.0 + t * 1.0);
// ===================================================
    return (color);
}

t_rgb	ray_render(int y, int x, t_cam cam, t_scene *scene)
{
	t_ray	ray;
	double	u;
	double	v;

	u = (double)x / (WIN_WIDTH - 1);
	v = (double)y / (WIN_HEIGHT - 1);
	vector_equal(cam.pos, &ray.origin);
	ray.dir.x = cam.lower_left_corner.x + u * cam.horizontal.x + v * cam.vertical.x - cam.origin.x;
	ray.dir.y = cam.lower_left_corner.y + u * cam.horizontal.y + v * cam.vertical.y - cam.origin.y;
	ray.dir.z = cam.lower_left_corner.z + u * cam.horizontal.z + v * cam.vertical.z - cam.origin.z;
	vector_add(cam.vec3, ray.dir, &ray.dir);
	return (ray_color(ray, scene));
}



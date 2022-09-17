/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:16:54 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/17 23:05:41 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"

void	add_coeficient(t_pos *rgb, double coef, t_rgb *col)
{
	rgb->x += (coef * col->r) / 255;
	rgb->y += (coef * col->g) / 255;
	rgb->z += (coef * col->b) / 255;
}

t_rgb	int_to_rgb(int col)
{
	unsigned int	mask;
	t_rgb			rgb;

	mask = 255 << 16;
	rgb.r = (col & mask) >> 16;
	mask >>= 8;
	rgb.g = (col & mask) >> 8;
	mask >>= 8;
	rgb.b = col & mask;
	return (rgb);
}

void	apply_light(t_hit *hit_from_camera, t_pos *diffuse, t_pos *dir_light,
	t_light *lights)
{
	double	coeff;

	coeff = dot_product(hit_from_camera->normal, *dir_light);
	if (coeff > 0)
	{
		coeff *= lights->r / (vector_norm(hit_from_camera->normal)
				* vector_norm(*dir_light));
		add_coeficient(diffuse, coeff, &lights->col);
	}
}

t_rgb	add_lights(t_scene *scene, t_hit *hit)
{
	t_light	*lights;
	t_pos	dir_light;
	t_hit	hit_from_camera;
	t_pos	diffuse;
	t_ray	ray_to_light;

	hit_cpy(hit, &hit_from_camera);
	set_vector(0, 0, 0, &diffuse);
	add_coeficient(&diffuse, scene->ambient->r, &scene->ambient->col);
	if (scene->lights)
	{
		lights = (t_light *)scene->lights->content;
		vector_ab(hit_from_camera.pos, lights->pos, &dir_light);
		unit_vector(&dir_light);
		reset_hit();
		create_ray(hit_from_camera.pos, dir_light, &ray_to_light);
		find_plane(scene->planes, &ray_to_light);
		if (scene->bvh)
			find_volume(scene->bvh, ray_to_light);
		if (get_hit(hit) == -1
			|| hit->dst_origin > dist_ab(&hit_from_camera.pos, &lights->pos))
			apply_light(&hit_from_camera, &diffuse, &dir_light, lights);
	}
	c_mult(&diffuse, &hit_from_camera.col, &hit_from_camera.col);
	return (hit_from_camera.col);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:16:54 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/06 21:10:06 by fmauguin         ###   ########.fr       */
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

/*t_rgb	add_lights(t_scene *scene, t_hit *hit)
{
	t_light	*lights;
	t_light	*lights1;
	t_pos	dir_light;
	double	coeff;
	t_pos	diffuse;
	t_hit	hit_from_camera;
//	t_ray	ray_to_light;

	hit_cpy(hit, &hit_from_camera);
	set_vector(0, 0, 0, &diffuse);
	lights = (t_light *)scene->lights->next->content;
	lights1 = (t_light *)scene->lights->content;

	add_coeficient(&diffuse, lights1->r, &lights1->col);
	vector_ab(hit_from_camera.pos, lights->pos, &dir_light);
	unit_vector(&dir_light);

//	// new_ray from old_hit to light, check if ther're a hit between them 
	reset_hit();
	create_ray(hit_from_camera.pos, dir_light, &ray_to_light);
	find_plane(scene->planes, &ray_to_light);
	if (scene->bvh)
		find_volume(scene->bvh, ray_to_light);
//
	// if (get_hit(&hit) == -1), there aren't a hit
	if (get_hit(hit) == -1)
	{
		ft_printf("YOOOOOOOOOOOO\n");
		coeff = dot_product(hit_from_camera.normal, dir_light);
		if (coeff > 0.f)
		{
			coeff *= lights->r / (vector_norm(hit_from_camera.normal) * vector_norm(dir_light));
			add_coeficient(&diffuse, coeff, &lights->col);
		}
	}
	c_mult(&diffuse, &hit_from_camera.col, &hit_from_camera.col);
	return (hit_from_camera.col);
}*/

t_rgb	add_lights(t_scene *scene, t_hit *hit)
{
	t_light	*lights;
	t_pos	dir_light;
	t_hit	hit_from_camera;
	double	coeff;
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
		if (scene->bvh) {
			find_volume(scene->bvh, ray_to_light);
		}
		if (get_hit(hit) == -1)
		{
			coeff = dot_product(hit_from_camera.normal, dir_light);
			if (coeff > 0)
			{
				coeff *= lights->r / (vector_norm(hit_from_camera.normal) * vector_norm(dir_light));
				add_coeficient(&diffuse, coeff, &lights->col);
			}
		}
	}
	c_mult(&diffuse, &hit_from_camera.col, &hit_from_camera.col);
	return (hit_from_camera.col);
}

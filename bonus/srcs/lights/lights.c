/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:16:54 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 18:01:44 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"

void	apply_light(t_hit *hit_from_camera, t_pos *dir_light,
	t_light *lights, t_pos	*diffuse)
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

static void	find_shadows(t_hit hit_from_camera, t_pos *dir_light,
	t_scene *scene, t_light *lights)
{
	t_ray	ray_to_light;

	vector_ab(hit_from_camera.pos, lights->pos, dir_light);
	unit_vector(dir_light);
	reset_hit();
	create_ray(hit_from_camera.pos, *dir_light, &ray_to_light);
	find_plane(scene->planes, &ray_to_light);
	if (scene->bvh)
		find_volume(scene->bvh, ray_to_light);
}

t_rgb	add_lights(t_scene *scene, t_hit *hit, t_ray *ray)
{
	t_rgb	light_specular[2];
	t_list	*lst_lights;
	t_light	*lights;
	t_pos	dir_light;
	t_hit	hit_from_camera;
	t_pos	diffuse[2];

	lst_lights = scene->lights;
	hit_cpy(hit, &hit_from_camera);
	set_color(0, 0, 0, &light_specular[0]);
	set_vector(0, 0, 0, &diffuse[0]);
	set_vector(0, 0, 0, &diffuse[1]);
	do_tex_bump(&hit_from_camera, ray);
	do_disruption(&hit_from_camera);
	if (scene->ambient)
		add_coeficient(&diffuse[0], scene->ambient->r, &scene->ambient->col);
	while (lst_lights)
	{
		lights = (t_light *)lst_lights->content;
		find_shadows(hit_from_camera, &dir_light, scene, lights);
		if (get_hit(hit) == -1
			|| hit->dst_origin > dist_ab(&hit_from_camera.pos, &lights->pos))
		{
			apply_light(&hit_from_camera, &dir_light, lights, &diffuse[0]);
			add_coeficient(&diffuse[1],
				phong_reflection(hit_from_camera, dir_light, lights, scene->cam),
				&lights->col);
			c_mult(&diffuse[1], &lights->col, &light_specular[1]);
			c_add(&light_specular[1], &light_specular[0], &light_specular[0]);
		}
		lst_lights = lst_lights->next;
	}
	c_mult(&diffuse[0], &hit_from_camera.col, &hit_from_camera.col);
	c_add(&hit_from_camera.col, &light_specular[0], &hit_from_camera.col);
	return (hit_from_camera.col);
}

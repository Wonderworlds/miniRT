/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:16:54 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/16 01:23:03 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"

void	apply_light(t_hit *hit_from_camera, t_pos *dir_light,
	t_light *lights, t_pos	*diffuse)
{
	float	coeff;

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

static void	add_lights_loop(t_scene *scene, t_hit *hit,
			t_help_light *h_light, t_list *lst_lights)
{
	while (lst_lights)
	{
		h_light->lights = (t_light *)lst_lights->content;
		find_shadows(h_light->hit_from_camera, &h_light->dir_light,
			scene, h_light->lights);
		if (get_hit(hit) == -1
			|| hit->dst_origin > dist_ab(&h_light->hit_from_camera.pos,
				&h_light->lights->pos))
		{
			bump_map(&h_light->hit_from_camera, h_light->lights);
			apply_light(&h_light->hit_from_camera, &h_light->dir_light,
				h_light->lights, &h_light->diffuse[0]);
			add_coeficient(&h_light->diffuse[1],
				phong_reflection(h_light->hit_from_camera, h_light->dir_light,
					h_light->lights, scene->cam), &h_light->lights->col);
			c_mult(&h_light->diffuse[1], &h_light->lights->col,
				&h_light->light_specular[1]);
			c_add(&h_light->light_specular[1], &h_light->light_specular[0],
				&h_light->light_specular[0]);
		}
		lst_lights = lst_lights->next;
	}
}

t_rgb	add_lights(t_scene *scene, t_hit *hit)
{
	t_help_light	h_light;

	hit_cpy(hit, &h_light.hit_from_camera);
	set_color(0, 0, 0, &h_light.light_specular[0]);
	set_vector(0, 0, 0, &h_light.diffuse[0]);
	set_vector(0, 0, 0, &h_light.diffuse[1]);
	do_tex_bump(&h_light.hit_from_camera);
	do_disruption(&h_light.hit_from_camera);
	if (scene->ambient)
	{
		bump_map(&h_light.hit_from_camera, scene->ambient);
		add_coeficient(&h_light.diffuse[0], scene->ambient->r,
			&scene->ambient->col);
	}
	add_lights_loop(scene, hit, &h_light, scene->lights);
	c_mult(&h_light.diffuse[0], &h_light.hit_from_camera.col,
		&h_light.hit_from_camera.col);
	c_add(&h_light.hit_from_camera.col, &h_light.light_specular[0],
		&h_light.hit_from_camera.col);
	return (h_light.hit_from_camera.col);
}

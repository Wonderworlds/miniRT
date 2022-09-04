/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:16:54 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/04 19:05:31 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"

t_rgb	add_lights(t_scene *scene, t_hit *hit)
{
	t_light	*lights;
	t_ray	ray_light;
	t_pos	dir_light;
	t_rgb	diffuse;
	float	coeff;

	diffuse = gen_rgb(0, 0, 0);
	lights = (t_light *)scene->lights->content;
	vector_ab(hit->pos, lights->pos, &dir_light);
	vector_add(hit->pos, dir_light, &dir_light);
	create_ray(hit->pos, dir_light, &ray_light);
	coeff = maxf(dot_product(hit->normal, ray_light.dir), 0.0f) / powf(dist_ab(&hit->pos, &lights->pos), 2);
	c_add(&diffuse, &lights->col, &diffuse);
	c_scale(coeff, &diffuse);
	c_scale(ALBEDO, &diffuse);
	c_mult(&diffuse, &hit->col, &hit->col);
	return (hit->col);
}
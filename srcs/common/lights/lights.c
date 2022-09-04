/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:16:54 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/04 20:46:44 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"


void	add_coeficient(t_rgb *rgb, float coef, t_rgb *col)
{
	rgb->r += coef * col->r / 255;
	rgb->g += coef * col->g / 255;
	rgb->b += coef * col->b / 255;
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

t_rgb	add_lights(t_scene *scene, t_hit *hit)
{
	t_light	*lights;
	t_ray	ray_light;
	t_pos	dir_light;
	t_rgb	diffuse;
	float	coeff;

	diffuse = gen_rgb(0, 0, 0);
	lights = (t_light *)scene->lights->next->content;
	vector_ab(hit->pos, lights->pos, &dir_light);
	vector_add(hit->pos, dir_light, &dir_light);
	coeff = dot_product(hit->normal, ray_light.dir);
	if (coeff > 0)
	{
		coeff *= lights->r / (vector_norm(hit->pos) * vector_norm(dir_light));
		add_coeficient(&diffuse, coeff, &lights->col);
	}
	c_mult(&diffuse, &hit->col, &hit->col);
	return (hit->col);
}
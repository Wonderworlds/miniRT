/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:16:54 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/04 21:50:54 by fmauguin         ###   ########.fr       */
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

t_rgb	add_lights(t_scene *scene, t_hit *hit)
{
	t_light	*lights;
	t_light	*lights1;
	t_pos	dir_light;
	double	coeff;
	t_pos	diffuse;

	set_vector(0, 0, 0, &diffuse);
	lights = (t_light *)scene->lights->next->content;
	lights1 = (t_light *)scene->lights->content;
	add_coeficient(&diffuse, lights1->r, &lights1->col);
	vector_ab(hit->pos, lights->pos, &dir_light);
	unit_vector(&dir_light);
	coeff = dot_product(hit->normal, dir_light);
	if (coeff > 0)
	{
		coeff = lights->r * (dot_product(hit->normal, dir_light) / (vector_norm(hit->normal) * vector_norm(dir_light)));
		add_coeficient(&diffuse, coeff, &lights->col);
	}
	c_mult(&diffuse, &hit->col, &hit->col);
	return (hit->col);
}
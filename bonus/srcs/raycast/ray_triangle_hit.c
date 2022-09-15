/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_triangle_hit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:11:07 by amahla            #+#    #+#             */
/*   Updated: 2022/09/15 18:57:35 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"
#include "libft.h"
#include <math.h>

t_bool	is_triangle_hit(t_ray *ray, t_vol *tr)
{
	t_pos	vec3[5];
	double	abcde[5];

	vector_ab(tr->tr[0], tr->tr[1], &vec3[0]);
	vector_ab(tr->tr[0], tr->tr[2], &vec3[1]);
	cross_product(ray->dir, vec3[1], &vec3[2]);
	abcde[0] = dot_product(vec3[0], vec3[2]);
	if (abcde[0] > -0.00001 && abcde[0] < 0.00001)
		return (false);
	abcde[1] = 1.0 / abcde[0];
	vector_ab(tr->tr[0], ray->origin, &vec3[3]);
	abcde[2] = abcde[1] * dot_product(vec3[2], vec3[3]);
	if (abcde[2] < 0.0 /*|| abcde[2] > 1.0*/)
		return (false);
	cross_product(vec3[3], vec3[0], &vec3[4]);
	abcde[3] = abcde[1] * dot_product(ray->dir, vec3[4]);
	if (abcde[3] < 0.0 || abcde[3] + abcde[2] > 1.0)
		return (false);
	abcde[5] = abcde[1] * dot_product(vec3[1], vec3[4]);
	if (abcde[5] > 0.00001)
	{
		create_hit(abcde[5], tr, NULL, ray);
		return (true);
	}
	return (false);
}


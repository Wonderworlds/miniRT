/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:17:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 18:57:39 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include <math.h>

void	unit_vector(t_pos *vec)
{
	double	mag;
	t_pos	tmp;

	set_vector(0, 0, 0, &tmp);
	mag = dist_ab(&tmp, vec);
	if (mag == 0)
		return ;
	vec->x /= mag;
	vec->y /= mag;
	vec->z /= mag;
}

void	vector_scale(double scale, t_pos *dst)
{
	dst->x *= scale;
	dst->y *= scale;
	dst->z *= scale;
}

t_pos	gen_vec(double x, double y, double z)
{
	t_pos	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

void	vector_div(t_pos a, float b, t_pos *dst)
{
	dst->x = a.x / b;
	dst->y = a.y / b;
	dst->z = a.z / b;
}


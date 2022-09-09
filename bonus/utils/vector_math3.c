/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:17:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/06 16:37:10 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include <math.h>

void	unit_vector(t_pos *vec)
{
	float	mag;
	t_pos	tmp;

	set_vector(0, 0, 0, &tmp);
	mag = dist_ab(&tmp, vec);
	if (mag == 0)
		return ;
	vec->x /= mag;
	vec->y /= mag;
	vec->z /= mag;
}

void	vector_scale(float scale, t_pos *dst)
{
	dst->x *= scale;
	dst->y *= scale;
	dst->z *= scale;
}

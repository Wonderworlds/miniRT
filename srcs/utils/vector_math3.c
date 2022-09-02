/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:17:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/02 11:58:28 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include <math.h>

float	magnitude_vec(const t_pos *vec)
{
	return (fabsf(vec->x) + fabsf(vec->y) + fabsf(vec->z));
}

void	unit_vector(t_pos *vec)
{
	float	mag;

	mag = magnitude_vec(vec);
	if (mag == 0)
		return ;
	vec->x /= mag;
	vec->y /= mag;
	vec->z /= mag;
}

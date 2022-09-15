/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:17:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 18:10:37 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include <math.h>

double	dot_product(t_pos a, t_pos b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

double	vector_norm(t_pos vec)
{
	return (sqrt(dot_product(vec, vec)));
}

void	vector_ab(t_pos a, t_pos b, t_pos *vec)
{
	vec->x = b.x - a.x;
	vec->y = b.y - a.y;
	vec->z = b.z - a.z;
}

void	vector_add(t_pos a, t_pos b, t_pos *vec)
{
	vec->x = a.x + b.x;
	vec->y = a.y + b.y;
	vec->z = a.z + b.z;
}

void	set_vector(double x, double y, double z, t_pos *vec)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

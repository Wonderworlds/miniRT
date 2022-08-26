/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:17:16 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/26 21:06:47 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include <math.h>

double	dist_ab(const t_pos *a, const t_pos *b)
{
	return (fabs((b->x - a->x) + (b->y - a->y) + (b->z - a->z)));
}

void	vector_equal(t_pos src, t_pos *dst)
{
	dst->x = src.x;
	dst->y = src.y;
	dst->z = src.z;
}

void	cross_product(t_pos a, t_pos b, t_pos *dst)
{
	dst->x = a.y * b.z - a.z * b.y;
	dst->y = a.z * b.x - a.x * b.z;
	dst->z = a.x * b.y - a.y * b.x;
}

void	vector_multi(t_pos a, t_pos b, t_pos *dst)
{
	dst->x = a.x * b.x;
	dst->y = a.y * b.y;
	dst->z = a.z * b.z;
}

void	vector_sub(t_pos a, t_pos b, t_pos *dst)
{
	dst->x = a.x - b.x;
	dst->y = a.y - b.y;
	dst->z = a.z - b.z;
}

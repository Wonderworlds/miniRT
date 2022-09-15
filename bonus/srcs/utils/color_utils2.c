/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 21:17:57 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/16 00:16:13 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"

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

void	add_coeficient(t_pos *rgb, float coef, t_rgb *col)
{
	rgb->x += (coef * col->r) / 255;
	rgb->y += (coef * col->g) / 255;
	rgb->z += (coef * col->b) / 255;
}

void	c_mult_basic(t_rgb *mult, t_rgb *dest)
{
	dest->r = (mult->r * dest->r) / 255;
	dest->g = (mult->g * dest->g) / 255;
	dest->b = (mult->b * dest->b) / 255;
}

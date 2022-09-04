/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 17:41:57 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/03 14:15:16 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"

int	check_rgb(int col)
{
	if (col > 255)
		return (255);
	else if (col < 0)
		return (0);
	return (col);
}

void	c_scale(const float f, t_rgb *rgb)
{
	rgb->r = check_rgb(f * rgb->r);
	rgb->g = check_rgb(f * rgb->g);
	rgb->b = check_rgb(f * rgb->b);
}

void	c_add(const t_rgb *c1, const t_rgb *c2, t_rgb *dest)
{
	dest->r = check_rgb(c1->r + c2->r);
	dest->g = check_rgb(c1->g + c2->g);
	dest->b = check_rgb(c1->b + c2->b);
}

void	c_mult(const t_rgb *c1, const t_rgb *c2, t_rgb *dest)
{
	dest->r = check_rgb((c1->r * c2->r) / 255);
	dest->g = check_rgb((c1->g + c2->g) / 255);
	dest->b = check_rgb((c1->b + c2->b) / 255);
}

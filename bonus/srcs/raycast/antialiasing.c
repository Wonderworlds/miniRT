/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:14:36 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 20:02:02 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"

void	rand_f(t_resolut *res, int index, t_couplef *uv)
{
	if (res->aliasing == 1 || index == 0)
	{
		uv->x = 0;
		uv->y = 0;
	}
	else
	{
		uv->x = cosf(index * res->subdivide) / (res->win_width - 1);
		uv->y = sinf(index * res->subdivide) / (res->win_height - 1);
		uv->x /= 2;
		uv->y /= 2;
	}
}

void	write_color(t_rgb *pixel_color, t_resolut *res)
{
	double	scale;

	scale = 1.0 / res->aliasing;
	pixel_color->r *= scale;
	pixel_color->g *= scale;
	pixel_color->b *= scale;
}

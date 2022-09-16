/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:14:36 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 16:19:06 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdlib.h>
#include "minirt.h"

float	random_float(t_resolut *res)
{
	if (res->aliasing == 1)
		return (0.f);
	return (rand() / (RAND_MAX + 1.0));
}

void	write_color(t_rgb *pixel_color, t_resolut *res)
{
	double	scale;

	scale = 1.0 / res->aliasing;
	pixel_color->r *= scale;
	pixel_color->g *= scale;
	pixel_color->b *= scale;
}

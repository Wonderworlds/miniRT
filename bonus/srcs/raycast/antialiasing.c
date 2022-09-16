/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   antialiasing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:14:36 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 14:22:33 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdlib.h>
#include "minirt.h"

float random_float(void)
{
	if (SAMPLES_PER_PIXEL == 1)
		return (0.f);
    return rand() / (RAND_MAX + 1.0);
}

void	write_color(t_rgb *pixel_color)
{
    double scale;

    scale = 1.0 / SAMPLES_PER_PIXEL;
    pixel_color->r *= scale;
    pixel_color->g *= scale;
    pixel_color->b *= scale;
}

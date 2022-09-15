/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:47:55 by amahla            #+#    #+#             */
/*   Updated: 2022/09/15 18:58:48 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "minirt.h"
#include "libft.h"
#include "utils.h"
#include <math.h>

void	checkerboard(t_hit *hit)
{
	double sines;

	sines = sinf(10 * hit->pos.x) * sinf(10 * hit->pos.y)
		* sinf(10 * hit->pos.z);
	if (sines < 0)
	{
		hit->col.r = 0;
		hit->col.g = 0;
		hit->col.b = 0;
	}
}

void	do_disruption(t_hit *hit)
{
	t_plane		*pl;
	t_vol		*vol;

	pl = NULL;
	vol = NULL;
	if (hit->vol_type == PLANE)
	{
		pl = (t_plane *)hit->vol;
		if (pl->disruption == CHECKERBOARD)
			checkerboard(hit);
	}
	else
	{
		vol = (t_vol *)hit->vol;
		if (vol->disruption == CHECKERBOARD)
			checkerboard(hit);
	}
}

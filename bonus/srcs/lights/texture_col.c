/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:45:33 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 15:48:42 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "minirt.h"
#include "libft.h"
#include "utils.h"
#include <math.h>

t_rgb	rgb2gray(t_rgb rgb)
{
	unsigned char	gray;

	gray = 0.299 * rgb.r + 0.587 * rgb.g + 0.114 * rgb.b;
	return (gen_rgb(gray, gray, gray));
}

static int	get_tex_pix(t_xpm *xpm, float u, float v)
{
	int	x;
	int	y;

	x = ((int)u) * (xpm->bpp / 8);
	y = ((int)v) * xpm->line_len;
	return (*((int *)(xpm->addr + x + y)));
}

void	bump_map(t_hit *hit, t_xpm *bump, t_ray *ray, t_couplef *uv)
{
	t_rgb	bump_pix;
	double	coeff;

	bump_pix = rgb2gray(int_to_rgb(get_tex_pix(bump, uv->x, uv->y)));
	coeff = ((255 * 3) - bump_pix.r - bump_pix.g - bump_pix.b) / (255 * 3);
	(void)ray;
	(void)coeff;
	(void)hit;
}

static void do_tex_bump2(t_xpm *tex, t_xpm *bump, t_hit *hit)
{
	t_couplef	uv;
	t_rgb		tex_rgb;

	if (tex || bump)
	{
		if (hit->vol_type == SPHERE)
			get_uv_sp(hit, hit->vol, &uv);
		else if (hit->vol_type == CYLINDER)
			get_uv_cy(hit, hit->vol, &uv);
		else if (hit->vol_type == PLANE)
			get_uv_pl(hit, hit->vol, &uv);
		else if (hit->vol_type == TRIANGLE)
			get_uv_tr(hit, hit->vol, &uv);
		if (tex)
		{
			tex_rgb = int_to_rgb(get_tex_pix(tex, uv.x, uv.y));
			c_mult_basic(&tex_rgb, &hit->col);
		}
		if (bump)
		{
			tex_rgb = rgb2gray(int_to_rgb(get_tex_pix(bump, uv.x, uv.y)));
			bump->coeff = ((255 * 3) - tex_rgb.r - tex_rgb.g - tex_rgb.b)
				/ (255 * 3);
		}
	}
}

void	do_tex_bump(t_hit *hit)
{
	t_plane		*pl;
	t_vol		*vol;

	pl = NULL;
	vol = NULL;
	if (hit->vol_type == PLANE)
	{
		pl = (t_plane *)hit->vol;
		do_tex_bump2(pl->tex, pl->bump, hit);
	}
	else
	{
		vol = (t_vol *)hit->vol;
		do_tex_bump2(vol->tex, vol->bump, hit);
	}
}

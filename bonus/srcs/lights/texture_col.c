/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:45:33 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 18:08:31 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "minirt.h"
#include "libft.h"
#include "utils.h"
#include <math.h>

#define BUMP_SCALE 10

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

void	bump_map(t_hit *hit, t_light *light)
{
	double	coeff;

	coeff = -1;
	if (hit->vol_type == PLANE && ((t_plane *)hit->vol)->bump)
		coeff = ((t_plane *)hit->vol)->bump->coeff;
	else if (hit->vol_type != PLANE && ((t_vol *)hit->vol)->bump)
		coeff = ((t_vol *)hit->vol)->bump->coeff;
	if (coeff == -1)
		return ;
	light->r = light->r_o * (coeff + 0.6f);
}

static void do_tex_bump2(t_xpm *tex, t_xpm *bump, t_hit *hit)
{
	t_couplef	uv;
	t_rgb		tex_rgb;

	if (tex)
	{
		if (hit->vol_type == SPHERE)
			get_uv_sp(hit, hit->vol, &uv, tex);
		else if (hit->vol_type == CYLINDER)
			get_uv_cy(hit, hit->vol, &uv, tex);
		else if (hit->vol_type == PLANE)
			get_uv_pl(hit, hit->vol, &uv, tex);
		else if (hit->vol_type == TRIANGLE)
			get_uv_tr(hit, hit->vol, &uv, tex);
		tex_rgb = int_to_rgb(get_tex_pix(tex, uv.x, uv.y));
		c_mult_basic(&tex_rgb, &hit->col);
	}
	if (bump)
	{
		if (hit->vol_type == SPHERE)
			get_uv_sp(hit, hit->vol, &uv, bump);
		else if (hit->vol_type == CYLINDER)
			get_uv_cy(hit, hit->vol, &uv, bump);
		else if (hit->vol_type == PLANE)
			get_uv_pl(hit, hit->vol, &uv, bump);
		else if (hit->vol_type == TRIANGLE)
			get_uv_tr(hit, hit->vol, &uv, bump);
		tex_rgb = int_to_rgb(get_tex_pix(bump, uv.x, uv.y));
		bump->coeff = (float)(tex_rgb.r + tex_rgb.g + tex_rgb.b) / (255.0f * 3.0f);
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

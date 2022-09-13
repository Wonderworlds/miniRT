/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:45:33 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/13 21:36:26 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include <math.h>

t_pos	ft_vector_rotate_cw(t_pos vector)
{
	float	tmp;

	tmp = vector.z;
	vector.z = vector.y;
	vector.y = vector.x;
	vector.x = tmp;
	return (vector);
}

t_pos	ft_vector_rotate_ccw(t_pos vector)
{
	float	tmp;

	tmp = vector.x;
	vector.x = vector.y;
	vector.y = vector.z;
	vector.z = tmp;
	return (vector);
}

t_rgb	rgb2gray(t_rgb rgb)
{
	unsigned char	gray;

	gray = 0.299 * rgb.r + 0.587 * rgb.g + 0.114 * rgb.b;
	return (gen_rgb(gray, gray, gray));
}


static void	get_uv(t_hit *hit, t_pos ray_dir, t_couple *uv, t_xpm *xpm)
{
	t_pos	local;
	t_pos	ulocal;
	double	costheta;

	vector_sub(hit->normal, ray_dir, &local);
	vector_equal(local, &ulocal);
	unit_vector(&ulocal);
	costheta = dot_product(ulocal, ft_vector_rotate_cw(hit->normal));
	uv->x = sqrt(dot_product(local, ulocal)) * costheta * xpm->w;
	costheta = dot_product(ulocal, ft_vector_rotate_ccw(hit->normal));
	uv->y = sqrt(dot_product(local, ulocal)) * costheta * xpm->h;
}

static int	get_tex_pix(t_xpm *xpm, float u, float v)
{
	int	x;
	int	y;

	x = fmodf(fmodf(u, xpm->w) + xpm->w, xpm->w);
	y = fmodf(fmodf(v, xpm->h) + xpm->h, xpm->h);
	return (xpm->addr[x * y]);
}

void	get_tex_pixel(t_vol *vol, t_hit *hit, t_ray *ray)
{
	t_couple	uv;
	t_rgb		tex_rgb;

	if (vol->tex)
	{
		get_uv(hit, ray->dir, &uv, vol->tex);
		tex_rgb = int_to_rgb(get_tex_pix(vol->tex, uv.x, uv.y));
		c_mult_basic(&tex_rgb, &vol->col);
	}
	if (vol->bump)
	{
		get_uv(hit, ray->dir, &uv, vol->bump);
		tex_rgb = rgb2gray(int_to_rgb(get_tex_pix(vol->bump, uv.x, uv.y)));
		c_mult_basic(&tex_rgb, &vol->col);
	}
}

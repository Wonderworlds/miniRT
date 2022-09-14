/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:45:33 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/14 14:57:50 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "libft.h"
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


static void	get_uv(t_hit *hit, t_pos *vec_ref, t_couplef *uv, t_xpm *xpm)
{
	t_pos	local;
	t_pos	ulocal;
	double	costheta;

	vector_sub(hit->normal, *vec_ref, &local);
	vector_equal(local, &ulocal);
	unit_vector(&ulocal);
	costheta = dot_product(ulocal, ft_vector_rotate_cw(hit->normal));
	uv->x = sqrt(dot_product(local, ulocal)) * costheta * xpm->w;
	costheta = dot_product(ulocal, ft_vector_rotate_ccw(hit->normal));
	uv->y = sqrt(dot_product(local, ulocal)) * costheta * xpm->h;
}

static void	get_uv_sp(t_hit *hit, t_vol *sp, t_couplef *uv)
{
	t_pos	on_sp;

	vector_sub(hit->pos, sp->pos, &on_sp);
	unit_vector(&on_sp);
	uv->x = 0.5 + atan2f(on_sp.z, on_sp.x) / M_PI * 0.5;
	uv->y = 0.5 - asinf(on_sp.y) / M_PI;
	uv->x *= sp->tex->w;
	uv->y *= sp->tex->h;
}

static void	get_uv_pl(t_hit *hit, t_plane *pl, t_couplef *uv)
{
	t_pos	on_pl;
	t_pos	u;
	t_pos	v;

	cross_product(hit->normal, gen_vec(1, 0, 0), &u);
	if (u.x == 0 && u.y == 0 && u.z == 0)
		cross_product(hit->normal, gen_vec(0, 0, 1), &u);
	unit_vector(&u);
	cross_product(hit->normal, u, &v);
	unit_vector(&v);
	vector_sub(hit->pos, pl->pos, &on_pl);
	uv->x = dot_product(u, on_pl);
	uv->y = dot_product(v, on_pl);
	uv->x = fmodf(fmodf(uv->x, pl->tex->w) + pl->tex->w, pl->tex->w);
	uv->y = fmodf(fmodf(uv->y, pl->tex->h) + pl->tex->h, pl->tex->h);
}

static int	get_tex_pix(t_xpm *xpm, float u, float v)
{
	int	x;
	int	y;

	x = xpm->w - u;
	y = v;
	x *= xpm->bpp / 8;
	y *= xpm->line_len;
	return (*((int *)(xpm->addr + x + y)));
}

static void get_tex_pixel2(t_xpm *tex, t_xpm *bump, t_hit *hit, t_ray *ray)
{
	t_couplef	uv;
	t_rgb		tex_rgb;

	if (tex)
	{
		if (hit->vol_type == SPHERE)
			get_uv_sp(hit, hit->vol, &uv);
		if (hit->vol_type == PLANE)
			get_uv_pl(hit, hit->vol, &uv);
		tex_rgb = int_to_rgb(get_tex_pix(tex, uv.x, uv.y));
		c_mult_basic(&tex_rgb, &hit->col);
	}
	if (bump)
	{
		get_uv(hit, &ray->dir, &uv, bump);
		tex_rgb = rgb2gray(int_to_rgb(get_tex_pix(bump, uv.x, uv.y)));
		c_mult_basic(&tex_rgb, &hit->col);
	}
}

void	get_tex_pixel(t_hit *hit, t_ray *ray)
{
	t_plane		*pl;
	t_vol		*vol;

	pl = NULL;
	vol = NULL;
	if (hit->vol_type == PLANE)
	{
		pl = (t_plane *)hit->vol;
		get_tex_pixel2(pl->tex, pl->bump, hit, ray);
	}
	else
	{
		vol = (t_vol *)hit->vol;
		get_tex_pixel2(vol->tex, vol->bump, hit, ray);
	}

}

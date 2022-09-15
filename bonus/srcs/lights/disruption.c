/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:47:55 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 00:42:59 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "minirt.h"
#include "libft.h"
#include "utils.h"
#include <math.h>

void	checkerboard_sphere(t_couplef uv, t_hit *hit)
{
	float	u2;
	float	v2;
	int		res;

	u2 = floorf(uv.x * 14);
	v2 = floorf(uv.y * 14);
	res = u2 + v2;
	if (res % 2)
	{
		hit->col.r = 0;
		hit->col.g = 0;
		hit->col.b = 0;
	}
}

void	get_uvw_sp(t_hit *hit, t_vol *sp, t_couplef *uv)
{
	t_pos	on_sp;

	vector_sub(hit->pos, sp->pos, &on_sp);
	unit_vector(&on_sp);
	uv->x = 0.5 + atan2f(on_sp.z, on_sp.x) / M_PI * 0.5;
	uv->y = 0.5 - asinf(on_sp.y) / M_PI;
}

void	checkerboard(t_pos on_vol, t_hit *hit)
{
	float sines;

	sines = sinf(10 * on_vol.x) * sinf(10 * on_vol.y)
		* sinf(10 * on_vol.z);
	if (sines < 0)
	{
		hit->col.r = 0;
		hit->col.g = 0;
		hit->col.b = 0;
	}
}

void	get_uvw_pl(t_hit *hit, t_plane *pl, t_pos *on_pl)
{
	t_pos	u;
	t_pos	v;
	t_pos	w;

	cross_product(hit->normal, gen_vec(1, 0, 0), &u);
	if (u.x == 0 && u.y == 0 && u.z == 0)
		cross_product(hit->normal, gen_vec(0, 0, 1), &u);
	unit_vector(&u);
	cross_product(hit->normal, u, &v);
	unit_vector(&v);
	cross_product(v, u, &w);
	unit_vector(&w);
	vector_sub(hit->pos, pl->pos, on_pl);
	on_pl->x = dot_product(v, *on_pl);
	on_pl->z = dot_product(u, *on_pl);
	on_pl->y = dot_product(hit->normal, *on_pl);
}


void	get_uvw_cy(t_hit *hit, t_vol *cy, t_couplef *uv)
{
	t_pos	on_cy;
	t_pos	proj;
	t_pos	u;
	t_pos	v;
	float	add;

	cross_product(cy->vec3, gen_vec(1, 0, 0), &u);
	if (u.x == 0 && u.y == 0 && u.z == 0)
		cross_product(cy->vec3, gen_vec(0, 0, 1), &u);
	unit_vector(&u);
	cross_product(cy->vec3, u, &v);
	unit_vector(&v);
	vector_sub(hit->pos, cy->pos, &on_cy);
	proj.x = dot_product(v, on_cy);
	proj.y = dot_product(cy->vec3, on_cy);
	proj.z = dot_product(u, on_cy);
	if (proj.y < 0)
		proj.y = 0;
	float theta = atan2f(proj.x, proj.z);
    float rawU = theta / (2 * M_PI);
	if (proj.x == 0 && proj.z == 0)
		add = 0;
	else
		add = vector_norm(gen_vec(proj.x, 0, proj.z));
	if (proj.y >= cy->h)
		proj.y = cy->h + cy->d - add;
	else
		proj.y += add;
	proj.y /= (cy->h + cy->d);
	uv->x = 1 - (rawU + 0.5);
	uv->y = fmodf(fmodf(proj.y, 1) + 1, 1);
}

void	get_uvw_tr(t_hit *hit, t_vol *tr, t_pos *on_tr)
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
	vector_sub(hit->pos, tr->tr[0], &on_pl);
	on_tr->x = dot_product(v, on_pl);
	on_tr->y = dot_product(u, on_pl);
	on_tr->z = dot_product(hit->normal, on_pl);
}

void	get_uvw_co(t_hit *hit, t_vol *co, t_couplef *uv)
{
	t_pos	on_co;
	t_pos	proj;
	t_pos	u;
	t_pos	v;
	float	add;

	cross_product(co->vec3, gen_vec(1, 0, 0), &u);
	if (u.x == 0 && u.y == 0 && u.z == 0)
		cross_product(co->vec3, gen_vec(0, 0, 1), &u);
	unit_vector(&u);
	cross_product(co->vec3, u, &v);
	unit_vector(&v);
	vector_sub(hit->pos, co->pos, &on_co);
	proj.x = dot_product(v, on_co);
	proj.y = dot_product(co->vec3, on_co);
	proj.z = dot_product(u, on_co);
	float theta = atan2f(proj.x, proj.z);
    float rawU = theta / (2 * M_PI);
	if (proj.x == 0 && proj.z == 0)
		add = 0;
	else
		add = vector_norm(gen_vec(proj.x, 0, proj.z));
	if (proj.y == 0)
		proj.y += add;
	else
		proj.y += co->d / 2;
	proj.y /= (co->h + (co->d / 2));
	uv->x = 1 - (rawU + 0.5);
	uv->y = fmodf(fmodf(proj.y, 1) + 1, 1);
}

void	do_disruption2(t_disruption disruption, t_hit *hit)
{
	t_pos		on_vol;
	t_couplef	uv;

	if (disruption != NONE)
	{
		if (hit->vol_type == SPHERE)
			get_uvw_sp(hit, hit->vol, &uv);
		else if (hit->vol_type == CONE)
			get_uvw_co(hit, hit->vol, &uv);
		else if (hit->vol_type == CYLINDER)
			get_uvw_cy(hit, hit->vol, &uv);
		else if (hit->vol_type == PLANE)
			get_uvw_pl(hit, hit->vol, &on_vol);
		else
			get_uvw_tr(hit, hit->vol, &on_vol);
		if (disruption == CHECKERBOARD && (hit->vol_type == SPHERE
				|| hit->vol_type == CONE || hit->vol_type == CYLINDER))
			checkerboard_sphere(uv, hit);
		else if (disruption == CHECKERBOARD)
			checkerboard(on_vol, hit);
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
		do_disruption2(pl->disruption, hit);
	}
	else
	{
		vol = (t_vol *)hit->vol;
		do_disruption2(vol->disruption, hit);
	}
}


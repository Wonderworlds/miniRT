/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:47:55 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 01:19:41 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "minirt.h"
#include "libft.h"
#include "utils.h"
#include <math.h>

void	checkerboard(t_couplef uv, t_hit *hit)
{
	float	u2;
	float	v2;
	int		res;
	int		coeff;


	if (hit->vol_type == TRIANGLE)
		coeff = 4;
	else if (hit->vol_type == PLANE)
		coeff = 1;
	else if (hit->vol_type == SPHERE)
		coeff = 14;
	else
		coeff = 12;
	u2 = floorf(uv.x * coeff);
	v2 = floorf(uv.y * coeff);
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

void	get_uvw_pl(t_hit *hit, t_plane *pl, t_couplef *uv)
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
	uv->x = dot_product(v, on_pl);
	uv->y = dot_product(u, on_pl);
}

void	get_uvw_cy(t_hit *hit, t_vol *cy, t_couplef *uv)
{
	t_pos	on_cy;
	t_pos	proj;
	t_pos	u;
	t_pos	v;

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
	float theta = atan2f(proj.x, proj.z);
    float rawU = theta / (2 * M_PI);
	proj.y /= (cy->h + cy->d);
	uv->x = 1 - (rawU + 0.5);
	uv->y = fmodf(fmodf(proj.y, 1) + 1, 1);
}

void	get_uvw_tr(t_hit *hit, t_vol *tr, t_couplef *uv)
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
	uv->x = dot_product(v, on_pl);
	uv->y = dot_product(u, on_pl);
}

void	get_uvw_co(t_hit *hit, t_vol *co, t_couplef *uv)
{
	t_pos	on_co;
	t_pos	proj;
	t_pos	u;
	t_pos	v;

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
	proj.y /= (co->h + (co->d / 2));
	uv->x = 1 - (rawU + 0.5);
	uv->y = fmodf(fmodf(proj.y, 1) + 1, 1);
}

void	do_disruption2(t_disruption disruption, t_hit *hit)
{
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
			get_uvw_pl(hit, hit->vol, &uv);
		else
			get_uvw_tr(hit, hit->vol, &uv);
		if (disruption == CHECKERBOARD)
			checkerboard(uv, hit);
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


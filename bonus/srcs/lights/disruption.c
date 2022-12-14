/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:47:55 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 23:31:42 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "minirt.h"
#include "libft.h"
#include "utils.h"
#include <math.h>

static void	get_uv_co_and_cy2(t_pos *proj, t_vol *co, t_couplef *uv)
{
	float	theta;
	float	raw_u;
	float	add;

	theta = atan2f(proj->x, proj->z);
	raw_u = theta / (2 * M_PI);
	if (proj->x == 0 && proj->z == 0)
		add = 0;
	else
		add = vector_norm(gen_vec(proj->x, 0, proj->z));
	if (co->type == CYLINDER && proj->y >= co->h)
		proj->y = co->h + co->d - add;
	else if ((co->type == CONE && proj->y <= 0) || co->type == CYLINDER)
		proj->y += add;
	else if (co->type == CONE)
		proj->y += co->d / 2;
	if (co->type == CONE)
		proj->y /= (co->h + (co->d / 2));
	else
		proj->y /= (co->h + co->d);
	uv->x = 1 - (raw_u + 0.5);
	uv->y = fmodf(fmodf(proj->y, 1) + 1, 1);
}

void	get_uvw_co_and_cy(t_hit *hit, t_vol *co, t_couplef *uv)
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
	get_uv_co_and_cy2(&proj, co, uv);
}

void	do_disruption2(t_disruption disruption, t_hit *hit)
{
	t_couplef	uv;

	if (disruption != NONE)
	{
		if (hit->vol_type == SPHERE)
			get_uvw_sp(hit, hit->vol, &uv);
		else if (hit->vol_type == CONE || hit->vol_type == CYLINDER)
			get_uvw_co_and_cy(hit, hit->vol, &uv);
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

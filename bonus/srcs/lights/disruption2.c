/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disruption2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 17:47:55 by amahla            #+#    #+#             */
/*   Updated: 2022/09/16 02:04:17 by fmauguin         ###   ########.fr       */
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

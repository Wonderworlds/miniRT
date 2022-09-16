/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:22:29 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/16 22:38:24 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "libft.h"
#include "utils.h"
#include <math.h>

#define SUBDIVISION 3

void	get_uv_sp(t_hit *hit, t_vol *sp, t_couplef *uv, t_xpm *xpm)
{
	t_pos	on_sp;

	vector_sub(hit->pos, sp->pos, &on_sp);
	unit_vector(&on_sp);
	uv->x = 0.5 + atan2f(on_sp.z, on_sp.x) / M_PI * 0.5;
	uv->y = 0.5 - asinf(on_sp.y) / M_PI;
	uv->x = xpm->w - (uv->x * xpm->w);
	uv->y *= xpm->h;
}

void	get_uv_pl(t_hit *hit, t_plane *pl, t_couplef *uv, t_xpm *xpm)
{
	t_pos	on_pl;
	t_pos	u;
	t_pos	v;
	float	size;

	cross_product(hit->normal, gen_vec(1, 0, 0), &u);
	if (u.x == 0 && u.y == 0 && u.z == 0)
		cross_product(hit->normal, gen_vec(0, 0, 1), &u);
	unit_vector(&u);
	cross_product(hit->normal, u, &v);
	unit_vector(&v);
	vector_sub(hit->pos, pl->pos, &on_pl);
	uv->x = dot_product(v, on_pl);
	uv->y = dot_product(u, on_pl);
	size = xpm->w / SUBDIVISION;
	uv->x = fmodf(fmodf(uv->x, size) + size, size);
	size = xpm->h / SUBDIVISION;
	uv->y = fmodf(fmodf(uv->y, size) + size, size);
	uv->x *= SUBDIVISION;
	uv->y = xpm->h - (uv->y * SUBDIVISION);
}

void	get_uv_tr(t_hit *hit, t_vol *tr, t_couplef *uv, t_xpm *xpm)
{
	t_pos	on_pl;
	t_pos	u;
	t_pos	v;
	float	size;

	cross_product(hit->normal, gen_vec(1, 0, 0), &u);
	if (u.x == 0 && u.y == 0 && u.z == 0)
		cross_product(hit->normal, gen_vec(0, 0, 1), &u);
	unit_vector(&u);
	cross_product(hit->normal, u, &v);
	unit_vector(&v);
	vector_sub(hit->pos, tr->tr[0], &on_pl);
	uv->x = dot_product(v, on_pl);
	uv->y = dot_product(u, on_pl);
	size = xpm->w / SUBDIVISION;
	uv->x = fmodf(fmodf(uv->x, size) + size, size);
	size = xpm->h / SUBDIVISION;
	uv->y = fmodf(fmodf(uv->y, size) + size, size);
	uv->x *= SUBDIVISION;
	uv->x = xpm->w - uv->x;
	uv->y = xpm->h - (uv->y * SUBDIVISION);
}

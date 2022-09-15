/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:22:29 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 15:20:18 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "structs_utils.h"
#include "libft.h"
#include "utils.h"
#include <math.h>

#define SUBDIVISION 24

void	get_uv_sp(t_hit *hit, t_vol *sp, t_couplef *uv)
{
	t_pos	on_sp;

	vector_sub(hit->pos, sp->pos, &on_sp);
	unit_vector(&on_sp);
	uv->x = 0.5 + atan2f(on_sp.z, on_sp.x) / M_PI * 0.5;
	uv->y = 0.5 - asinf(on_sp.y) / M_PI;
	uv->x = sp->tex->w - (uv->x * sp->tex->w);
	uv->y *= sp->tex->h;
}

void	get_uv_cy(t_hit *hit, t_vol *cy, t_couplef *uv)
{
	t_pos	on_cy;
	t_pos	proj;
	t_pos	u;
	t_pos	v;
	double	add;

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
	if (proj.y >=  cy->d)
		proj.y = cy->d;
	float theta = atan2f(proj.x, proj.z);
    float rawU = theta / (2 * M_PI);
	if (cy->pos.x == proj.x && cy->pos.z == proj.z)
		add = 0;
	else
		add = vector_norm(gen_vec(proj.x - cy->pos.x, 0, proj.z - cy->pos.z));
	if (proj.y >= cy->h)
		proj.y = cy->h + cy->d - add;
	else
		proj.y += add;
	proj.y /= (cy->h + cy->d);
    uv->x = 1 - (rawU + 0.5);
	uv->y = fmodf(fmodf(proj.y, 1) + 1, 1);
	uv->x = cy->tex->w - (uv->x * cy->tex->w);
	uv->y = cy->tex->h - (uv->y * cy->tex->h);
}

void	get_uv_pl(t_hit *hit, t_plane *pl, t_couplef *uv)
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
	size = pl->tex->w / SUBDIVISION;
	uv->x = fmodf(fmodf(uv->x, size) + size, size);
	size = pl->tex->h / SUBDIVISION;
	uv->y = fmodf(fmodf(uv->y, size) + size, size);
	uv->x *= SUBDIVISION;
	uv->y = pl->tex->h - (uv->y * SUBDIVISION);
}


void	get_uv_tr(t_hit *hit, t_vol *tr, t_couplef *uv)
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
	size = tr->tex->w / SUBDIVISION;
	uv->x = fmodf(fmodf(uv->x, size) + size, size);
	size = tr->tex->h / SUBDIVISION;
	uv->y = fmodf(fmodf(uv->y, size) + size, size);
	uv->x *= SUBDIVISION;
	uv->x = tr->tex->w - uv->x;
	uv->y = tr->tex->h - (uv->y  * SUBDIVISION);
}

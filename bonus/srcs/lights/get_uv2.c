/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_uv2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:22:29 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/16 19:18:43 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "libft.h"
#include "utils.h"
#include <math.h>

static void	get_uv_cy2(t_pos *proj, t_vol *cy, t_couplef *uv, t_xpm *xpm)
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
	if (proj->y >= cy->h)
		proj->y = cy->h + cy->d - add;
	else
		proj->y += add;
	proj->y /= (cy->h + cy->d);
	uv->x = 1 - (raw_u + 0.5);
	uv->y = fmodf(fmodf(proj->y, 1) + 1, 1);
	uv->x = xpm->w - (uv->x * xpm->w);
	uv->y = xpm->h - (uv->y * xpm->h);
}

void	get_uv_cy(t_hit *hit, t_vol *cy, t_couplef *uv, t_xpm *xpm)
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
	get_uv_cy2(&proj, cy, uv, xpm);
}

static void	get_uv_co2(t_pos *proj, t_vol *co, t_couplef *uv, t_xpm *xpm)
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
	if (proj->y <= 0)
		proj->y += add;
	else
		proj->y += co->d / 2;
	proj->y /= (co->h + (co->d / 2));
	uv->x = 1 - (raw_u + 0.5);
	uv->y = fmodf(fmodf(proj->y, 1) + 1, 1);
	uv->x = xpm->w - (uv->x * xpm->w);
	uv->y = xpm->h - (uv->y * xpm->h);
}

void	get_uv_co(t_hit *hit, t_vol *co, t_couplef *uv, t_xpm *xpm)
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
	get_uv_co2(&proj, co, uv, xpm);
}

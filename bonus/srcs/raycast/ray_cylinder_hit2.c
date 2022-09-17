/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_hit2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:39:27 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/17 02:06:51 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"
#include "libft.h"
#include <math.h>

static t_bool	set_cylinder_hit(float *abc, t_ray *ray, t_vol *cy, t_pos *cy_s)
{
	float	d;
	float	t;
	t_pos	h;
	t_pos	temp[2];

	vector_equal(ray->dir, &h);
	d = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (d < 0.f)
		return (false);
	d = sqrtf(d);
	t = (-1 * abc[1] - d) / (2 * abc[0]);
	vector_scale(t, &h);
	vector_add(ray->origin, h, &h);
	vector_ab(cy->pos, h, &temp[0]);
	vector_ab(cy_s[0], h, &temp[1]);
	if (dot_product(temp[0], cy->vec3) > 0
		&& dot_product(temp[1], cy->vec3) < 0)
		create_hit(t, cy, NULL, ray);
	return (true);
}

t_bool	is_cylinder_hit(t_ray *ray, t_vol *cy)
{
	float	abc[3];
	t_pos	va_rao[2];
	t_pos	temp[2];
	t_pos	cy_s[2];
	t_hit	hit;

	set_vector(cy->pos.x + cy->h * cy->vec3.x, cy->pos.y
		+ cy->h * cy->vec3.y, cy->pos.z + cy->h * cy->vec3.z, &cy_s[0]);
	vector_ab(cy->pos, cy_s[0], &cy_s[1]);
	unit_vector(&cy_s[1]);
	cross_product(cy_s[1], ray->dir, &temp[0]);
	cross_product(temp[0], cy_s[1], &va_rao[0]);
	abc[0] = dot_product(va_rao[0], va_rao[0]);
	vector_ab(cy->pos, ray->origin, &temp[1]);
	cross_product(cy_s[1], temp[1], &temp[0]);
	cross_product(temp[0], cy_s[1], &va_rao[1]);
	abc[1] = 2 * dot_product(va_rao[1], va_rao[0]);
	abc[2] = dot_product(va_rao[1], va_rao[1]) - cy->d / 2 * cy->d / 2;
	if (set_cylinder_hit(abc, ray, cy, cy_s) == false)
		return (false);
	check_cylinder_extremity(cy, cy_s[0], ray);
	if (get_hit(&hit) != -1)
		return (true);
	return (false);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cylinder_hit2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:39:27 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 19:03:04 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs_utils.h"
#include "utils.h"
#include "minirt.h"
#include "libft.h"
#include <math.h>

static t_bool	set_cylinder_hit(double *abcdef, double *hty,
	t_ray *ray, t_vol *cy)
{
	hty[0] = abcdef[4] * abcdef[4] - abcdef[3] * abcdef[5];
	if (hty[0] < 0.0)
		return (false);
	hty[0] = sqrtf(hty[0]);
	hty[1] = (-1 * abcdef[4] - hty[0]) / abcdef[3];
	hty[2] = abcdef[2] + hty[1] * abcdef[1];
	if (hty[2] > 0.0 && hty[2] < abcdef[0])
		create_hit(hty[1], cy, NULL, ray);
	hty[1] = (-1 * abcdef[4] + hty[0]) / abcdef[3];
	hty[3] = abcdef[2] + hty[1] * abcdef[1];
	if (hty[3] > 0.f && hty[3] < abcdef[0])
		create_hit(hty[1], cy, NULL, ray);
	return (true);
}

t_bool	is_cylinder_hit(t_ray *ray, t_vol *cy)
{
	t_pos	vec3_cy;
	t_pos	vec3[2];
	double	abcdef[6];
	double	hty[4];
	t_hit	hit;

	set_vector(cy->pos.x + cy->h * cy->vec3.x, cy->pos.y
		+ cy->h * cy->vec3.y, cy->pos.z + cy->h * cy->vec3.z, &vec3_cy);
	vector_ab(cy->pos, vec3_cy, vec3);
	vector_ab(cy->pos, ray->origin, vec3 + 1);
	abcdef[0] = dot_product(vec3[0], vec3[0]);
	abcdef[1] = dot_product(vec3[0], ray->dir);
	abcdef[2] = dot_product(vec3[0], vec3[1]);
	abcdef[3] = abcdef[0] - abcdef[1] * abcdef[1];
	abcdef[4] = abcdef[0] * dot_product(vec3[1], ray->dir)
		- abcdef[2] * abcdef[1];
	abcdef[5] = abcdef[0] * dot_product(vec3[1], vec3[1])
		- abcdef[2] * abcdef[2] - cy->d / 2 * cy->d / 2 * abcdef[0];
	if (set_cylinder_hit(abcdef, hty, ray, cy) == false)
		return (false);
	check_cylinder_extremity(cy, vec3_cy, ray);
	if (get_hit(&hit) != -1)
		return (true);
	return (false);
}

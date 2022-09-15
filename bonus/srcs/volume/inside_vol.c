/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside_vol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:47:12 by fmauguin          #+#    #+#             */
/*   Updated: 2022/09/15 21:38:52 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"
#include "math.h"
#include "structs_utils.h"

int	inside_sphere(t_pos *pos, t_vol *sp)
{
	if ((powf(pos->x - sp->pos.x, 2) + powf(pos->y - sp->pos.y, 2)
			+ powf(pos->z - sp->pos.z, 2)) < powf(sp->d / 2, 2))
		return (true);
	return (false);
}

int	inside_cylinder(t_pos *pos, t_vol *cy)
{
	t_pos	vec_cy;
	t_pos	vec_pt;
	t_pos	cy_top;
	float	dot;
	float	lengthsquared;

	cy_top.x = cy->pos.x + (cy->h * cy->vec3.x);
	cy_top.y = cy->pos.y + (cy->h * cy->vec3.y);
	cy_top.z = cy->pos.z + (cy->h * cy->vec3.z);
	vector_ab(cy->pos, cy_top, &vec_cy);
	vector_ab(cy->pos, *pos, &vec_pt);
	dot = dot_product(vec_cy, vec_pt);
	lengthsquared = powf(cy->h, 2);
	if (dot < 0.0f || dot > lengthsquared)
		return (false);
	else if (((powf(vec_pt.x, 2) + powf(vec_pt.y, 2) + powf(vec_pt.z, 2))
			- (powf(dot, 2) / lengthsquared)) > cy->d / 2)
		return (false);
	return (true);
}

int	inside_plane(t_pos *pos, t_vol *pl)
{
	float	dot;
	t_pos	vec_pt;

	vector_ab(*pos, pl->pos, &vec_pt);
	dot = dot_product(vec_pt, pl->vec3);
	if (dot == 0)
		return (true);
	return (false);
}

int	(*inside_vol(t_vol *volume))(t_pos *pos, t_vol *volume)
{
	int	(*f[3])(t_pos *, t_vol *);

	f[0] = &inside_sphere;
	f[1] = &inside_plane;
	f[2] = &inside_cylinder;
	return (f[volume->type - SPHERE]);
}

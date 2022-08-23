/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 15:47:12 by fmauguin          #+#    #+#             */
/*   Updated: 2022/08/23 19:24:50 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "math.h"
#include "structs_utils.h"

double dotProduct(t_pos a, t_pos b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

void vector(t_pos a, t_pos b, t_pos *vec)
{

	vec->x = b.x - a.x;
	vec->y = b.y - a.y;
	vec->z = b.z - a.z;
}

bool	inside_sphere(t_pos pos, t_vol sp)
{
	if ((exp2(pos.x - sp.pos.x) + exp2(pos.y - sp.pos.y)
		+ exp2(pos.z - sp.pos.z)) < exp2(sp.d / 2))
		return (true);
	return (false);
}

bool	inside_cylinder(t_pos pos, t_vol cy)
{
	t_pos	vec_cy;
	t_pos	vec_pt;
	t_pos	cy_top;
	double	dot;
	double	lengthsquared;

	cy_top.x = (cy.pos.x + cy.h) * cy.vec3.x;
	cy_top.y = (cy.pos.y + cy.h) * cy.vec3.y;
	cy_top.z = (cy.pos.z + cy.h) * cy.vec3.z;
	vector(cy.pos, cy_top, &vec_cy);
	vector(pos, cy.pos, &vec_pt);
	dot = dotProduct(vec_cy, vec_pt);
	lengthsquared = exp2(cy.h);
	if ( dot < 0.0f || dot > lengthsquared)
		return (false);
	else if (((exp2(vec_pt.x) + exp2(vec_pt.y) + exp2(vec_pt.z))
		- (exp2(dot) / lengthsquared)) > cy.d / 2)
		return (false);
	return (true);
}

bool	inside_plane(t_pos pos, t_vol pl)
{
	if (dotProduct(pos, pl.pos) == 1)
		return (true);
	return (false);
}

bool	inside_vol(t_pos pos, t_vol volume)
{
	bool (*f[3])(t_pos , t_vol );

	f[0] = inside_sphere;
	f[1] = inside_plane;
	f[2] = inside_cylinder;
	return (f[volume.type - SPHERE](pos, volume));
}
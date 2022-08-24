/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:54:16 by amahla            #+#    #+#             */
/*   Updated: 2022/08/24 18:57:10 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <math.h>

void	sphere_bounds(t_vol sp, t_box *box)
{
	float	r;

	r = sp.d / 2;
	set_vector(0, r, 0, &box->max);
	set_vector(0, -r, 0, &box->min);
	vector_add(sp.pos, box->max, &box->max);
	vector_add(sp.pos, box->min, &box->min);
	vector_ab(box->min, box->max, &box->size);
}

void	cylinder_bounds(t_vol cy, t_box *box)
{
	float	r;
	t_pos	cy_med;

	r = sqrtf(powf(cy.h / 2, 2) + powf(cy.d / 2, 2));
	cy_med.x = cy.pos.x + (cy.h / 2 * cy.vec3.x);
	cy_med.y = cy.pos.y + (cy.h / 2 * cy.vec3.y);
	cy_med.z = cy.pos.z + (cy.h / 2 * cy.vec3.z);
	set_vector(0, r, 0, &box->max);
	set_vector(0, -r, 0, &box->min);
	vector_add(cy_med, box->max, &box->max);
	vector_add(cy_med, box->min, &box->min);
	vector_ab(box->min, box->max, &box->size);
}
